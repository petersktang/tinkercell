/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * turtle_parser.y - Raptor Turtle / TRIG / N3 parsers - over tokens from turtle grammar lexer
 *
 * Copyright (C) 2003-2010, David Beckett http://www.dajobe.org/
 * Copyright (C) 2003-2005, University of Bristol, UK http://www.bristol.ac.uk/
 * 
 * This package is Free Software and part of Redland http://librdf.org/
 * 
 * It is licensed under the following three licenses as alternatives:
 *   1. GNU Lesser General Public License (LGPL) V2.1 or any newer version
 *   2. GNU General Public License (GPL) V2 or any newer version
 *   3. Apache License, V2.0 or any newer version
 * 
 * You may not use this file except in compliance with at least one of
 * the above three licenses.
 * 
 * See LICENSE.html or LICENSE.txt at the top of this package for the
 * complete terms and further detail along with the license texts for
 * the licenses in COPYING.LIB, COPYING and LICENSE-2.0.txt respectively.
 * 
 * 
 * Turtle is defined in http://www.dajobe.org/2004/01/turtle/
 *
 * Made from a subset of the terms in
 *   http://www.w3.org/DesignIssues/Notation3.html
 *
 * TRIG is defined in http://www.wiwiss.fu-berlin.de/suhl/bizer/TriG/Spec/
 */

%{
#ifdef HAVE_CONFIG_H
#include <raptor_config.h>
#endif

#ifdef WIN32
#include <win32_raptor_config.h>
#endif

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#ifdef HAVE_ERRNO_H
#include <errno.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include <raptor.h>
#include <raptor_internal.h>

#include <turtle_parser.h>

#define YY_DECL int turtle_lexer_lex (YYSTYPE *turtle_parser_lval, yyscan_t yyscanner)
#define YY_NO_UNISTD_H 1
#include <turtle_lexer.h>

#include <turtle_common.h>


/* Make verbose error messages for syntax errors */
#ifdef RAPTOR_DEBUG
#define YYERROR_VERBOSE 1
#endif

/* Slow down the grammar operation and watch it work */
#if RAPTOR_DEBUG > 2
#define YYDEBUG 1
#endif

/* the lexer does not seem to track this */
#undef RAPTOR_TURTLE_USE_ERROR_COLUMNS

/* Prototypes */ 
int turtle_parser_error(void* rdf_parser, const char *msg);

/* Missing turtle_lexer.c/h prototypes */
int turtle_lexer_get_column(yyscan_t yyscanner);
/* Not used here */
/* void turtle_lexer_set_column(int  column_no , yyscan_t yyscanner);*/


/* What the lexer wants */
extern int turtle_lexer_lex (YYSTYPE *turtle_parser_lval, yyscan_t scanner);
#define YYLEX_PARAM ((raptor_turtle_parser*)(((raptor_parser*)rdf_parser)->context))->scanner

/* Pure parser argument (a void*) */
#define YYPARSE_PARAM rdf_parser

/* Make the yyerror below use the rdf_parser */
#undef yyerror
#define yyerror(message) turtle_parser_error(rdf_parser, message)

/* Make lex/yacc interface as small as possible */
#undef yylex
#define yylex turtle_lexer_lex


/* Prototypes for local functions */
static void raptor_turtle_generate_statement(raptor_parser *parser, raptor_statement *triple);

%}


/* directives */



%pure-parser


/* Interface between lexer and parser */
%union {
  unsigned char *string;
  raptor_term *identifier;
  raptor_sequence *sequence;
  raptor_uri *uri;
  int integer; /* 0+ for a xsd:integer datatyped RDF literal */
}

%expect 0


/* others */

%token A "a"
%token AT "@"
%token HAT "^"
%token DOT "."
%token COMMA ","
%token SEMICOLON ";"
%token LEFT_SQUARE "["
%token RIGHT_SQUARE "]"
%token LEFT_ROUND "("
%token RIGHT_ROUND ")"
%token LEFT_CURLY "{"
%token RIGHT_CURLY "}"
%token COLONMINUS ":-"
%token TRUE_TOKEN "true"
%token FALSE_TOKEN "false"

/* literals */
%token <string> STRING_LITERAL "string literal"
%token <uri> URI_LITERAL "URI literal"
%token <string> BLANK_LITERAL "blank node"
%token <uri> QNAME_LITERAL "QName"
%token <string> PREFIX "@prefix"
%token <string> BASE "@base"
%token <string> IDENTIFIER "identifier"
%token <string> INTEGER_LITERAL "integer literal"
%token <string> FLOATING_LITERAL "floating point literal"
%token <string> DECIMAL_LITERAL "decimal literal"

/* syntax error */
%token ERROR_TOKEN

%type <identifier> subject predicate object verb literal resource blank collection graphName
%type <sequence> objectList itemList propertyList

/* tidy up tokens after errors */

%destructor {
  if($$)
    RAPTOR_FREE(cstring, $$);
} STRING_LITERAL BLANK_LITERAL INTEGER_LITERAL FLOATING_LITERAL DECIMAL_LITERAL IDENTIFIER

%destructor {
  if($$)
    raptor_free_uri($$);
} URI_LITERAL QNAME_LITERAL

%destructor {
  if($$)
    raptor_free_term($$);
} subject predicate object verb literal resource blank collection graphName

%destructor {
  if($$)
    raptor_free_sequence($$);
} objectList itemList propertyList

%%

Document : statementList
;

colonMinusOpt: COLONMINUS 
{
  raptor_parser* parser = (raptor_parser *)rdf_parser;
  raptor_turtle_parser* turtle_parser = (raptor_turtle_parser*)parser->context;
  if(!turtle_parser->trig)
    turtle_parser_error(rdf_parser, ":- is not allowed in Turtle");
}
| /* empty */
;

