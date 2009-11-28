/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.sbml.libsbml;

/** 
 * LibSBML implementation of SBML's AlgebraicRule construct.
 * <p>
 * The rule type {@link AlgebraicRule} is derived from the parent class {@link Rule}.  It
 * is used to express equations that are neither assignments of model
 * variables nor rates of change.  {@link AlgebraicRule} does not add any
 * attributes to the basic {@link Rule}; its role is simply to distinguish this
 * case from the other cases.
 * <p>
 * In the context of a simulation, algebraic rules are in effect at all
 * times, <em>t</em> &#8805; <em>0</em>.  For purposes of evaluating
 * expressions that involve the delay 'csymbol' (see the SBML
 * specification), algebraic rules are considered to apply also at
 * <em>t</em> &#8804; <em>0</em>.  The SBML Level&nbsp;2 Version&nbsp;4
 * specification provides additional information about the semantics of
 * assignments, rules, and entity values for simulation time <em>t</em>
 * &#8804; <em>0</em>.
 * <p>
 * The ability to define arbitrary algebraic expressions in an SBML model
 * introduces the possibility that a model is mathematically overdetermined
 * by the overall system of equations constructed from its rules and
 * reactions.  An SBML model must not be overdetermined; see the
 * description of {@link Rule} and also the SBML Level&nbsp;2 Version&nbsp;4
 * specification.  An SBML model that does not contain {@link AlgebraicRule}
 * structures cannot be overdetermined.
 * <p>
 * Assessing whether a given continuous, deterministic, mathematical model
 * is overdetermined does not require dynamic analysis; it can be done by
 * analyzing the system of equations created from the model.  One approach
 * is to construct a bipartite graph in which one set of vertices
 * represents the variables and the other the set of vertices represents
 * the equations.  Place edges between vertices such that variables in the
 * system are linked to the equations that determine them.  For algebraic
 * equations, there will be edges between the equation and each variable
 * occurring in the equation.  For ordinary differential equations (such as
 * those defined by rate rules or implied by the reaction rate
 * definitions), there will be a single edge between the equation and the
 * variable determined by that differential equation.  A mathematical model
 * is overdetermined if the maximal matchings of the bipartite graph
 * contain disconnected vertexes representing equations.  (If one maximal
 * matching has this property, then all the maximal matchings will have
 * this property; i.e., it is only necessary to find one maximal matching.)
 * Appendix D of the SBML Level&nbsp;2 Version&nbsp;4 specification
 * describes a method of applying this procedure to specific SBML data
 * objects.
 * <p>
 * <h2>General summary of SBML rules</h2>
<p>
In SBML Level&nbsp;2, rules are separated into three subclasses for the
benefit of model analysis software.  The three subclasses are based on
the following three different possible functional forms (where <em>x</em> is
a variable, <em>f</em> is some arbitrary function returning a numerical
result, <b>V</b> is a vector of variables that does not include <em>x</em>,
and <b>W</b> is a vector of variables that may include <em>x</em>):

<p>
<center>
<table border='0' cellpadding='0' style='font-size: small'>
<tr><td width='120px'><em>Algebraic:</em></td><td width='250px'>left-hand side is zero</td><td><em>0 = f(<b>W</b>)</em></td></tr>
<tr><td><em>Assignment:</em></td><td>left-hand side is a scalar:</td><td><em>x = f(<b>V</b>)</em></td></tr>
<tr><td><em>Rate:</em></td><td>left-hand side is a rate-of-change:</td><td><em>dx/dt = f(<b>W</b>)</em></td></tr>
</table>
</center>

<p>
In their general form given above, there is little to distinguish
between <em>assignment</em> and <em>algebraic</em> rules.  They are treated as
separate cases for the following reasons:
<p>
<ul>
<li> <em>Assignment</em> rules can simply be evaluated to calculate
intermediate values for use in numerical methods.  They are statements
of equality that hold at all times.  (For assignments that are only
performed once, see {@link InitialAssignment}.)<p>

<li> SBML needs to place restrictions on assignment rules, for example
the restriction that assignment rules cannot contain algebraic loops.<p>

<li> Some simulators do not contain numerical solvers capable of solving
unconstrained algebraic equations, and providing more direct forms such
as assignment rules may enable those simulators to process models they
could not process if the same assignments were put in the form of
general algebraic equations;<p>

<li> Those simulators that <em>can</em> solve these algebraic equations make a
distinction between the different categories listed above; and<p>

<li> Some specialized numerical analyses of models may only be applicable
to models that do not contain <em>algebraic</em> rules.
</ul>

<p> The approach taken to covering these cases in SBML is to define an
abstract {@link Rule} structure containing a subelement, 'math', to hold the
right-hand side expression, then to derive subtypes of {@link Rule} that add
attributes to distinguish the cases of algebraic, assignment and rate
rules.  The 'math' subelement must contain a MathML expression defining the
mathematical formula of the rule.  This MathML formula must return a
numerical value.  The formula can be an arbitrary expression referencing
the variables and other entities in an SBML model.

<p> Each of the three subclasses of {@link Rule} (AssignmentRule, {@link AlgebraicRule},
{@link RateRule}) inherit the the 'math' subelement and other fields from {@link SBase}.
The {@link AssignmentRule} and {@link RateRule} classes add an additional attribute,
'variable'.  See the definitions of {@link AssignmentRule}, {@link AlgebraicRule} and
{@link RateRule} for details about the structure and interpretation of each one.

<h2>Additional restrictions on SBML rules</h2>

<p> An important design goal of SBML rule semantics is to ensure that a
model's simulation and analysis results will not be dependent on when or
how often rules are evaluated.  To achieve this, SBML needs to place two
restrictions on rule use.  The first concerns algebraic loops in the system
of assignments in a model, and the second concerns overdetermined systems.

<h3>A model must not contain algebraic loops</h3>

<p> The combined set of {@link InitialAssignment}, {@link AssignmentRule} and {@link KineticLaw}
objects in a model constitute a set of assignment statements that should be
considered as a whole.  (A {@link KineticLaw} object is counted as an assignment
because it assigns a value to the symbol contained in the 'id' attribute of
the {@link Reaction} object in which it is defined.)  This combined set of
assignment statements must not contain algebraic loops&mdash;dependency
chains between these statements must terminate.  To put this more formally,
consider a directed graph in which nodes are assignment statements and
directed arcs exist for each occurrence of an SBML species, compartment or
parameter symbol in an assignment statement's 'math' subelement.  Let the
directed arcs point from the statement assigning the symbol to the
statements that contain the symbol in their 'math' subelement expressions.
This graph must be acyclic.

<p> SBML does not specify when or how often rules should be evaluated.
Eliminating algebraic loops ensures that assignment statements can be
evaluated any number of times without the result of those evaluations
changing.  As an example, consider the set of equations <em>x = x + 1</em>,
<em>y = z + 200</em> and <em>z = y + 100</em>.  If this set of equations
were interpreted as a set of assignment statements, it would be invalid
because the rule for <em>x</em> refers to <em>x</em> (exhibiting one type
of loop), and the rule for <em>y</em> refers to <em>z</em> while the rule
for <em>z</em> refers back to <em>y</em> (exhibiting another type of loop).
Conversely, the following set of equations would constitute a valid set of
assignment statements: <em>x = 10</em>, <em>y = z + 200</em>, and <em>z = x
+ 100</em>.

<h3>A model must not be overdetermined</h3>

<p> An SBML model must not be overdetermined; that is, a model must not
define more equations than there are unknowns in a model.  An SBML model
that does not contain {@link AlgebraicRule} structures cannot be overdetermined.

<p> LibSBML 3.3 implements the static analysis procedure described in
Appendix D of the SBML Level&nbsp;2 Version&nbsp;4 specification for
assessing whether a model is overdetermined.

<p> (In summary, assessing whether a given continuous, deterministic,
mathematical model is overdetermined does not require dynamic analysis; it
can be done by analyzing the system of equations created from the model.
One approach is to construct a bipartite graph in which one set of vertices
represents the variables and the other the set of vertices represents the
equations.  Place edges between vertices such that variables in the system
are linked to the equations that determine them.  For algebraic equations,
there will be edges between the equation and each variable occurring in the
equation.  For ordinary differential equations (such as those defined by
rate rules or implied by the reaction rate definitions), there will be a
single edge between the equation and the variable determined by that
differential equation.  A mathematical model is overdetermined if the
maximal matchings of the bipartite graph contain disconnected vertexes
representing equations.  If one maximal matching has this property, then
all the maximal matchings will have this property; i.e., it is only
necessary to find one maximal matching.)

<h3><a class='anchor' name='RuleType_t'>RuleType_t</a></h3>

<p> SBML Level 1 uses a different scheme than SBML Level&nbsp;2 for
distinguishing rules; specifically, it uses an attribute whose value is
drawn from an enumeration.  LibSBML supports this using methods that work
with the RuleType_t enumeration.

<p>
<center>
<table width='90%' cellspacing='1' cellpadding='1' border='0' class='normal-font'>
 <tr style='background: lightgray' class='normal-font'>
     <td><strong>Enumerator</strong></td>
     <td><strong>Meaning</strong></td>
 </tr>
<tr><td><em>RULE_TYPE_RATE</em></td><td>Indicates the rule is a 'rate' rule.</td>
<tr><td><em>RULE_TYPE_SCALAR</em></td><td>Indicates the rule is a 'scalar' rule.</td>
<tr><td><em>RULE_TYPE_UNKNOWN</em></td><td>Indicates the rule type is unknown or not
yet set.</td>
</table>
</center>


 * <p>
 * <!-- leave this next break as-is to work around some doxygen bug -->
 */

