/**
 * @file    FunctionDefinition.cpp
 * @brief   Implementation of FunctionDefinition and ListOfFunctionDefinitions.
 * @author  Ben Bornstein
 *
 * $Id: FunctionDefinition.cpp 10143 2009-08-29 10:59:15Z sarahkeating $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/trunk/libsbml/src/sbml/FunctionDefinition.cpp $
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 *
 * Copyright (C) 2009-2011 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. EMBL European Bioinformatics Institute (EBML-EBI), Hinxton, UK
 *  
 * Copyright (C) 2006-2008 by the California Institute of Technology,
 *     Pasadena, CA, USA 
 *  
 * Copyright (C) 2002-2005 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. Japan Science and Technology Agency, Japan
 * 
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.  A copy of the license agreement is provided
 * in the file named "LICENSE.txt" included with this software distribution
 * and also available online as http://sbml.org/software/libsbml/license.html
 * ---------------------------------------------------------------------- -->*/

#include <cstring>

#include <sbml/xml/XMLNode.h>
#include <sbml/xml/XMLAttributes.h>
#include <sbml/xml/XMLInputStream.h>
#include <sbml/xml/XMLOutputStream.h>

#include <sbml/math/FormulaParser.h>
#include <sbml/math/ASTNode.h>
#include <sbml/math/MathML.h>

#include <sbml/SBO.h>
#include <sbml/SBMLVisitor.h>
#include <sbml/SBMLError.h>
#include <sbml/FunctionDefinition.h>
#include <sbml/SBMLDocument.h>
#include <sbml/Model.h>

/** @cond doxygen-ignored */

using namespace std;

/** @endcond */

LIBSBML_CPP_NAMESPACE_BEGIN

FunctionDefinition::FunctionDefinition (unsigned int level, unsigned int version) :
   SBase ( level, version )
 , mId   ( "" )
 , mName ( "" )
 , mMath ( NULL  )
{
  if (!hasValidLevelVersionNamespaceCombination())
    throw SBMLConstructorException();
}


FunctionDefinition::FunctionDefinition (SBMLNamespaces * sbmlns) :
   SBase ( sbmlns )
 , mId   ( "" )
 , mName ( "" )
 , mMath ( NULL  )
{
  if (!hasValidLevelVersionNamespaceCombination())
  {
    std::string err(getElementName());
    XMLNamespaces* xmlns = sbmlns->getNamespaces();
    if (xmlns)
    {
      std::ostringstream oss;
      XMLOutputStream xos(oss);
      xos << *xmlns;
      err.append(oss.str());
    }
    throw SBMLConstructorException(err);
  }

  loadPlugins(sbmlns);
}


/*
 * Destroys this FunctionDefinition.
 */
FunctionDefinition::~FunctionDefinition ()
{
  delete mMath;
}


/*
 * Copy constructor. Creates a copy of this FunctionDefinition.
 */
FunctionDefinition::FunctionDefinition (const FunctionDefinition& orig) :
   SBase             ( orig         )
 , mMath             ( NULL            )
{
  if (&orig == NULL)
  {
    throw SBMLConstructorException("Null argument to copy constructor");
  }
  else
  {
    mId               = orig.mId;
    mName             = orig.mName;
  
    if (orig.mMath != NULL) 
    {
      mMath = orig.mMath->deepCopy();
      mMath->setParentSBMLObject(this);
    }
  }
}


/*
 * Assignment operator
 */
FunctionDefinition& FunctionDefinition::operator=(const FunctionDefinition& rhs)
{
  if (&rhs == NULL)
  {
    throw SBMLConstructorException("Null argument to assignment operator");
  }
  else if(&rhs!=this)
  {
    this->SBase::operator =(rhs);
    mId = rhs.mId;
    mName = rhs.mName;

    delete mMath;
    if (rhs.mMath != NULL) 
    {
      mMath = rhs.mMath->deepCopy();
      mMath->setParentSBMLObject(this);
    }
    else
    {
      mMath = NULL;
    }
  }

  return *this;
}


/*
 * Accepts the given SBMLVisitor.
 *
 * @return the result of calling <code>v.visit()</code>, which indicates
 * whether or not the Visitor would like to visit the Model's next
 * FunctionDefinition (if available).
 */
bool
FunctionDefinition::accept (SBMLVisitor& v) const
{
  return v.visit(*this);
}