graph: graphName colonMinusOpt LEFT_CURLY
  {
    /* action in mid-rule so this is run BEFORE the triples in graphBody */
    raptor_parser* parser = (raptor_parser *)rdf_parser;
    raptor_turtle_parser* turtle_parser;

    turtle_parser = (raptor_turtle_parser*)parser->context;
    if(!turtle_parser->trig)
      turtle_parser_error(rdf_parser, "{ ... } is not allowed in Turtle");
    else {
      if(turtle_parser->graph_name)
        raptor_free_term(turtle_parser->graph_name);
      turtle_parser->graph_name = $1; /* becomes owner of $1 */
      raptor_parser_start_graph(parser, turtle_parser->graph_name->value.uri, 1);
    }
  }
  graphBody RIGHT_CURLY
{
  raptor_parser* parser = (raptor_parser *)rdf_parser;
  raptor_turtle_parser* turtle_parser;

  turtle_parser = (raptor_turtle_parser*)parser->context;

  if(turtle_parser->trig) {
    raptor_parser_end_graph(parser, turtle_parser->graph_name->value.uri, 1);
    raptor_free_term(turtle_parser->graph_name);
    turtle_parser->graph_name = NULL;
    parser->emitted_default_graph = 0;
  }
}
|
LEFT_CURLY
  {
    /* action in mid-rule so this is run BEFORE the triples in graphBody */
    raptor_parser* parser = (raptor_parser *)rdf_parser;
    raptor_turtle_parser* turtle_parser;

    turtle_parser = (raptor_turtle_parser*)parser->context;
    if(!turtle_parser->trig)
      turtle_parser_error(rdf_parser, "{ ... } is not allowed in Turtle");
    else {
      raptor_parser_start_graph(parser, NULL, 1);
      parser->emitted_default_graph++;
    }
  }
  graphBody RIGHT_CURLY
{
  raptor_parser* parser = (raptor_parser *)rdf_parser;
  raptor_turtle_parser* turtle_parser;

  turtle_parser = (raptor_turtle_parser*)parser->context;
  if(turtle_parser->trig) {
    raptor_parser_end_graph(parser, NULL, 1);
    parser->emitted_default_graph = 0;
  }
}
;

graphName: resource
;

graphBody: triplesList
|
/* empty */
;

triplesList: triples
|
terminatedTriples triplesList
|
terminatedTriples
;

terminatedTriples: triples DOT
;

statementList: statementList statement
| /* empty line */
;

statement: directive
| graph
| terminatedTriples
;

triples: subject propertyList
{
  int i;

#if RAPTOR_DEBUG > 1  
  printf("statement 2\n subject=");
  if($1)
    raptor_term_print_as_ntriples(stdout, $1);
  else
    fputs("NULL", stdout);
  if($2) {
    printf("\n propertyList (reverse order to syntax)=");
    raptor_sequence_print($2, stdout);
    printf("\n");
  } else     
    printf("\n and empty propertyList\n");
#endif

  if($1 && $2) {
    /* have subject and non-empty property list, handle it  */
    for(i = 0; i < raptor_sequence_size($2); i++) {
      raptor_statement* t2 = (raptor_statement*)raptor_sequence_get_at($2, i);
      t2->subject = raptor_term_copy($1);
    }
#if RAPTOR_DEBUG > 1  
    printf(" after substitution propertyList=");
    raptor_sequence_print($2, stdout);
    printf("\n\n");
#endif
    for(i = 0; i < raptor_sequence_size($2); i++) {
      raptor_statement* t2 = (raptor_statement*)raptor_sequence_get_at($2, i);
      raptor_turtle_generate_statement((raptor_parser*)rdf_parser, t2);
    }
  }

  if($2)
    raptor_free_sequence($2);

  if($1)
    raptor_free_term($1);
}
| error DOT
;


objectList: objectList COMMA object
{
  raptor_statement *triple;

#if RAPTOR_DEBUG > 1  
  printf("objectList 1\n");
  if($3) {
    printf(" object=\n");
    raptor_term_print_as_ntriples(stdout, $3);
    printf("\n");
  } else  
    printf(" and empty object\n");
  if($1) {
    printf(" objectList=");
    raptor_sequence_print($1, stdout);
    printf("\n");
  } else
    printf(" and empty objectList\n");
#endif

  if(!$3)
    $$ = NULL;
  else {
    triple = raptor_new_statement_from_nodes(((raptor_parser*)rdf_parser)->world, NULL, NULL, $3, NULL);
    if(!triple) {
      raptor_free_sequence($1);
      YYERROR;
    }
    if(raptor_sequence_push($1, triple)) {
      raptor_free_sequence($1);
      YYERROR;
    }
    $$ = $1;
#if RAPTOR_DEBUG > 1  
    printf(" objectList is now ");
    raptor_sequence_print($$, stdout);
    printf("\n\n");
#endif
  }
}
| object
{
  raptor_statement *triple;

#if RAPTOR_DEBUG > 1  
  printf("objectList 2\n");
  if($1) {
    printf(" object=\n");
    raptor_term_print_as_ntriples(stdout, $1);
    printf("\n");
  } else  
    printf(" and empty object\n");
#endif

  if(!$1)
    $$ = NULL;
  else {
    triple = raptor_new_statement_from_nodes(((raptor_parser*)rdf_parser)->world, NULL, NULL, $1, NULL);
    if(!triple)
      YYERROR;
#ifdef RAPTOR_DEBUG
    $$ = raptor_new_sequence((raptor_data_free_handler)raptor_free_statement,
                             (raptor_data_print_handler)raptor_statement_print);
#else
    $$ = raptor_new_sequence((raptor_data_free_handler)raptor_free_statement, NULL);
#endif
    if(!$$) {
      raptor_free_statement(triple);
      YYERROR;
    }
    if(raptor_sequence_push($$, triple)) {
      raptor_free_sequence($$);
      $$ = NULL;
      YYERROR;
    }
#if RAPTOR_DEBUG > 1  
    printf(" objectList is now ");
    raptor_sequence_print($$, stdout);
    printf("\n\n");
#endif
  }
}
;