public class AlgebraicRule extends Rule {
   private long swigCPtr;

   protected AlgebraicRule(long cPtr, boolean cMemoryOwn)
   {
     super(libsbmlJNI.SWIGAlgebraicRuleUpcast(cPtr), cMemoryOwn);
     swigCPtr = cPtr;
   }

   protected static long getCPtr(AlgebraicRule obj)
   {
     return (obj == null) ? 0 : obj.swigCPtr;
   }

   protected static long getCPtrAndDisown (AlgebraicRule obj)
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
        libsbmlJNI.delete_AlgebraicRule(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  
  /**
   * Creates a new {@link AlgebraicRule} using the given SBML <code>level</code> and <code>version</code>
   * values.
   * <p>
   * @param level a long integer, the SBML Level to assign to this {@link AlgebraicRule}
   * <p>
   * @param version a long integer, the SBML Version to assign to this
   * {@link AlgebraicRule}
   * <p>
   * @note Once a {@link AlgebraicRule} has been added to an {@link SBMLDocument}, the <code>level</code>,
   * <code>version</code> for the document <em>override</em> those used
   * to create the {@link AlgebraicRule}.  Despite this, the ability to supply the values
   * at creation time is an important aid to creating valid SBML.  Knowledge of
   * the intented SBML Level and Version determine whether it is valid to
   * assign a particular value to an attribute, or whether it is valid to add
   * an object to an existing {@link SBMLDocument}.
   */
 public AlgebraicRule(long level, long version) throws org.sbml.libsbml.SBMLConstructorException {
    this(libsbmlJNI.new_AlgebraicRule__SWIG_0(level, version), true);
  }

  
  /**
   * Creates a new {@link AlgebraicRule} using the given {@link SBMLNamespaces} object
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
   * @note Once a {@link AlgebraicRule} has been added to an {@link SBMLDocument}, the <code>level</code>,
   * <code>version</code> and <code>xmlns</code> namespaces for the document <em>override</em> those used
   * to create the {@link AlgebraicRule}.  Despite this, the ability to supply the values
   * at creation time is an important aid to creating valid SBML.  Knowledge of
   * the intented SBML Level and Version determine whether it is valid to
   * assign a particular value to an attribute, or whether it is valid to add
   * an object to an existing {@link SBMLDocument}.
   */
 public AlgebraicRule(SBMLNamespaces sbmlns) throws org.sbml.libsbml.SBMLConstructorException {
    this(libsbmlJNI.new_AlgebraicRule__SWIG_1(SBMLNamespaces.getCPtr(sbmlns), sbmlns), true);
  }

  
  /**
   * Creates and returns a deep copy of this {@link Rule}.
   * <p>
   * @return a (deep) copy of this {@link Rule}.
   */
 public AlgebraicRule cloneObject() {
    long cPtr = libsbmlJNI.AlgebraicRule_cloneObject(swigCPtr, this);
    return (cPtr == 0) ? null : new AlgebraicRule(cPtr, true);
  }

  
  /**
   * Predicate returning <code>true</code> or <code>false</code> depending on whether
   * all the required attributes for this {@link AlgebraicRule} object
   * have been set.
   * <p>
   * @note The required attributes for a {@link AlgebraicRule} object are:
   * formula (L1 only)
   */
 public boolean hasRequiredAttributes() {
    return libsbmlJNI.AlgebraicRule_hasRequiredAttributes(swigCPtr, this);
  }

}