/*
 * @return a (deep) copy of this FunctionDefinition.
 */
FunctionDefinition*
FunctionDefinition::clone () const
{
  return new FunctionDefinition(*this);
}


/*
 * @return the id of this SBML object.
 */
const string&
FunctionDefinition::getId () const
{
  return mId;
}


/*
 * @return the name of this SBML object.
 */
const string&
FunctionDefinition::getName () const
{
  return (getLevel() == 1) ? mId : mName;
}


/*
 * @return the math of this FunctionDefinition.
 */
const ASTNode*
FunctionDefinition::getMath () const
{
  return mMath;
}


/*
 * @return true if the id of this SBML object is set, false
 * otherwise.
 */
bool
FunctionDefinition::isSetId () const
{
  return (mId.empty() == false);
}


/*
 * @return true if the name of this SBML object is set, false
 * otherwise.
 */
bool
FunctionDefinition::isSetName () const
{
  return (getLevel() == 1) ? (mId.empty() == false) : 
                            (mName.empty() == false);
}


/*
 * @return true if the math of this FunctionDefinition is set, false
 * otherwise.
 */
bool
FunctionDefinition::isSetMath () const
{
  return (mMath != NULL);
}

/*
 * Sets the id of this SBML object to a copy of sid.
 */
int
FunctionDefinition::setId (const std::string& sid)
{
  /* since the setId function has been used as an
   * alias for setName we cant require it to only
   * be used on a L2 model
   */
/*  if (getLevel() == 1)
  {
    return LIBSBML_UNEXPECTED_ATTRIBUTE;
  }
*/
  if (&(sid) == NULL)
  {
    return LIBSBML_INVALID_ATTRIBUTE_VALUE;
  }
  else if (!(SyntaxChecker::isValidInternalSId(sid)))
  {
    return LIBSBML_INVALID_ATTRIBUTE_VALUE;
  }
  else
  {
    mId = sid;
    return LIBSBML_OPERATION_SUCCESS;
  }
}


/*
 * Sets the name of this SBML object to a copy of name.
 */
int
FunctionDefinition::setName (const std::string& name)
{
  /* if this is setting an L2 name the type is string
   * whereas if it is setting an L1 name its type is SId
   */
  if (&(name) == NULL)
  {
    return LIBSBML_INVALID_ATTRIBUTE_VALUE;
  }
  else if (getLevel() == 1)
  {
    if (!(SyntaxChecker::isValidInternalSId(name)))
    {
      return LIBSBML_INVALID_ATTRIBUTE_VALUE;
    }
    else
    {
      mId = name;
      return LIBSBML_OPERATION_SUCCESS;
    }
  }
  else
  {
    mName = name;
    return LIBSBML_OPERATION_SUCCESS;
  }
}


/*
 * Sets the math of this FunctionDefinition to the given ASTNode.
 */
int
FunctionDefinition::setMath (const ASTNode* math)
{
  if (mMath == math) 
  {
    return LIBSBML_OPERATION_SUCCESS;
  }
  else if (math == NULL)
  {
    delete mMath;
    mMath = NULL;
    return LIBSBML_OPERATION_SUCCESS;
  }
  else if (!(math->isWellFormedASTNode()))
  {
    return LIBSBML_INVALID_OBJECT;
  }
  else
  {
    delete mMath;
    mMath = (math != NULL) ? math->deepCopy() : NULL;
    if (mMath != NULL) mMath->setParentSBMLObject(this);
    return LIBSBML_OPERATION_SUCCESS;
  }
}


/*
 * Unsets the name of this SBML object.
 */
int
FunctionDefinition::unsetName ()
{
  if (getLevel() == 1) 
  {
    mId.erase();
  }
  else 
  {
    mName.erase();
  }

  if (getLevel() == 1 && mId.empty())
  {
    return LIBSBML_OPERATION_SUCCESS;
  }
  else if (mName.empty())
  {
    return LIBSBML_OPERATION_SUCCESS;
  }
  else
  {
    return LIBSBML_OPERATION_FAILED;
  }
}


/*
 * @return the nth argument (bound variable) passed to this
 * FunctionDefinition.
 */
const ASTNode*
FunctionDefinition::getArgument (unsigned int n) const
{
  return (n < getNumArguments()) ? mMath->getChild(n) : NULL;
}


/*
 * @return the argument (bound variable) in this FunctionDefinition with
 * the given name or @c NULL if no such argument exists.
 */