itemList: itemList object
{
  raptor_statement *triple;

#if RAPTOR_DEBUG > 1  
  printf("objectList 1\n");
  if($2) {
    printf(" object=\n");
    raptor_term_print_as_ntriples(stdout, $2);
    printf("\n");
  } else  
    printf(" and empty object\n");
  if($1) {
    printf(" objectList=");
    raptor_sequence_print($1, stdout);
    printf("\n");
  } else
    printf(" and empty objectList\n");
#endif

  if(!$2)
    $$ = NULL;
  else {
    triple = raptor_new_statement_from_nodes(((raptor_parser*)rdf_parser)->world, NULL, NULL, $2, NULL);
    if(!triple) {
      raptor_free_sequence($1);
      YYERROR;
    }
    if(raptor_sequence_push($1, triple)) {
      raptor_free_sequence($1);
      YYERROR;
    }
    $$ = $1;
#if RAPTOR_DEBUG > 1  
    printf(" objectList is now ");
    raptor_sequence_print($$, stdout);
    printf("\n\n");
#endif
  }
}
| object
{
  raptor_statement *triple;

#if RAPTOR_DEBUG > 1  
  printf("objectList 2\n");
  if($1) {
    printf(" object=\n");
    raptor_term_print_as_ntriples(stdout, $1);
    printf("\n");
  } else  
    printf(" and empty object\n");
#endif

  if(!$1)
    $$ = NULL;
  else {
    triple = raptor_new_statement_from_nodes(((raptor_parser*)rdf_parser)->world, NULL, NULL, $1, NULL);
    if(!triple)
      YYERROR;
#ifdef RAPTOR_DEBUG
    $$ = raptor_new_sequence((raptor_data_free_handler)raptor_free_statement,
                             (raptor_data_print_handler)raptor_statement_print);
#else
    $$ = raptor_new_sequence((raptor_data_free_handler)raptor_free_statement, NULL);
#endif
    if(!$$) {
      raptor_free_statement(triple);
      YYERROR;
    }
    if(raptor_sequence_push($$, triple)) {
      raptor_free_sequence($$);
      $$ = NULL;
      YYERROR;
    }
#if RAPTOR_DEBUG > 1  
    printf(" objectList is now ");
    raptor_sequence_print($$, stdout);
    printf("\n\n");
#endif
  }
}
;

verb: predicate
{
#if RAPTOR_DEBUG > 1  
  printf("verb predicate=");
  raptor_term_print_as_ntriples(stdout, $1);
  printf("\n");
#endif

  $$ = $1;
}
| A
{
#if RAPTOR_DEBUG > 1  
  printf("verb predicate = rdf:type (a)\n");
#endif

  $$ = raptor_term_copy(RAPTOR_RDF_type_term(((raptor_parser*)rdf_parser)->world));
  if(!$$)
    YYERROR;
}
;


propertyList: propertyList SEMICOLON verb objectList
{
  int i;
  
#if RAPTOR_DEBUG > 1  
  printf("propertyList 1\n verb=");
  raptor_term_print_as_ntriples(stdout, $3);
  printf("\n objectList=");
  raptor_sequence_print($4, stdout);
  printf("\n propertyList=");
  raptor_sequence_print($1, stdout);
  printf("\n\n");
#endif
  
  if($4 == NULL) {
#if RAPTOR_DEBUG > 1  
    printf(" empty objectList not processed\n");
#endif
  } else if($3 && $4) {
    /* non-empty property list, handle it  */
    for(i = 0; i < raptor_sequence_size($4); i++) {
      raptor_statement* t2 = (raptor_statement*)raptor_sequence_get_at($4, i);
      t2->predicate = raptor_term_copy($3);
    }
  
#if RAPTOR_DEBUG > 1  
    printf(" after substitution objectList=");
    raptor_sequence_print($4, stdout);
    printf("\n");
#endif
  }

  if($1 == NULL) {
#if RAPTOR_DEBUG > 1  
    printf(" empty propertyList not copied\n\n");
#endif
  } else if($3 && $4 && $1) {
    while(raptor_sequence_size($4)) {
      raptor_statement* t2 = (raptor_statement*)raptor_sequence_unshift($4);
      if(raptor_sequence_push($1, t2)) {
        raptor_free_sequence($1);
        raptor_free_term($3);
        raptor_free_sequence($4);
        YYERROR;
      }
    }

#if RAPTOR_DEBUG > 1  
    printf(" after appending objectList (reverse order)=");
    raptor_sequence_print($1, stdout);
    printf("\n\n");
#endif

    raptor_free_sequence($4);
  }

  if($3)
    raptor_free_term($3);

  $$ = $1;
}
| verb objectList
{
  int i;
#if RAPTOR_DEBUG > 1  
  printf("propertyList 2\n verb=");
  raptor_term_print_as_ntriples(stdout, $1);
  if($2) {
    printf("\n objectList=");
    raptor_sequence_print($2, stdout);
    printf("\n");
  } else
    printf("\n and empty objectList\n");
#endif

  if($1 && $2) {
    for(i = 0; i < raptor_sequence_size($2); i++) {
      raptor_statement* t2 = (raptor_statement*)raptor_sequence_get_at($2, i);
      t2->predicate = raptor_term_copy($1);
    }

#if RAPTOR_DEBUG > 1  
    printf(" after substitution objectList=");
    raptor_sequence_print($2, stdout);
    printf("\n\n");
#endif
  }

  if($1)
    raptor_free_term($1);

  $$ = $2;
}
| /* empty */
{
#if RAPTOR_DEBUG > 1  
  printf("propertyList 4\n empty returning NULL\n\n");
#endif
  $$ = NULL;
}
| propertyList SEMICOLON
{
  $$ = $1;
#if RAPTOR_DEBUG > 1  
  printf("propertyList 5\n trailing semicolon returning existing list ");
  raptor_sequence_print($$, stdout);
  printf("\n\n");
#endif
}
;

directive : prefix | base
;

prefix: PREFIX IDENTIFIER URI_LITERAL DOT
{
  unsigned char *prefix=$2;
  raptor_turtle_parser* turtle_parser = (raptor_turtle_parser*)(((raptor_parser*)rdf_parser)->context);
  raptor_namespace *ns;

#if 0
  Get around bison complaining about not using $1
#endif

#if RAPTOR_DEBUG > 1  
  printf("directive @prefix %s %s\n",($2 ? (char*)$2 : "(default)"), raptor_uri_as_string($3));
#endif

  if(prefix) {
    size_t len = strlen((const char*)prefix);
    if(prefix[len-1] == ':') {
      if(len == 1)
         /* declaring default namespace prefix @prefix : ... */
        prefix = NULL;
      else
        prefix[len-1]='\0';
    }
  }

  ns = raptor_new_namespace_from_uri(&turtle_parser->namespaces, prefix, $3, 0);
  if(ns) {
    raptor_namespaces_start_namespace(&turtle_parser->namespaces, ns);
    raptor_parser_start_namespace((raptor_parser*)rdf_parser, ns);
  }

  if($2)
    RAPTOR_FREE(cstring, $2);
  raptor_free_uri($3);

  if(!ns)
    YYERROR;
}
;


base: BASE URI_LITERAL DOT
{
  raptor_uri *uri=$2;
  /*raptor_turtle_parser* turtle_parser = (raptor_turtle_parser*)(((raptor_parser*)rdf_parser)->context);*/
  raptor_parser* parser = (raptor_parser*)rdf_parser;
  if(parser->base_uri)
    raptor_free_uri(parser->base_uri);
  parser->base_uri = uri;
}
;

