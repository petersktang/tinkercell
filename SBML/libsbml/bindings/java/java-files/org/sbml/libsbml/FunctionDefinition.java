/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.sbml.libsbml;

/** 
 * LibSBML implementation of SBML's FunctionDefinition construct.
 * <p>
 * The {@link FunctionDefinition} structure associates an identifier with a
 * function definition.  This identifier can then be used as the function
 * called in subsequent MathML content elsewhere in an SBML model.
 * <p>
 * {@link FunctionDefinition} has one required attribute, 'id', to give the
 * function a unique identifier by which other parts of an SBML model
 * definition can refer to it.  A {@link FunctionDefinition} instance can also have
 * an optional 'name' attribute of type <code>string</code>.  Identifiers and names
 * must be used according to the guidelines described in the SBML
 * specification (e.g., Section 3.3 in the Level 2 Version 4
 * specification).
 * <p>
 * {@link FunctionDefinition} has a required 'math' subelement containing a MathML
 * expression defining the function body.  The content of this element can
 * only be a MathML 'lambda' element.  The 'lambda' element must begin with
 * zero or more 'bvar' elements, followed by any other of the elements in
 * the MathML subset allowed in SBML Level 2 <em>except</em> 'lambda' (i.e., a
 * 'lambda' element cannot contain another 'lambda' element).  This is the
 * only place in SBML where a 'lambda' element can be used.  The function
 * defined by a {@link FunctionDefinition} is only available for use in other
 * MathML elements that <em>follow</em> the {@link FunctionDefinition} definition in the
 * model.  (These restrictions prevent recursive and mutually-recursive
 * functions from being expressed.)
 * <p>
 * A further restriction on the content of 'math' is that it cannot contain
 * references to variables other than the variables declared to the
 * 'lambda' itself.  That is, the contents of MathML 'ci' elements inside
 * the body of the 'lambda' can only be the variables declared by its
 * 'bvar' elements, or the identifiers of other {@link FunctionDefinition}
 * instances earlier in the model.  This means must be written so that all
 * variables or parameters used in the MathML content are passed to them
 * via their function parameters.
 * <p>
 * @note Function definitions (also informally known as user-defined
 * functions) were introduced in SBML Level 2.  They have purposefully
 * limited capabilities.  A function cannot reference parameters or other
 * model quantities outside of itself; values must be passed as parameters
 * to the function.  Moreover, recursive and mutually-recursive functions
 * are not permitted.  The purpose of these limitations is to balance power
 * against complexity of implementation.  With the restrictions as they
 * are, function definitions could be implemented as textual
 * substitutions&mdash;they are simply macros.  Software implementations
 * therefore do not need the full function-definition machinery typically
 * associated with programming languages.
 * <p>
 * @note Another important point to note is {@link FunctionDefinition} does not
 * have a separate attribute for defining the units of the value returned
 * by the function.  The units associated with the function's return value,
 * when the function is called from within MathML expressions elsewhere in
 * SBML, are simply the overall units of the expression in
 * {@link FunctionDefinition}'s 'math' subelement when applied to the arguments
 * supplied in the call to the function.  Ascertaining these units requires
 * performing dimensional analysis on the expression.  (Readers may wonder
 * why there is no attribute.  The reason is that having a separate
 * attribute for declaring the units would not only be redundant, but also
 * lead to the potential for having conflicting information.  In the case
 * of a conflict between the declared units and those of the value actually
 * returned by the function, the only logical resolution rule would be to
 * assume that the correct units are those of the expression anyway.)
 * <p>
 * <!---------------------------------------------------------------------- -->
 * <p>
 */

public class FunctionDefinition extends SBase {
   private long swigCPtr;

   protected FunctionDefinition(long cPtr, boolean cMemoryOwn)
   {
     super(libsbmlJNI.SWIGFunctionDefinitionUpcast(cPtr), cMemoryOwn);
     swigCPtr = cPtr;
   }

   protected static long getCPtr(FunctionDefinition obj)
   {
     return (obj == null) ? 0 : obj.swigCPtr;
   }