const ASTNode*
FunctionDefinition::getArgument (const std::string& name) const
{
  const char*    cname = name.c_str();
  const ASTNode* found = NULL;


  for (unsigned int n = 0; n < getNumArguments(); ++n)
  {
    const ASTNode* node = getArgument(n);

    if (node != NULL && node->isName() && !strcmp(node->getName(), cname))
    {
      found = node;
      break;
    }
  }

  return found;
}


/*
 * @return the body of this FunctionDefinition, or @c NULL if no body is
 * defined.
 */
const ASTNode*
FunctionDefinition::getBody () const
{
  if (mMath == NULL) return NULL;
  /* if the math is not a lambda this function can cause issues
   * elsewhere, technically if the math is not a lambda
   * function the body is NULL
   */
  if (!(mMath->isLambda())) return NULL;

  unsigned int nc = mMath->getNumChildren();
  /* here we do actually need to look at whether something is a bvar
   * and not just assume that the last child is a function body 
   * it should be BUT it might not be
   */

  if (nc > 0 && !(mMath->getChild(nc-1)->isBvar()))
  {
    return mMath->getChild(nc-1);
  }
  else
  {
    return NULL;
  }
}


/*
 * @return the body of this FunctionDefinition, or @c NULL if no body is
 * defined.
 */
ASTNode*
FunctionDefinition::getBody ()
{
   if (mMath == NULL) return NULL;

  /* if the math is not a lambda this function can cause issues
   * elsewhere, technically if the math is not a lambda
   * function the body is NULL
   */
  if (!(mMath->isLambda())) return NULL;

  unsigned int nc = mMath->getNumChildren();
  /* here we do actually need to look at whether something is a bvar
   * and not just assume that the last child is a function body 
   * it should be BUT it might not be
   */

  if (nc > 0 && !(mMath->getChild(nc-1)->isBvar()))
  {
    return mMath->getChild(nc-1);
  }
  else
  {
    return NULL;
  }
}


/*
 * @return the number of arguments (bound variables) that must be passed
 * to this FunctionDefinition.
 */
unsigned int
FunctionDefinition::getNumArguments () const
{
  /* if the math is not a lambda this function can cause issues
   * elsewhere, technically if the math is not a lambda
   * function there are no arguments
   */
  if ( !isSetMath()
    || !(mMath->isLambda())
    || mMath->getNumChildren() == 0) 
    return 0;
  else 
  {
    /* here we do actually need to look at whether something is a bvar
     * and not just assume that the last child is a function body 
     */

    unsigned int num = mMath->getNumChildren();
    if (mMath->getChild(num-1)->isBvar())
      return num;
    else
      return num - 1;
  }
}


/*
 * @return the typecode (int) of this SBML object or SBML_UNKNOWN
 * (default).
 *
 * @see getElementName()
 */
int
FunctionDefinition::getTypeCode () const
{
  return SBML_FUNCTION_DEFINITION;
}


/*
 * @return the name of this element ie "functionDefinition".
 */
const string&
FunctionDefinition::getElementName () const
{
  static const string name = "functionDefinition";
  return name;
}


bool 
FunctionDefinition::hasRequiredAttributes() const
{
  bool allPresent = true;

  /* required attributes for functionDefinition: id */

  if (!isSetId())
    allPresent = false;

  return allPresent;
}


bool 
FunctionDefinition::hasRequiredElements() const
{
  bool allPresent = true;

  /* required attributes for functionDefinition: math */

  if (!isSetMath())
    allPresent = false;

  return allPresent;
}


/** @cond doxygen-libsbml-internal */
/*
 * Subclasses should override this method to read (and store) XHTML,
 * MathML, etc. directly from the XMLInputStream.
 *
 * @return true if the subclass read from the stream, false otherwise.
 */