subject: resource
{
  $$ = $1;
}
| blank
{
  $$ = $1;
}
;


predicate: resource
{
  $$ = $1;
}
;


object: resource
{
  $$ = $1;
}
| blank
{
  $$ = $1;
}
| literal
{
#if RAPTOR_DEBUG > 1  
  printf("object literal=");
  raptor_term_print_as_ntriples(stdout, $1);
  printf("\n");
#endif

  $$ = $1;
}
;


literal: STRING_LITERAL AT IDENTIFIER
{
#if RAPTOR_DEBUG > 1  
  printf("literal + language string=\"%s\"\n", $1);
#endif

  $$ = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                    $1, NULL, $3);
  RAPTOR_FREE(cstring, $1);
  RAPTOR_FREE(cstring, $3);
  if(!$$)
    YYERROR;
}
| STRING_LITERAL AT IDENTIFIER HAT URI_LITERAL
{
#if RAPTOR_DEBUG > 1  
  printf("literal + language=\"%s\" datatype string=\"%s\" uri=\"%s\"\n", $1, $3, raptor_uri_as_string($5));
#endif

  if($5) {
    if($3) {
      raptor_parser_warning((raptor_parser*)rdf_parser, 
                            "Ignoring language used with datatyped literal");
      RAPTOR_FREE(cstring, $3);
      $3 = NULL;
    }
  
    $$ = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                      $1, $5, NULL);
    RAPTOR_FREE(cstring, $1);
    raptor_free_uri($5);
    if(!$$)
      YYERROR;
  } else
    $$ = NULL;
    
}
| STRING_LITERAL AT IDENTIFIER HAT QNAME_LITERAL
{
#if RAPTOR_DEBUG > 1  
  printf("literal + language=\"%s\" datatype string=\"%s\" qname URI=<%s>\n", $1, $3, raptor_uri_as_string($5));
#endif

  if($5) {
    if($3) {
      raptor_parser_warning((raptor_parser*)rdf_parser, 
                            "Ignoring language used with datatyped literal");
      RAPTOR_FREE(cstring, $3);
      $3 = NULL;
    }
  
    $$ = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                      $1, $5, NULL);
    RAPTOR_FREE(cstring, $1);
    raptor_free_uri($5);
    if(!$$)
      YYERROR;
  } else
    $$ = NULL;

}
| STRING_LITERAL HAT URI_LITERAL
{
#if RAPTOR_DEBUG > 1  
  printf("literal + datatype string=\"%s\" uri=\"%s\"\n", $1, raptor_uri_as_string($3));
#endif

  if($3) {
    $$ = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                      $1, $3, NULL);
    RAPTOR_FREE(cstring, $1);
    raptor_free_uri($3);
    if(!$$)
      YYERROR;
  } else
    $$ = NULL;
    
}
| STRING_LITERAL HAT QNAME_LITERAL
{
#if RAPTOR_DEBUG > 1  
  printf("literal + datatype string=\"%s\" qname URI=<%s>\n", $1, raptor_uri_as_string($3));
#endif

  if($3) {
    $$ = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                      $1, $3, NULL);
    RAPTOR_FREE(cstring, $1);
    raptor_free_uri($3);
    if(!$$)
      YYERROR;
  } else
    $$ = NULL;
}
| STRING_LITERAL
{
#if RAPTOR_DEBUG > 1  
  printf("literal string=\"%s\"\n", $1);
#endif

  $$ = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                    $1, NULL, NULL);
  RAPTOR_FREE(cstring, $1);
  if(!$$)
    YYERROR;
}
| INTEGER_LITERAL
{
  raptor_uri *uri;
#if RAPTOR_DEBUG > 1  
  printf("resource integer=%s\n", $1);
#endif
  uri = raptor_new_uri(((raptor_parser*)rdf_parser)->world, (const unsigned char*)"http://www.w3.org/2001/XMLSchema#integer");
  if(!uri) {
    RAPTOR_FREE(cstring, $1);
    YYERROR;
  }
  $$ = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                    $1, uri, NULL);
  RAPTOR_FREE(cstring, $1);
  raptor_free_uri(uri);
  if(!$$)
    YYERROR;
}
| FLOATING_LITERAL
{
  raptor_uri *uri;
#if RAPTOR_DEBUG > 1  
  printf("resource double=%s\n", $1);
#endif
  uri = raptor_new_uri(((raptor_parser*)rdf_parser)->world, (const unsigned char*)"http://www.w3.org/2001/XMLSchema#double");
  if(!uri) {
    RAPTOR_FREE(cstring, $1);
    YYERROR;
  }
  $$ = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                    $1, uri, NULL);
  RAPTOR_FREE(cstring, $1);
  raptor_free_uri(uri);
  if(!$$)
    YYERROR;
}
| DECIMAL_LITERAL
{
  raptor_uri *uri;
#if RAPTOR_DEBUG > 1  
  printf("resource decimal=%s\n", $1);
#endif
  uri = raptor_new_uri(((raptor_parser*)rdf_parser)->world, (const unsigned char*)"http://www.w3.org/2001/XMLSchema#decimal");
  if(!uri) {
    RAPTOR_FREE(cstring, $1);
    YYERROR;
  }
  $$ = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                    $1, uri, NULL);
  RAPTOR_FREE(cstring, $1);
  raptor_free_uri(uri);
  if(!$$)
    YYERROR;
}
| TRUE_TOKEN
{
  raptor_uri *uri;
#if RAPTOR_DEBUG > 1  
  fputs("resource boolean true\n", stderr);
#endif
  uri = raptor_new_uri(((raptor_parser*)rdf_parser)->world, (const unsigned char*)"http://www.w3.org/2001/XMLSchema#boolean");
  if(!uri)
    YYERROR;
  $$ = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                    (const unsigned char*)"true", uri, NULL);
  raptor_free_uri(uri);
  if(!$$)
    YYERROR;
}
| FALSE_TOKEN
{
  raptor_uri *uri;
#if RAPTOR_DEBUG > 1  
  fputs("resource boolean false\n", stderr);
#endif
  uri = raptor_new_uri(((raptor_parser*)rdf_parser)->world, (const unsigned char*)"http://www.w3.org/2001/XMLSchema#boolean");
  if(!uri)
    YYERROR;
  $$ = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                    (const unsigned char*)"false", uri, NULL);
  raptor_free_uri(uri);
  if(!$$)
    YYERROR;
}
;