   protected static long getCPtrAndDisown (FunctionDefinition obj)
   {
     long ptr = 0;

     if (obj != null)
     {
       ptr             = obj.swigCPtr;
       obj.swigCMemOwn = false;
     }

     return ptr;
   }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        libsbmlJNI.delete_FunctionDefinition(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  
  /**
   * Creates a new {@link FunctionDefinition} using the given SBML <code>level</code> and <code>version</code>
   * values.
   * <p>
   * @param level a long integer, the SBML Level to assign to this {@link FunctionDefinition}
   * <p>
   * @param version a long integer, the SBML Version to assign to this
   * {@link FunctionDefinition}
   * <p>
   * @note Once a {@link FunctionDefinition} has been added to an {@link SBMLDocument}, the <code>level</code>,
   * <code>version</code> for the document <em>override</em> those used
   * to create the {@link FunctionDefinition}.  Despite this, the ability to supply the values
   * at creation time is an important aid to creating valid SBML.  Knowledge of
   * the intented SBML Level and Version determine whether it is valid to
   * assign a particular value to an attribute, or whether it is valid to add
   * an object to an existing {@link SBMLDocument}.
   */
 public FunctionDefinition(long level, long version) throws org.sbml.libsbml.SBMLConstructorException {
    this(libsbmlJNI.new_FunctionDefinition__SWIG_0(level, version), true);
  }

  
  /**
   * Creates a new {@link FunctionDefinition} using the given {@link SBMLNamespaces} object
   * <code>sbmlns</code>.
   * <p>
   * The {@link SBMLNamespaces} object encapsulates SBML Level/Version/namespaces
   * information.  It is used to communicate the SBML Level, Version, and
   * (in Level&nbsp;3) packages used in addition to SBML Level&nbsp; Core.
   * A common approach to using this class constructor is to create an
   * {@link SBMLNamespaces} object somewhere in a program, once, then pass it to
   * object constructors such as this one when needed.
   * <p>
   * @param sbmlns an {@link SBMLNamespaces} object.
   * <p>
   * @note Once a {@link FunctionDefinition} has been added to an {@link SBMLDocument}, the <code>level</code>,
   * <code>version</code> and <code>xmlns</code> namespaces for the document <em>override</em> those used
   * to create the {@link FunctionDefinition}.  Despite this, the ability to supply the values
   * at creation time is an important aid to creating valid SBML.  Knowledge of
   * the intented SBML Level and Version determine whether it is valid to
   * assign a particular value to an attribute, or whether it is valid to add
   * an object to an existing {@link SBMLDocument}.
   */
 public FunctionDefinition(SBMLNamespaces sbmlns) throws org.sbml.libsbml.SBMLConstructorException {
    this(libsbmlJNI.new_FunctionDefinition__SWIG_1(SBMLNamespaces.getCPtr(sbmlns), sbmlns), true);
  }

  
  /**
   * Copy constructor; creates a copy of this {@link FunctionDefinition}.
   */
 public FunctionDefinition(FunctionDefinition orig) throws org.sbml.libsbml.SBMLConstructorException {
    this(libsbmlJNI.new_FunctionDefinition__SWIG_2(FunctionDefinition.getCPtr(orig), orig), true);
  }

  
  /**
   * Creates and returns a deep copy of this {@link FunctionDefinition}.
   * <p>
   * @return a (deep) copy of this {@link FunctionDefinition}.
   */
 public FunctionDefinition cloneObject() {
    long cPtr = libsbmlJNI.FunctionDefinition_cloneObject(swigCPtr, this);
    return (cPtr == 0) ? null : new FunctionDefinition(cPtr, true);
  }

  
  /**
   * Returns the value of the 'id' attribute of this {@link FunctionDefinition}.
   * <p>
   * @return the id of this {@link FunctionDefinition}.
   */
 public String getId() {
    return libsbmlJNI.FunctionDefinition_getId(swigCPtr, this);
  }

  
  /**
   * Returns the value of the 'name' attribute of this {@link FunctionDefinition}.
   * <p>
   * @return the name of this {@link FunctionDefinition}.
   */
 public String getName() {
    return libsbmlJNI.FunctionDefinition_getName(swigCPtr, this);
  }

  
  /**
   * Get the mathematical formula of this {@link FunctionDefinition}.
   * <p>
   * @return an {@link ASTNode}, the value of the 'math' subelement of this
   * {@link FunctionDefinition}
   */
 public ASTNode getMath() {
    long cPtr = libsbmlJNI.FunctionDefinition_getMath(swigCPtr, this);
    return (cPtr == 0) ? null : new ASTNode(cPtr, false);
  }

  
  /**
   * Predicate returning <code>true</code> or <code>false</code> depending on whether this
   * {@link FunctionDefinition}'s 'id' attribute has been set.
   * <p>
   * <em>Some words of explanation about the</em>
<code>set</code>/<code>unset</code>/<code>isSet</code> <em>methods</em>:
SBML Levels 1 and 2 define certain attributes on some classes of objects as
optional.  This requires an application to be careful about the distinction
between two cases: (1) a given attribute has <em>never</em> been set to a
value, and therefore should be assumed to have the SBML-defined default
value, and (2) a given attribute has been set to a value, but the value
happens to be an empty string.  LibSBML supports these distinctions by
providing methods to set, unset, and query the status of attributes that
are optional.  The methods have names of the form
<code>set</code><i>Attribute</i><code>(...)</code>,
<code>unset</code><i>Attribute</i><code>()</code>, and
<code>isSet</code><i>Attribute</i><code>()</code>, where <i>Attribute</i>
is the the name of the optional attribute in question.

   * <p>
   * @return <code>true</code> if the 'id' attribute of this {@link FunctionDefinition} has been
   * set, <code>false</code> otherwise.
   */
 public boolean isSetId() {
    return libsbmlJNI.FunctionDefinition_isSetId(swigCPtr, this);
  }

  
  /**
   * Predicate returning <code>true</code> or <code>false</code> depending on whether this
   * {@link FunctionDefinition}'s 'name' attribute has been set.
   * <p>
   * <em>Some words of explanation about the</em>
<code>set</code>/<code>unset</code>/<code>isSet</code> <em>methods</em>:
SBML Levels 1 and 2 define certain attributes on some classes of objects as
optional.  This requires an application to be careful about the distinction
between two cases: (1) a given attribute has <em>never</em> been set to a
value, and therefore should be assumed to have the SBML-defined default
value, and (2) a given attribute has been set to a value, but the value
happens to be an empty string.  LibSBML supports these distinctions by
providing methods to set, unset, and query the status of attributes that
are optional.  The methods have names of the form
<code>set</code><i>Attribute</i><code>(...)</code>,
<code>unset</code><i>Attribute</i><code>()</code>, and
<code>isSet</code><i>Attribute</i><code>()</code>, where <i>Attribute</i>
is the the name of the optional attribute in question.

   * <p>
   * @return <code>true</code> if the 'name' attribute of this {@link FunctionDefinition} has been
   * set, <code>false</code> otherwise.
   */
 public boolean isSetName() {
    return libsbmlJNI.FunctionDefinition_isSetName(swigCPtr, this);
  }

  
  /**
   * Predicate returning <code>true</code> or <code>false</code> depending on whether this
   * {@link FunctionDefinition}'s 'math' subelement contains a value.
   * <p>
   * @return <code>true</code> if the 'math' for this {@link FunctionDefinition} has been set,
   * <code>false</code> otherwise.
   */
 public boolean isSetMath() {
    return libsbmlJNI.FunctionDefinition_isSetMath(swigCPtr, this);
  }

  
  /**
   * Sets the value of the 'id' attribute of this {@link FunctionDefinition}.
   * <p>
   * The string <code>sid</code> is copied.  Note that SBML has strict requirements
   * for the syntax of identifiers.  The following is summary of the
   * definition of the SBML identifier type <code>SId</code> (here expressed in an
   * extended form of BNF notation):
   * <div class='fragment'><pre>
   *   letter .= 'a'..'z','A'..'Z'
   *   digit  .= '0'..'9'
   *   idChar .= letter | digit | '_'
   *   SId    .= ( letter | '_' ) idChar</pre></div>
   * The equality of SBML identifiers is determined by an exact character
   * sequence match; i.e., comparisons must be performed in a
   * case-sensitive manner.  In addition, there are a few conditions for
   * the uniqueness of identifiers in an SBML model.  Please consult the
   * SBML specifications for the exact formulations.
   * <p>
   * <em>Some words of explanation about the</em>
<code>set</code>/<code>unset</code>/<code>isSet</code> <em>methods</em>:
SBML Levels 1 and 2 define certain attributes on some classes of objects as
optional.  This requires an application to be careful about the distinction
between two cases: (1) a given attribute has <em>never</em> been set to a
value, and therefore should be assumed to have the SBML-defined default
value, and (2) a given attribute has been set to a value, but the value
happens to be an empty string.  LibSBML supports these distinctions by
providing methods to set, unset, and query the status of attributes that
are optional.  The methods have names of the form
<code>set</code><i>Attribute</i><code>(...)</code>,
<code>unset</code><i>Attribute</i><code>()</code>, and
<code>isSet</code><i>Attribute</i><code>()</code>, where <i>Attribute</i>
is the the name of the optional attribute in question.

   * <p>
   * @param sid the string to use as the identifier of this {@link FunctionDefinition}
   * <p>
   * @return integer value indicating success/failure of the
   * function.   The possible values
   * returned by this function are:
   * <li> LIBSBML_OPERATION_SUCCESS
   * <li> LIBSBML_INVALID_ATTRIBUTE_VALUE
   */
 public int setId(String sid) {
    return libsbmlJNI.FunctionDefinition_setId(swigCPtr, this, sid);
  }

  
  /**
   * Sets the value of the 'name' attribute of this {@link FunctionDefinition}.
   * <p>
   * The string in <code>name</code> is copied.
   * <p>
   * <em>Some words of explanation about the</em>
<code>set</code>/<code>unset</code>/<code>isSet</code> <em>methods</em>:
SBML Levels 1 and 2 define certain attributes on some classes of objects as
optional.  This requires an application to be careful about the distinction
between two cases: (1) a given attribute has <em>never</em> been set to a
value, and therefore should be assumed to have the SBML-defined default
value, and (2) a given attribute has been set to a value, but the value
happens to be an empty string.  LibSBML supports these distinctions by
providing methods to set, unset, and query the status of attributes that
are optional.  The methods have names of the form
<code>set</code><i>Attribute</i><code>(...)</code>,
<code>unset</code><i>Attribute</i><code>()</code>, and
<code>isSet</code><i>Attribute</i><code>()</code>, where <i>Attribute</i>
is the the name of the optional attribute in question.

   * <p>
   * @param name the new name for the {@link FunctionDefinition}
   * <p>
   * @return integer value indicating success/failure of the
   * function.   The possible values
   * returned by this function are:
   * <li> LIBSBML_OPERATION_SUCCESS
   * <li> LIBSBML_INVALID_ATTRIBUTE_VALUE
   */
 public int setName(String name) {
    return libsbmlJNI.FunctionDefinition_setName(swigCPtr, this, name);
  }

  
  /**
   * Sets the 'math' subelement of this {@link FunctionDefinition} to the Abstract
   * Syntax Tree given in <code>math</code>.
   * <p>
   * @param math an AST containing the mathematical expression to
   * be used as the formula for this {@link FunctionDefinition}.
   * <p>
   * @return integer value indicating success/failure of the
   * function.   The possible values
   * returned by this function are:
   * <li> LIBSBML_OPERATION_SUCCESS
   * <li> LIBSBML_INVALID_OBJECT
   */
 public int setMath(ASTNode math) {
    return libsbmlJNI.FunctionDefinition_setMath(swigCPtr, this, ASTNode.getCPtr(math), math);
  }

  
  /**
   * Unsets the value of the 'name' attribute of this {@link FunctionDefinition}.
   * <p>
   * <em>Some words of explanation about the</em>
<code>set</code>/<code>unset</code>/<code>isSet</code> <em>methods</em>:
SBML Levels 1 and 2 define certain attributes on some classes of objects as
optional.  This requires an application to be careful about the distinction
between two cases: (1) a given attribute has <em>never</em> been set to a
value, and therefore should be assumed to have the SBML-defined default
value, and (2) a given attribute has been set to a value, but the value
happens to be an empty string.  LibSBML supports these distinctions by
providing methods to set, unset, and query the status of attributes that
are optional.  The methods have names of the form
<code>set</code><i>Attribute</i><code>(...)</code>,
<code>unset</code><i>Attribute</i><code>()</code>, and
<code>isSet</code><i>Attribute</i><code>()</code>, where <i>Attribute</i>
is the the name of the optional attribute in question.

   * <p>
   * @return integer value indicating success/failure of the
   * function.   The possible values
   * returned by this function are:
   * <li> LIBSBML_OPERATION_SUCCESS
   * <li> LIBSBML_OPERATION_FAILED
   */
 public int unsetName() {
    return libsbmlJNI.FunctionDefinition_unsetName(swigCPtr, this);
  }

  
  /**
   * Get the <code>n</code>th argument to this function.
   * <p>
   * Callers should first find out the number of arguments to the function
   * by calling getNumArguments().
   * <p>
   * @param n an integer index for the argument sought.
   * <p>
   * @return the nth argument (bound variable) passed to this
   * {@link FunctionDefinition}.
   * <p>
   * @see #getNumArguments()
   */
 public ASTNode getArgument(long n) {
    long cPtr = libsbmlJNI.FunctionDefinition_getArgument__SWIG_0(swigCPtr, this, n);
    return (cPtr == 0) ? null : new ASTNode(cPtr, false);
  }

  
  /**
   * Get the argument named <code>name</code> to this {@link FunctionDefinition}.
   * <p>
   * @param name the exact name (case-sensitive) of the sought-after
   * argument
   * <p>
   * @return the argument (bound variable) having the given name, or NULL if
   * no such argument exists.
   */
 public ASTNode getArgument(String name) {
    long cPtr = libsbmlJNI.FunctionDefinition_getArgument__SWIG_1(swigCPtr, this, name);
    return (cPtr == 0) ? null : new ASTNode(cPtr, false);
  }

  
  /**
   * Get the mathematical expression that is the body of this
   * {@link FunctionDefinition} object.
   * <p>
   * @return the body of this {@link FunctionDefinition} as an Abstract Syntax
   * Tree, or NULL if no body is defined.
   */
 public ASTNode getBody() {
    long cPtr = libsbmlJNI.FunctionDefinition_getBody__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new ASTNode(cPtr, false);
  }

  
  /**
   * Get the number of arguments (bound variables) taken by this
   * {@link FunctionDefinition}.
   * <p>
   * @return the number of arguments (bound variables) that must be passed
   * to this {@link FunctionDefinition}.
   */
 public long getNumArguments() {
    return libsbmlJNI.FunctionDefinition_getNumArguments(swigCPtr, this);
  }

  
  /**
   * Returns the libSBML type code for this SBML object.
   * <p>
   * LibSBML attaches an
   * identifying code to every kind of SBML object.  These are known as
   * <em>SBML type codes</em>.  In other languages, the set of type codes
   * is stored in an enumeration; in the Java language interface for
   * libSBML, the type codes are defined as static integer constants in
   * interface class {@link libsbmlConstants}.  The names of the type codes
   * all begin with the characters <code>SBML_</code>. 
   * <p>
   * @return the SBML type code for this object, or <code>SBML_UNKNOWN</code> (default).
   * <p>
   * @see #getElementName()
   */
 public int getTypeCode() {
    return libsbmlJNI.FunctionDefinition_getTypeCode(swigCPtr, this);
  }

  
  /**
   * Returns the XML element name of this object, which for
   * {@link FunctionDefinition}, is always <code>'functionDefinition'</code>.
   * <p>
   * @return the name of this element, i.e., <code>'functionDefinition'</code>.
   */
 public String getElementName() {
    return libsbmlJNI.FunctionDefinition_getElementName(swigCPtr, this);
  }

  
  /**
   * Predicate returning <code>true</code> or <code>false</code> depending on whether
   * all the required attributes for this {@link FunctionDefinition} object
   * have been set.
   * <p>
   * @note The required attributes for a {@link FunctionDefinition} object are:
   * id
   * <p>
   * @return a boolean value indicating whether all the required
   * attributes for this object have been defined.
   */
 public boolean hasRequiredAttributes() {
    return libsbmlJNI.FunctionDefinition_hasRequiredAttributes(swigCPtr, this);
  }

  
  /**
   * Predicate returning <code>true</code> or <code>false</code> depending on whether
   * all the required elements for this {@link FunctionDefinition} object
   * have been set.
   * <p>
   * @note The required elements for a {@link FunctionDefinition} object are:
   * math
   * <p>
   * @return a boolean value indicating whether all the required
   * elements for this object have been defined.
   */
 public boolean hasRequiredElements() {
    return libsbmlJNI.FunctionDefinition_hasRequiredElements(swigCPtr, this);
  }

}