bool
FunctionDefinition::readOtherXML (XMLInputStream& stream)
{
  bool          read = false;
  const string& name = stream.peek().getName();

  if (name == "math")
  {
    // if this is level 1 there shouldnt be any math!!!
    if (getLevel() == 1) 
    {
      logError(NotSchemaConformant, getLevel(), getVersion(),
	       "SBML Level 1 does not support MathML.");
      delete mMath;
      return false;
    }


    if (mMath != NULL)
    {
      if (getLevel() < 3) 
      {
        logError(NotSchemaConformant, getLevel(), getVersion(),
	        "Only one <math> element is permitted inside a "
	        "particular containing element.");
      }
      else
      {
        logError(OneMathElementPerFunc, getLevel(), getVersion());
      }
    }
    /* check for MathML namespace 
     * this may be explicitly declared here
     * or implicitly declared on the whole document
     */
    const XMLToken elem = stream.peek();
    const std::string prefix = checkMathMLNamespace(elem);

    delete mMath;
    mMath = readMathML(stream, prefix);
    if (mMath != NULL) mMath->setParentSBMLObject(this);
    read  = true;
  }

  /* ------------------------------
   *
   *   (EXTENSION)
   *
   * ------------------------------ */
  if ( SBase::readOtherXML(stream) )
    read = true;

  return read;
}
/** @endcond */


/** @cond doxygen-libsbml-internal */
/**
 * Subclasses should override this method to get the list of
 * expected attributes.
 * This function is invoked from corresponding readAttributes()
 * function.
 */
void
FunctionDefinition::addExpectedAttributes(ExpectedAttributes& attributes)
{
  SBase::addExpectedAttributes(attributes);

  attributes.add("name");
  attributes.add("id");

  const unsigned int level = getLevel();
  const unsigned int version = getVersion();

  if (level == 2 && version == 2)
  {
    attributes.add("sboTerm");
  }

}

/*
 * Subclasses should override this method to read values from the given
 * XMLAttributes set into their specific fields.  Be sure to call your
 * parents implementation of this method as well.
 */
void
FunctionDefinition::readAttributes (const XMLAttributes& attributes,
                                    const ExpectedAttributes& expectedAttributes)
{
  const unsigned int level   = getLevel  ();
  const unsigned int version = getVersion();

  SBase::readAttributes(attributes, expectedAttributes);

  switch (level)
  {
  case 1:
    logError(NotSchemaConformant, level, version,
	      "FunctionDefinition is not a valid component for this level/version.");
    break;
  case 2:
    readL2Attributes(attributes);
    break;
  case 3:
  default:
    readL3Attributes(attributes);
    break;
  }
}
/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * Subclasses should override this method to read values from the given
 * XMLAttributes set into their specific fields.  Be sure to call your
 * parents implementation of this method as well.
 */
void
FunctionDefinition::readL2Attributes (const XMLAttributes& attributes)
{
  const unsigned int level = getLevel();
  const unsigned int version = getVersion();

  //
  // id: SId  { use="required" }  (L2v1 ->)
  //
  bool assigned;
  assigned = attributes.readInto("id", mId, getErrorLog(), true);
  if (assigned && mId.size() == 0)
  {
    logEmptyString("id", level, version, "<functionDefinition>");
  }
  if (!SyntaxChecker::isValidInternalSId(mId)) logError(InvalidIdSyntax);

  //
  // name: string  { use="optional" }  (L2v1 ->)
  //
  attributes.readInto("name", mName);

  //
  // sboTerm: SBOTerm { use="optional" }  (L2v2 ->)
  //
  if (version == 2)
    mSBOTerm = SBO::readTerm(attributes, this->getErrorLog(), level, version);

}
/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * Subclasses should override this method to read values from the given
 * XMLAttributes set into their specific fields.  Be sure to call your
 * parents implementation of this method as well.
 */
void
FunctionDefinition::readL3Attributes (const XMLAttributes& attributes)
{
  const unsigned int level = getLevel();
  const unsigned int version = getVersion();

  //
  // id: SId  { use="required" }  (L2v1 ->)
  //
  bool assigned;
  assigned = attributes.readInto("id", mId, getErrorLog());
  if (!assigned)
  {
    getErrorLog()->logError(AllowedAttributesOnFunc, level, version);
  }
  if (assigned && mId.size() == 0)
  {
    logEmptyString("id", level, version, "<functionDefinition>");
  }
  if (!SyntaxChecker::isValidInternalSId(mId)) logError(InvalidIdSyntax);

  //
  // name: string  { use="optional" }  (L2v1 ->)
  //
  attributes.readInto("name", mName);

}
/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * Subclasses should override this method to write their XML attributes
 * to the XMLOutputStream.  Be sure to call your parents implementation
 * of this method as well.
 */