resource: URI_LITERAL
{
#if RAPTOR_DEBUG > 1  
  printf("resource URI=<%s>\n", raptor_uri_as_string($1));
#endif

  if($1) {
    $$ = raptor_new_term_from_uri(((raptor_parser*)rdf_parser)->world, $1);
    raptor_free_uri($1);
    if(!$$)
      YYERROR;
  } else
    $$ = NULL;
}
| QNAME_LITERAL
{
#if RAPTOR_DEBUG > 1  
  printf("resource qname URI=<%s>\n", raptor_uri_as_string($1));
#endif

  if($1) {
    $$ = raptor_new_term_from_uri(((raptor_parser*)rdf_parser)->world, $1);
    raptor_free_uri($1);
    if(!$$)
      YYERROR;
  } else
    $$ = NULL;
}
;


blank: BLANK_LITERAL
{
  const unsigned char *id;
#if RAPTOR_DEBUG > 1  
  printf("subject blank=\"%s\"\n", $1);
#endif
  id = raptor_world_internal_generate_id(((raptor_parser*)rdf_parser)->world,
                                         $1);
  if(!id)
    YYERROR;

  $$ = raptor_new_term_from_blank(((raptor_parser*)rdf_parser)->world, id);
  RAPTOR_FREE(cstring, id);

  if(!$$)
    YYERROR;
}
| LEFT_SQUARE propertyList RIGHT_SQUARE
{
  int i;
  const unsigned char *id;

  id = raptor_world_generate_bnodeid(((raptor_parser*)rdf_parser)->world);
  if(!id) {
    if($2)
      raptor_free_sequence($2);
    YYERROR;
  }

  $$ = raptor_new_term_from_blank(((raptor_parser*)rdf_parser)->world, id);
  RAPTOR_FREE(cstring, id);
  if(!$$) {
    if($2)
      raptor_free_sequence($2);
    YYERROR;
  }

  if($2 == NULL) {
#if RAPTOR_DEBUG > 1  
    printf("resource\n propertyList=");
    raptor_term_print_as_ntriples(stdout, $$);
    printf("\n");
#endif
  } else {
    /* non-empty property list, handle it  */
#if RAPTOR_DEBUG > 1  
    printf("resource\n propertyList=");
    raptor_sequence_print($2, stdout);
    printf("\n");
#endif

    for(i = 0; i < raptor_sequence_size($2); i++) {
      raptor_statement* t2 = (raptor_statement*)raptor_sequence_get_at($2, i);
      t2->subject = raptor_term_copy($$);
      raptor_turtle_generate_statement((raptor_parser*)rdf_parser, t2);
    }

#if RAPTOR_DEBUG > 1
    printf(" after substitution objectList=");
    raptor_sequence_print($2, stdout);
    printf("\n\n");
#endif

    raptor_free_sequence($2);

  }
  
}
| collection
{
  $$ = $1;
}
;


collection: LEFT_ROUND itemList RIGHT_ROUND
{
  int i;
  raptor_world* world = ((raptor_parser*)rdf_parser)->world;
  raptor_term* first_identifier = NULL;
  raptor_term* rest_identifier = NULL;
  raptor_term* object = NULL;
  raptor_term* blank = NULL;

#if RAPTOR_DEBUG > 1  
  printf("collection\n objectList=");
  raptor_sequence_print($2, stdout);
  printf("\n");
#endif

  first_identifier = raptor_new_term_from_uri(world, RAPTOR_RDF_first_URI(world));
  if(!first_identifier)
    goto err_collection;
  rest_identifier = raptor_new_term_from_uri(world, RAPTOR_RDF_rest_URI(world));
  if(!rest_identifier)
    goto err_collection;
  
  /* non-empty property list, handle it  */
#if RAPTOR_DEBUG > 1  
  printf("resource\n propertyList=");
  raptor_sequence_print($2, stdout);
  printf("\n");
#endif

  object = raptor_new_term_from_uri(world, RAPTOR_RDF_nil_URI(world));
  if(!object)
    goto err_collection;

  for(i = raptor_sequence_size($2)-1; i>=0; i--) {
    raptor_term* temp;
    raptor_statement* t2 = (raptor_statement*)raptor_sequence_get_at($2, i);
    const unsigned char *blank_id;

    blank_id = raptor_world_generate_bnodeid(((raptor_parser*)rdf_parser)->world);
    if(!blank_id)
      goto err_collection;

    blank = raptor_new_term_from_blank(((raptor_parser*)rdf_parser)->world,
                                       blank_id);
    RAPTOR_FREE(cstring, blank_id);
    if(!blank)
      goto err_collection;
    
    t2->subject = blank;
    t2->predicate = first_identifier;
    /* t2->object already set to the value we want */
    raptor_turtle_generate_statement((raptor_parser*)rdf_parser, t2);
    
    temp = t2->object;
    
    t2->subject = blank;
    t2->predicate = rest_identifier;
    t2->object = object;
    raptor_turtle_generate_statement((raptor_parser*)rdf_parser, t2);

    t2->subject = NULL;
    t2->predicate = NULL;
    t2->object = temp;

    raptor_free_term(object);
    object = blank;
    blank = NULL;
  }
  
#if RAPTOR_DEBUG > 1
  printf(" after substitution objectList=");
  raptor_sequence_print($2, stdout);
  printf("\n\n");
#endif

  raptor_free_sequence($2);

  raptor_free_term(first_identifier);
  raptor_free_term(rest_identifier);

  $$=object;

  break; /* success */

  err_collection:

  if(blank)
    raptor_free_term(blank);

  if(object)
    raptor_free_term(object);

  if(rest_identifier)
    raptor_free_term(rest_identifier);

  if(first_identifier)
    raptor_free_term(first_identifier);

  raptor_free_sequence($2);

  YYERROR;
}
|  LEFT_ROUND RIGHT_ROUND 
{
  raptor_world* world = ((raptor_parser*)rdf_parser)->world;

#if RAPTOR_DEBUG > 1  
  printf("collection\n empty\n");
#endif

  $$ = raptor_new_term_from_uri(world, RAPTOR_RDF_nil_URI(world));
  if(!$$)
    YYERROR;
}
;


%%


/* Support functions */

/* This is declared in turtle_lexer.h but never used, so we always get
 * a warning unless this dummy code is here.  Used once below as a return.
 */
static int yy_init_globals (yyscan_t yyscanner ) { return 0; };


int
turtle_parser_error(void* ctx, const char *msg)
{
  raptor_parser* rdf_parser = (raptor_parser *)ctx;
  raptor_turtle_parser* turtle_parser;

  turtle_parser = (raptor_turtle_parser*)rdf_parser->context;
  
  if(turtle_parser->error_count++)
    return 0;

  rdf_parser->locator.line = turtle_parser->lineno;
#ifdef RAPTOR_TURTLE_USE_ERROR_COLUMNS
  rdf_parser->locator.column = turtle_lexer_get_column(yyscanner);
#endif

  raptor_log_error(rdf_parser->world, RAPTOR_LOG_LEVEL_ERROR,
                   &rdf_parser->locator, msg);

  return yy_init_globals(NULL); /* 0 but a way to use yy_init_globals */
}


int
turtle_syntax_error(raptor_parser *rdf_parser, const char *message, ...)
{
  raptor_turtle_parser* turtle_parser = (raptor_turtle_parser*)rdf_parser->context;
  va_list arguments;

  if(turtle_parser->error_count++)
    return 0;

  rdf_parser->locator.line = turtle_parser->lineno;
#ifdef RAPTOR_TURTLE_USE_ERROR_COLUMNS
  rdf_parser->locator.column = turtle_lexer_get_column(yyscanner);
#endif

  va_start(arguments, message);
  
  raptor_parser_error_varargs(((raptor_parser*)rdf_parser), message, arguments);

  va_end(arguments);

  return 0;
}


raptor_uri*
turtle_qname_to_uri(raptor_parser *rdf_parser, unsigned char *name, size_t name_len) 
{
  raptor_turtle_parser* turtle_parser = (raptor_turtle_parser*)rdf_parser->context;

  rdf_parser->locator.line = turtle_parser->lineno;
#ifdef RAPTOR_TURTLE_USE_ERROR_COLUMNS
  rdf_parser->locator.column = turtle_lexer_get_column(yyscanner);
#endif

  return raptor_qname_string_to_uri(&turtle_parser->namespaces, name, name_len);
}



static int
turtle_parse(raptor_parser *rdf_parser, const char *string, size_t length) {
  raptor_turtle_parser* turtle_parser = (raptor_turtle_parser*)rdf_parser->context;
  void *buffer;
  
  if(!string || !*string)
    return 0;
  
  if(turtle_lexer_lex_init(&turtle_parser->scanner))
    return 1;
  turtle_parser->scanner_set = 1;

  turtle_lexer_set_extra(rdf_parser, turtle_parser->scanner);
  buffer = turtle_lexer__scan_bytes(string, length, turtle_parser->scanner);

  turtle_parser_parse(rdf_parser);

  turtle_lexer_lex_destroy(turtle_parser->scanner);
  turtle_parser->scanner_set = 0;

  return 0;
}


/**
 * raptor_turtle_parse_init - Initialise the Raptor Turtle parser
 *
 * Return value: non 0 on failure
 **/

static int
raptor_turtle_parse_init(raptor_parser* rdf_parser, const char *name) {
  raptor_turtle_parser* turtle_parser = (raptor_turtle_parser*)rdf_parser->context;

  if(raptor_namespaces_init(rdf_parser->world, &turtle_parser->namespaces, 0))
    return 1;

  turtle_parser->trig = !strcmp(name, "trig");

  return 0;
}


/* PUBLIC FUNCTIONS */


/*
 * raptor_turtle_parse_terminate - Free the Raptor Turtle parser
 * @rdf_parser: parser object
 * 
 **/
static void
raptor_turtle_parse_terminate(raptor_parser *rdf_parser) {
  raptor_turtle_parser *turtle_parser = (raptor_turtle_parser*)rdf_parser->context;

  raptor_namespaces_clear(&turtle_parser->namespaces);

  if(turtle_parser->scanner_set) {
    turtle_lexer_lex_destroy(turtle_parser->scanner);
    turtle_parser->scanner_set = 0;
  }

  if(turtle_parser->buffer)
    RAPTOR_FREE(cdata, turtle_parser->buffer);

  if(turtle_parser->graph_name) {
    raptor_free_term(turtle_parser->graph_name);
    turtle_parser->graph_name = NULL;
  }
}


static void
raptor_turtle_generate_statement(raptor_parser *parser, raptor_statement *t)
{
  raptor_turtle_parser *turtle_parser = (raptor_turtle_parser*)parser->context;
  raptor_statement *statement = &parser->statement;

  if(!t->subject || !t->predicate || !t->object)
    return;

  if(!parser->statement_handler)
    return;

  if(turtle_parser->trig && turtle_parser->graph_name)
    statement->graph = raptor_term_copy(turtle_parser->graph_name);

  if(!parser->emitted_default_graph && !turtle_parser->graph_name) {
    /* for non-TRIG - start default graph at first triple */
    raptor_parser_start_graph(parser, NULL, 0);
    parser->emitted_default_graph++;
  }
  
  /* Two choices for subject for Turtle */
  if(t->subject->type == RAPTOR_TERM_TYPE_BLANK) {
    statement->subject = raptor_new_term_from_blank(parser->world,
                                                    t->subject->value.blank.string);
  } else {
    /* RAPTOR_TERM_TYPE_URI */
    RAPTOR_ASSERT(t->subject->type != RAPTOR_TERM_TYPE_URI,
                  "subject type is not resource");
    statement->subject = raptor_new_term_from_uri(parser->world,
                                                  t->subject->value.uri);
  }

  /* Predicates are URIs but check for bad ordinals */
  if(!strncmp((const char*)raptor_uri_as_string(t->predicate->value.uri),
              "http://www.w3.org/1999/02/22-rdf-syntax-ns#_", 44)) {
    unsigned char* predicate_uri_string = raptor_uri_as_string(t->predicate->value.uri);
    int predicate_ordinal = raptor_check_ordinal(predicate_uri_string+44);
    if(predicate_ordinal <= 0)
      raptor_parser_error(parser, "Illegal ordinal value %d in property '%s'.", predicate_ordinal, predicate_uri_string);
  }
  
  statement->predicate = raptor_new_term_from_uri(parser->world,
                                                  t->predicate->value.uri);
  

  /* Three choices for object for Turtle */
  if(t->object->type == RAPTOR_TERM_TYPE_URI) {
    statement->object = raptor_new_term_from_uri(parser->world,
                                                 t->object->value.uri);
  } else if(t->object->type == RAPTOR_TERM_TYPE_BLANK) {
    statement->object = raptor_new_term_from_blank(parser->world,
                                                   t->object->value.blank.string);
  } else {
    /* RAPTOR_TERM_TYPE_LITERAL */
    RAPTOR_ASSERT(t->object->type != RAPTOR_TERM_TYPE_LITERAL,
                  "object type is not literal");
    statement->object = raptor_new_term_from_literal(parser->world,
                                                     t->object->value.literal.string,
                                                     t->object->value.literal.datatype,
                                                     t->object->value.literal.language);
  }

  /* Generate the statement */
  (*parser->statement_handler)(parser->user_data, statement);

  raptor_free_term(statement->subject); statement->subject = NULL;
  raptor_free_term(statement->predicate); statement->predicate = NULL;
  raptor_free_term(statement->object); statement->object = NULL;
  if(statement->graph) {
    raptor_free_term(statement->graph); statement->graph = NULL;
  }
}