void
FunctionDefinition::writeAttributes (XMLOutputStream& stream) const
{
  const unsigned int level = getLevel();
  const unsigned int version = getVersion();

  /* invalid level/version */
  if (level < 2)
  {
    return;
  }

  SBase::writeAttributes(stream);

  //
  // sboTerm: SBOTerm { use="optional" }  (L2v2 ->)
  //
  // sboTerm for L2V3 or later is written in SBase::writeAttributes()
  //
  if ( (level == 2) && (version == 2) )
  {
    SBO::writeTerm(stream, mSBOTerm);
  }

  //
  // id: SId  { use="required" }  (L2v1 ->)
  //
  stream.writeAttribute("id", mId);

  //
  // name: string  { use="optional" }  (L2v1 ->)
  //
  stream.writeAttribute("name", mName);

  //
  // (EXTENSION)
  //
  SBase::writeExtensionAttributes(stream);

}
/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * Subclasses should override this method to write out their contained
 * SBML objects as XML elements.  Be sure to call your parents
 * implementation of this method as well.
 */
void
FunctionDefinition::writeElements (XMLOutputStream& stream) const
{
  SBase::writeElements(stream);

  if (mMath) writeMathML(mMath, stream);

  //
  // (EXTENSION)
  //
  SBase::writeExtensionElements(stream);
}
/** @endcond */


/*
 * Creates a new ListOfFunctionDefinitions items.
 */
ListOfFunctionDefinitions::ListOfFunctionDefinitions (unsigned int level, unsigned int version)
: ListOf(level,version)
{
}


/*
 * Creates a new ListOfFunctionDefinitions items.
 */
ListOfFunctionDefinitions::ListOfFunctionDefinitions (SBMLNamespaces* sbmlns)
: ListOf(sbmlns)
{
}


/*
 * @return a (deep) copy of this ListOfFunctionDefinitions.
 */
ListOfFunctionDefinitions*
ListOfFunctionDefinitions::clone () const
{
  return new ListOfFunctionDefinitions(*this);
}


/*
 * @return the typecode (int) of SBML objects contained in this ListOf or
 * SBML_UNKNOWN (default).
 */
int
ListOfFunctionDefinitions::getItemTypeCode () const
{
  return SBML_FUNCTION_DEFINITION;
}


/*
 * @return the name of this element ie "listOfFunctionDefinitions".
 */
const string&
ListOfFunctionDefinitions::getElementName () const
{
  static const string name = "listOfFunctionDefinitions";
  return name;
}


/* return nth item in list */
FunctionDefinition *
ListOfFunctionDefinitions::get(unsigned int n)
{
  return static_cast<FunctionDefinition*>(ListOf::get(n));
}


/* return nth item in list */
const FunctionDefinition *
ListOfFunctionDefinitions::get(unsigned int n) const
{
  return static_cast<const FunctionDefinition*>(ListOf::get(n));
}


/**
 * Used by ListOf::get() to lookup an SBase based by its id.
 */
struct IdEqFD : public unary_function<SBase*, bool>
{
  const string& id;

  IdEqFD (const string& id) : id(id) { }
  bool operator() (SBase* sb) 
       { return static_cast <FunctionDefinition *> (sb)->getId() == id; }
};


/* return item by id */
FunctionDefinition*
ListOfFunctionDefinitions::get (const std::string& sid)
{
  return const_cast<FunctionDefinition*>( 
    static_cast<const ListOfFunctionDefinitions&>(*this).get(sid) );
}


/* return item by id */
const FunctionDefinition*
ListOfFunctionDefinitions::get (const std::string& sid) const
{
  vector<SBase*>::const_iterator result;

  if (&(sid) == NULL)
  {
    return NULL;
  }
  else
  {
    result = find_if( mItems.begin(), mItems.end(), IdEqFD(sid) );
    return (result == mItems.end()) ? NULL : 
                               static_cast <FunctionDefinition*> (*result);
  }
}


/* Removes the nth item from this list */
FunctionDefinition*
ListOfFunctionDefinitions::remove (unsigned int n)
{
   return static_cast<FunctionDefinition*>(ListOf::remove(n));
}


/* Removes item in this list by id */
FunctionDefinition*
ListOfFunctionDefinitions::remove (const std::string& sid)
{
  SBase* item = NULL;
  vector<SBase*>::iterator result;

  if (&(sid) != NULL)
  {
    result = find_if( mItems.begin(), mItems.end(), IdEqFD(sid) );

    if (result != mItems.end())
    {
      item = *result;
      mItems.erase(result);
    }
  }

  return static_cast <FunctionDefinition*> (item);
}