static int
raptor_turtle_parse_chunk(raptor_parser* rdf_parser, 
                          const unsigned char *s, size_t len,
                          int is_end)
{
  char *ptr;
  raptor_turtle_parser *turtle_parser;

  turtle_parser = (raptor_turtle_parser*)rdf_parser->context;
  
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1
  RAPTOR_DEBUG2("adding %d bytes to line buffer\n", (int)len);
#endif

  if(len) {
    turtle_parser->buffer = (char*)RAPTOR_REALLOC(cstring, turtle_parser->buffer, turtle_parser->buffer_length + len + 1);
    if(!turtle_parser->buffer) {
      raptor_parser_fatal_error(rdf_parser, "Out of memory");
      return 1;
    }

    /* move pointer to end of cdata buffer */
    ptr = turtle_parser->buffer+turtle_parser->buffer_length;

    /* adjust stored length */
    turtle_parser->buffer_length += len;

    /* now write new stuff at end of cdata buffer */
    memcpy(ptr, s, len);
    ptr += len;
    *ptr = '\0';

#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1
    RAPTOR_DEBUG3("buffer buffer now '%s' (%d bytes)\n", 
                  turtle_parser->buffer, turtle_parser->buffer_length);
#endif
  }
  
  /* if not end, wait for rest of input */
  if(!is_end)
    return 0;

  /* Nothing to do */
  if(!turtle_parser->buffer_length)
    return 0;
  
  turtle_parse(rdf_parser, turtle_parser->buffer, turtle_parser->buffer_length);
  
  if(rdf_parser->emitted_default_graph) {
    /* for non-TRIG - end default graph after last triple */
    raptor_parser_end_graph(rdf_parser, NULL, 0);
    rdf_parser->emitted_default_graph--;
  }
  return 0;
}


static int
raptor_turtle_parse_start(raptor_parser *rdf_parser) 
{
  raptor_locator *locator=&rdf_parser->locator;
  raptor_turtle_parser *turtle_parser = (raptor_turtle_parser*)rdf_parser->context;

  /* base URI required for Turtle */
  if(!rdf_parser->base_uri)
    return 1;

  locator->line = 1;
  locator->column= -1; /* No column info */
  locator->byte= -1; /* No bytes info */

  if(turtle_parser->buffer_length) {
    RAPTOR_FREE(cdata, turtle_parser->buffer);
    turtle_parser->buffer = NULL;
    turtle_parser->buffer_length = 0;
  }
  
  turtle_parser->lineno = 1;

  return 0;
}


static int
raptor_turtle_parse_recognise_syntax(raptor_parser_factory* factory, 
                                     const unsigned char *buffer, size_t len,
                                     const unsigned char *identifier, 
                                     const unsigned char *suffix, 
                                     const char *mime_type)
{
  int score= 0;
  
  if(suffix) {
    if(!strcmp((const char*)suffix, "ttl"))
      score = 8;
    if(!strcmp((const char*)suffix, "n3"))
      score = 3;
  }
  
  if(mime_type) {
    if(strstr((const char*)mime_type, "turtle"))
      score += 6;
    if(strstr((const char*)mime_type, "n3"))
      score += 3;
  }

  /* Do this as long as N3 is not supported since it shares the same syntax */
  if(buffer && len) {
#define  HAS_TURTLE_PREFIX (raptor_memstr((const char*)buffer, len, "@prefix ") != NULL)
/* The following could also be found with N-Triples but not with @prefix */
#define  HAS_TURTLE_RDF_URI (raptor_memstr((const char*)buffer, len, ": <http://www.w3.org/1999/02/22-rdf-syntax-ns#>") != NULL)

    if(HAS_TURTLE_PREFIX) {
      score = 6;
      if(HAS_TURTLE_RDF_URI)
        score += 2;
    }
  }
  
  return score;
}


static raptor_uri*
raptor_turtle_get_graph(raptor_parser* rdf_parser)
{
  raptor_turtle_parser *turtle_parser;

  turtle_parser = (raptor_turtle_parser*)rdf_parser->context;
  if(turtle_parser->graph_name)
    return raptor_uri_copy(turtle_parser->graph_name->value.uri);

  return NULL;
}


#ifdef RAPTOR_PARSER_TRIG
static int
raptor_trig_parse_recognise_syntax(raptor_parser_factory* factory, 
                                   const unsigned char *buffer, size_t len,
                                   const unsigned char *identifier, 
                                   const unsigned char *suffix, 
                                   const char *mime_type)
{
  int score= 0;
  
  if(suffix) {
    if(!strcmp((const char*)suffix, "trig"))
      score = 9;
#ifndef RAPTOR_PARSER_TURTLE
    if(!strcmp((const char*)suffix, "ttl"))
      score = 8;
#endif
    if(!strcmp((const char*)suffix, "n3"))
      score = 3;
  }
  
  if(mime_type) {
#ifndef RAPTOR_PARSER_TURTLE
    if(strstr((const char*)mime_type, "turtle"))
      score += 6;
#endif
    if(strstr((const char*)mime_type, "n3"))
      score += 3;
  }

#ifndef RAPTOR_PARSER_TURTLE
  /* Do this as long as N3 is not supported since it shares the same syntax */
  if(buffer && len) {
#define  HAS_TRIG_PREFIX (raptor_memstr((const char*)buffer, len, "@prefix ") != NULL)
/* The following could also be found with N-Triples but not with @prefix */
#define  HAS_TRIG_RDF_URI (raptor_memstr((const char*)buffer, len, ": <http://www.w3.org/1999/02/22-rdf-syntax-ns#>") != NULL)

    if(HAS_TRIG_PREFIX) {
      score = 6;
      if(HAS_TRIG_RDF_URI)
        score += 2;
    }
  }
#endif
  
  return score;
}
#endif


#ifdef RAPTOR_PARSER_TURTLE
static const char* const turtle_names[4] = { "turtle", "ntriples-plus", "n3", NULL };

static const char* const turtle_uri_strings[2] = {
  "http://www.dajobe.org/2004/01/turtle/",
  NULL
};
  
#define TURTLE_TYPES_COUNT 5
static const raptor_type_q turtle_types[TURTLE_TYPES_COUNT + 1] = {
  /* first one is the default */
  { "application/x-turtle", 20, 10},
  { "application/turtle", 18, 10},
  { "text/n3", 7, 3},
  { "text/rdf+n3", 11, 3},
  { "application/rdf+n3", 18, 3},
  { NULL, 0}
};

static int
raptor_turtle_parser_register_factory(raptor_parser_factory *factory) 
{
  int rc = 0;

  factory->desc.names = turtle_names;

  factory->desc.mime_types = turtle_types;

  factory->desc.label = "Turtle Terse RDF Triple Language";
  factory->desc.uri_strings = turtle_uri_strings;

  factory->desc.flags = RAPTOR_SYNTAX_NEED_BASE_URI;
  
  factory->context_length     = sizeof(raptor_turtle_parser);
  
  factory->init      = raptor_turtle_parse_init;
  factory->terminate = raptor_turtle_parse_terminate;
  factory->start     = raptor_turtle_parse_start;
  factory->chunk     = raptor_turtle_parse_chunk;
  factory->recognise_syntax = raptor_turtle_parse_recognise_syntax;
  factory->get_graph = raptor_turtle_get_graph;

  return rc;
}
#endif


#ifdef RAPTOR_PARSER_TRIG
static const char* const trig_names[2] = { "trig", NULL };
  
static const char* const trig_uri_strings[2] = {
  "http://www.wiwiss.fu-berlin.de/suhl/bizer/TriG/Spec/",
  NULL
};
  
#define TRIG_TYPES_COUNT 1
static const raptor_type_q trig_types[TRIG_TYPES_COUNT + 1] = {
  /* first one is the default */
  { "application/x-trig", 18, 10},
  { NULL, 0, 0}
};

static int
raptor_trig_parser_register_factory(raptor_parser_factory *factory) 
{
  int rc = 0;

  factory->desc.names = trig_names;

  factory->desc.mime_types = trig_types;

  factory->desc.label = "TriG - Turtle with Named Graphs";
  factory->desc.uri_strings = trig_uri_strings;

  factory->desc.flags = RAPTOR_SYNTAX_NEED_BASE_URI;
  
  factory->context_length     = sizeof(raptor_turtle_parser);
  
  factory->init      = raptor_turtle_parse_init;
  factory->terminate = raptor_turtle_parse_terminate;
  factory->start     = raptor_turtle_parse_start;
  factory->chunk     = raptor_turtle_parse_chunk;
  factory->recognise_syntax = raptor_trig_parse_recognise_syntax;
  factory->get_graph = raptor_turtle_get_graph;

  return rc;
}
#endif


#ifdef RAPTOR_PARSER_TURTLE
int
raptor_init_parser_turtle(raptor_world* world)
{
  return !raptor_world_register_parser_factory(world,
                                               &raptor_turtle_parser_register_factory);
}
#endif

#ifdef RAPTOR_PARSER_TRIG
int
raptor_init_parser_trig(raptor_world* world)
{
  return !raptor_world_register_parser_factory(world,
                                               &raptor_trig_parser_register_factory);
}
#endif


#ifdef STANDALONE
#include <stdio.h>
#include <locale.h>

#define TURTLE_FILE_BUF_SIZE 2048

static
void turtle_parser_print_statement(void *user,
                                   const raptor_statement *statement) 
{
  FILE* stream = (FILE*)user;
  raptor_statement_print(statement, stream);
  putc('\n', stream);
}
  


int
main(int argc, char *argv[]) 
{
  char string[TURTLE_FILE_BUF_SIZE];
  raptor_parser rdf_parser; /* static */
  raptor_turtle_parser turtle_parser; /* static */
  raptor_locator *locator = &rdf_parser.locator;
  FILE *fh;
  const char *filename;
  int rc;
  
#if RAPTOR_DEBUG > 2
  turtle_parser_debug = 1;
#endif

  if(argc > 1) {
    filename = argv[1];
    fh = fopen(filename, "r");
    if(!fh) {
      fprintf(stderr, "%s: Cannot open file %s - %s\n", argv[0], filename,
              strerror(errno));
      exit(1);
    }
  } else {
    filename="<stdin>";
    fh = stdin;
  }

  memset(string, 0, TURTLE_FILE_BUF_SIZE);
  rc = fread(string, TURTLE_FILE_BUF_SIZE, 1, fh);
  if(rc < TURTLE_FILE_BUF_SIZE) {
    if(ferror(fh)) {
      fprintf(stderr, "%s: file '%s' read failed - %s\n",
              argv[0], filename, strerror(errno));
      fclose(fh);
      return(1);
    }
  }
  
  if(argc > 1)
    fclose(fh);

  memset(&rdf_parser, 0, sizeof(rdf_parser));
  memset(&turtle_parser, 0, sizeof(turtle_parser));

  locator->line= locator->column = -1;
  locator->file= filename;

  turtle_parser.lineno= 1;

  rdf_parser.world = raptor_world_instance();
  rdf_parser.context=&turtle_parser;
  rdf_parser.base_uri = raptor_new_uri((const unsigned char*)"http://example.org/fake-base-uri/");

  raptor_parser_set_statement_handler(&rdf_parser, stdout, turtle_parser_print_statement);
  raptor_turtle_parse_init(&rdf_parser, "turtle");
  
  turtle_parser.error_count = 0;

  turtle_parse(&rdf_parser, string, strlen(string));

  raptor_turtle_parse_terminate(&rdf_parser);
  
  raptor_free_uri(rdf_parser.base_uri);

  return (0);
}
#endif