/** @cond doxygen-libsbml-internal */
/*
 * @return the ordinal position of the element with respect to its siblings
 * or -1 (default) to indicate the position is not significant.
 */
int
ListOfFunctionDefinitions::getElementPosition () const
{
  return 1;
}
/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * @return the SBML object corresponding to next XMLToken in the
 * XMLInputStream or @c NULL if the token was not recognized.
 */
SBase*
ListOfFunctionDefinitions::createObject (XMLInputStream& stream)
{
  const string& name   = stream.peek().getName();
  SBase*        object = NULL;


  if (name == "functionDefinition")
  {
    try
    {
      object = new FunctionDefinition(getSBMLNamespaces());
    }
    catch (SBMLConstructorException*)
    {
      object = new FunctionDefinition(SBMLDocument::getDefaultLevel(),
        SBMLDocument::getDefaultVersion());
    }
    catch ( ... )
    {
      object = new FunctionDefinition(SBMLDocument::getDefaultLevel(),
        SBMLDocument::getDefaultVersion());
    }
    
    if (object != NULL) mItems.push_back(object);
  }

  return object;
}
/** @endcond */


/** @cond doxygen-c-only */


/**
 * Creates a new FunctionDefinition_t structure using the given SBML @p level
 * and @p version values.
 *
 * @param level an unsigned int, the SBML Level to assign to this
 * FunctionDefinition
 *
 * @param version an unsigned int, the SBML Version to assign to this
 * FunctionDefinition
 *
 * @return a pointer to the newly created FunctionDefinition_t structure.
 *
 * @note Once a FunctionDefinition has been added to an SBMLDocument, the @p
 * level and @p version for the document @em override those used to create
 * the FunctionDefinition.  Despite this, the ability to supply the values at
 * creation time is an important aid to creating valid SBML.  Knowledge of
 * the intended SBML Level and Version  determine whether it is valid to
 * assign a particular value to an attribute, or whether it is valid to add
 * an object to an existing SBMLDocument.
 */
LIBSBML_EXTERN
FunctionDefinition_t *
FunctionDefinition_create (unsigned int level, unsigned int version)
{
  try
  {
    FunctionDefinition* obj = new FunctionDefinition(level,version);
    return obj;
  }
  catch (SBMLConstructorException)
  {
    return NULL;
  }
}


/**
 * Creates a new FunctionDefinition_t structure using the given
 * SBMLNamespaces_t structure.
 *
 * @param sbmlns SBMLNamespaces, a pointer to an SBMLNamespaces structure
 * to assign to this FunctionDefinition
 *
 * @return a pointer to the newly created FunctionDefinition_t structure.
 *
 * @note Once a FunctionDefinition has been added to an SBMLDocument, the
 * @p sbmlns namespaces for the document @em override those used to create
 * the FunctionDefinition.  Despite this, the ability to supply the values at 
 * creation time is an important aid to creating valid SBML.  Knowledge of the 
 * intended SBML Level and Version determine whether it is valid to assign a 
 * particular value to an attribute, or whether it is valid to add an object to 
 * an existing SBMLDocument.
 */
LIBSBML_EXTERN
FunctionDefinition_t *
FunctionDefinition_createWithNS (SBMLNamespaces_t* sbmlns)
{
  try
  {
    FunctionDefinition* obj = new FunctionDefinition(sbmlns);
    return obj;
  }
  catch (SBMLConstructorException)
  {
    return NULL;
  }
}


/**
 * Frees the given FunctionDefinition.
 *
 * @param fd the FunctionDefinition_t structure
 */
LIBSBML_EXTERN
void
FunctionDefinition_free (FunctionDefinition_t *fd)
{
  if (fd != NULL)
  delete fd;
}


/**
 * Creates a deep copy of the given FunctionDefinition_t structure
 * 
 * @param fd the FunctionDefinition_t structure to be copied
 * 
 * @return a (deep) copy of the given FunctionDefinition_t structure.
 */
LIBSBML_EXTERN
FunctionDefinition_t *
FunctionDefinition_clone (const FunctionDefinition_t* fd)
{
  return (fd != NULL) ? static_cast<FunctionDefinition*>( fd->clone() ) : NULL;
}


/**
 * Returns a list of XMLNamespaces_t associated with this FunctionDefinition_t
 * structure.
 *
 * @param fd the FunctionDefinition_t structure
 * 
 * @return pointer to the XMLNamespaces_t structure associated with 
 * this SBML object
 */
LIBSBML_EXTERN
const XMLNamespaces_t *
FunctionDefinition_getNamespaces(FunctionDefinition_t *fd)
{
  return (fd != NULL) ? fd->getNamespaces() : NULL;
}


/**
 * Get the identifier of the given FunctionDefinition_t structure.
 *
 * @param fd the FunctionDefinition_t structure
 * 
 * @return the value of the "id" attribute of this FunctionDefinition_t
 * structure.
 */
LIBSBML_EXTERN
const char *
FunctionDefinition_getId (const FunctionDefinition_t *fd)
{
  return (fd != NULL && fd->isSetId()) ? fd->getId().c_str() : NULL;
}


/**
 * Get the name of the given FunctionDefinition_t structure.
 *
 * @param fd the FunctionDefinition_t structure
 *
 * @return the name of this FunctionDefinition_t structure.
 */
LIBSBML_EXTERN
const char *
FunctionDefinition_getName (const FunctionDefinition_t *fd)
{
  return (fd != NULL && fd->isSetName()) ? fd->getName().c_str() : NULL;
}


/**
 * Get the mathematical formula implemented by the given function.
 *
 * @param fd the FunctionDefinition_t structure
 * 
 * @return an ASTNode_t tree representing the mathematical formula of this
 * FunctionDefinition_t structure.
 */
LIBSBML_EXTERN
const ASTNode_t *
FunctionDefinition_getMath (const FunctionDefinition_t *fd)
{
  return (fd != NULL) ? fd->getMath() : NULL;
}


/**
 * Predicate returning @c true or @c false depending on whether the given
 * Compartment_t structure's "id" attribute is set.
 *
 * @param fd the FunctionDefinition_t structure
 *
 * @return nonzero if the "id" attribute of the FunctionDefinition_t
 * structure is set, zero (0) otherwise.
 */
LIBSBML_EXTERN
int
FunctionDefinition_isSetId (const FunctionDefinition_t *fd)
{
  return (fd != NULL) ? static_cast<int>( fd->isSetId() ) : 0;
}


/**
 * Predicate returning @c true or @c false depending on whether the given
 * Compartment_t structure's "name" attribute is set.
 *
 * @param fd the FunctionDefinition_t structure
 *
 * @return nonzero if the "name" attribute of the FunctionDefinition_t
 * structure is set, zero (0) otherwise.
 */
LIBSBML_EXTERN
int
FunctionDefinition_isSetName (const FunctionDefinition_t *fd)
{
  return (fd != NULL) ? static_cast<int>( fd->isSetName() ) : 0;
}


/**
 * Predicate returning @c true or @c false depending on whether the given
 * Compartment_t structure's "math" subelement is set.
 *
 * @param fd the FunctionDefinition_t structure
 *
 * @return nonzero if the mathematical expression of this
 * FunctionDefinition is set, zero (0) otherwise.
 */
LIBSBML_EXTERN
int
FunctionDefinition_isSetMath (const FunctionDefinition_t *fd)
{
  return (fd != NULL) ? static_cast<int>( fd->isSetMath() ) : 0;
}


/**
 * Sets the value of the "id" attribute of a FunctionDefinition_t structure.
 *
 * @param fd the FunctionDefinition_t structure to set.
 *
 * @param sid the identifier to assign to the "id" attribute of @p fd
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_INVALID_ATTRIBUTE_VALUE
 *
 * @note Using this function with an id of NULL is equivalent to
 * unsetting the "id" attribute.
 */
LIBSBML_EXTERN
int
FunctionDefinition_setId (FunctionDefinition_t *fd, const char *sid)
{
  if (fd != NULL)
    return (sid == NULL) ? fd->setId("") : fd->setId(sid);
  else
    return LIBSBML_INVALID_OBJECT;
}


/**
 * Sets the value of the "name" attribute of a FunctionDefinition_t structure.
 *
 * @param fd the FunctionDefinition_t structure to set.
 *
 * @param name the identifier to assign to the "name" attribute of @p fd
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_INVALID_ATTRIBUTE_VALUE
 *
 * @note Using this function with the name set to NULL is equivalent to
 * unsetting the "name" attribute.
 */
LIBSBML_EXTERN
int
FunctionDefinition_setName (FunctionDefinition_t *fd, const char *name)
{
  if (fd != NULL)
    return (name == NULL) ? fd->unsetName() : fd->setName(name);
  else
    return LIBSBML_INVALID_OBJECT;
}


/**
 * Sets the "math" subelement of a given FunctionDefinition_t structure.
 *
 * The ASTNode_t structure given in @p math is copied.
 *
 * @param fd the FunctionDefinition_t structure to set.
 *
 * @param math the ASTNode_t structure to copy and assign to the "math"
 * subelement of the given FunctionDefinition_t structure
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_INVALID_OBJECT
 */
LIBSBML_EXTERN
int
FunctionDefinition_setMath (FunctionDefinition_t *fd, const ASTNode_t *math)
{
  if (fd != NULL)
    return fd->setMath(math);
  else
    return LIBSBML_INVALID_OBJECT;
}


/**
 * Unsets the "name" attribute of the given FunctionDefinition_t structure.
 * 
 * @param fd the FunctionDefinition_t structure
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_OPERATION_FAILED
 */
LIBSBML_EXTERN
int
FunctionDefinition_unsetName (FunctionDefinition_t *fd)
{
  if (fd != NULL)
    return fd->unsetName();
  else
    return LIBSBML_INVALID_OBJECT;
}


/**
 * Get the nth argument (bound variable) to the given FunctionDefinition_t
 * structure.
 * 
 * @param fd the FunctionDefinition_t structure
 *
 * @param n the index of the argument to return
 *
 * @return an ASTNode_t tree structure for the argument.
 */
LIBSBML_EXTERN
const ASTNode_t *
FunctionDefinition_getArgument (const FunctionDefinition_t *fd, unsigned int n)
{
  return (fd != NULL) ? fd->getArgument(n) : NULL;
}


/**
 * Get the argument named @p name to the given FunctionDefinition_t structure.
 *
 * @param fd the FunctionDefinition_t structure
 *
 * @param name the exact name (case-sensitive) of the sought-after argument
 *
 * @return an ASTNode_t structure representing the argument (bound
 * variable)
 */
LIBSBML_EXTERN
const ASTNode_t *
FunctionDefinition_getArgumentByName ( FunctionDefinition_t *fd,
                                       const char *name )
{
  return (fd != NULL) ? fd->getArgument(name != NULL ? name : "") : NULL;
}


/**
 * Get the mathematical expression that constitutes the body of the given
 * function definition.
 *
 * @param fd the FunctionDefinition_t structure
 * 
 * @return an ASTNode_t tree that is the "math" subelement" of this
 * FunctionDefinition_t structure
 */
LIBSBML_EXTERN
const ASTNode_t *
FunctionDefinition_getBody (const FunctionDefinition_t *fd)
{
  return (fd != NULL) ? fd->getBody() : NULL;
}


/**
 * Get the number of arguments that the given function definition takes.
 *
 * @param fd the FunctionDefinition_t structure
 * 
 * @return the number of arguments (bound variables) that must be passed
 * to this FunctionDefinition_t structure.
 */
LIBSBML_EXTERN
unsigned int
FunctionDefinition_getNumArguments (const FunctionDefinition_t *fd)
{
  return (fd != NULL) ? fd->getNumArguments() : SBML_INT_MAX;
}



/**
 * @return item in this ListOfFunctionDefinition with the given id or @c NULL if no such
 * item exists.
 */
LIBSBML_EXTERN
FunctionDefinition_t *
ListOfFunctionDefinitions_getById (ListOf_t *lo, const char *sid)
{
  if (lo != NULL)
    return (sid != NULL) ? 
      static_cast <ListOfFunctionDefinitions *> (lo)->get(sid) : NULL;
  else
    return NULL;
}


/**
 * Removes item in this ListOf items with the given id or @c NULL if no such
 * item exists.  The caller owns the returned item and is responsible for
 * deleting it.
 */
LIBSBML_EXTERN
FunctionDefinition_t *
ListOfFunctionDefinitions_removeById (ListOf_t *lo, const char *sid)
{
  if (lo != NULL)
    return (sid != NULL) ? 
      static_cast <ListOfFunctionDefinitions *> (lo)->remove(sid) : NULL;
  else
    return NULL;
}

/** @endcond */

LIBSBML_CPP_NAMESPACE_END

