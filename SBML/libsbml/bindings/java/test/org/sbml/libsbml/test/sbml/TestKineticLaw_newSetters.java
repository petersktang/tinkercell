/*
 *
 * @file    TestKineticLaw_newSetters.java
 * @brief   KineticLaw unit tests for new set function API
 *
 * @author  Akiya Jouraku (Java conversion)
 * @author  Sarah Keating 
 *
 * $Id$
 * $HeadURL$
 *
 * This test file was converted from src/sbml/test/TestKineticLaw_newSetters.c
 * with the help of conversion sciprt (ctest_converter.pl).
 *
 *<!---------------------------------------------------------------------------
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 *
 * Copyright 2005-2009 California Institute of Technology.
 * Copyright 2002-2005 California Institute of Technology and
 *                     Japan Science and Technology Corporation.
 * 
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.  A copy of the license agreement is provided
 * in the file named "LICENSE.txt" included with this software distribution
 * and also available online as http://sbml.org/software/libsbml/license.html
 *--------------------------------------------------------------------------->*/


package org.sbml.libsbml.test.sbml;

import org.sbml.libsbml.*;

import java.io.File;
import java.lang.AssertionError;

public class TestKineticLaw_newSetters {

  static void assertTrue(boolean condition) throws AssertionError
  {
    if (condition == true)
    {
      return;
    }
    throw new AssertionError();
  }

  static void assertEquals(Object a, Object b) throws AssertionError
  {
    if ( (a == null) && (b == null) )
    {
      return;
    }
    else if ( (a == null) || (b == null) )
    {
      throw new AssertionError();
    }
    else if (a.equals(b))
    {
      return;
    }

    throw new AssertionError();
  }

  static void assertNotEquals(Object a, Object b) throws AssertionError
  {
    if ( (a == null) && (b == null) )
    {
      throw new AssertionError();
    }
    else if ( (a == null) || (b == null) )
    {
      return;
    }
    else if (a.equals(b))
    {
      throw new AssertionError();
    }
  }

  static void assertEquals(boolean a, boolean b) throws AssertionError
  {
    if ( a == b )
    {
      return;
    }
    throw new AssertionError();
  }

  static void assertNotEquals(boolean a, boolean b) throws AssertionError
  {
    if ( a != b )
    {
      return;
    }
    throw new AssertionError();
  }

  static void assertEquals(int a, int b) throws AssertionError
  {
    if ( a == b )
    {
      return;
    }
    throw new AssertionError();
  }

  static void assertNotEquals(int a, int b) throws AssertionError
  {
    if ( a != b )
    {
      return;
    }
    throw new AssertionError();
  }
  private KineticLaw kl;

  protected void setUp() throws Exception
  {
    kl = new  KineticLaw(2,4);
    if (kl == null);
    {
    }
  }

  protected void tearDown() throws Exception
  {
    kl = null;
  }

  public void test_KineticLaw_addParameter1()
  {
    KineticLaw kl = new  KineticLaw(2,2);
    Parameter p = new  Parameter(2,2);
    long i = kl.addParameter(p);
    assertTrue( i == libsbml.LIBSBML_INVALID_OBJECT );
    p.setId( "p");
    i = kl.addParameter(p);
    assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
    assertTrue( kl.getNumParameters() == 1 );
    p = null;
    kl = null;
  }

  public void test_KineticLaw_addParameter2()
  {
    KineticLaw kl = new  KineticLaw(2,2);
    Parameter p = new  Parameter(2,1);
    p.setId( "p");
    long i = kl.addParameter(p);
    assertTrue( i == libsbml.LIBSBML_VERSION_MISMATCH );
    assertTrue( kl.getNumParameters() == 0 );
    p = null;
    kl = null;
  }

  public void test_KineticLaw_addParameter3()
  {
    KineticLaw kl = new  KineticLaw(2,2);
    Parameter p = new  Parameter(1,2);
    p.setId( "p");
    long i = kl.addParameter(p);
    assertTrue( i == libsbml.LIBSBML_LEVEL_MISMATCH );
    assertTrue( kl.getNumParameters() == 0 );
    p = null;
    kl = null;
  }

  public void test_KineticLaw_addParameter4()
  {
    KineticLaw kl = new  KineticLaw(2,2);
    Parameter p = null;
    long i = kl.addParameter(p);
    assertTrue( i == libsbml.LIBSBML_OPERATION_FAILED );
    assertTrue( kl.getNumParameters() == 0 );
    kl = null;
  }

  public void test_KineticLaw_createParameter()
  {
    KineticLaw kl = new  KineticLaw(2,2);
    Parameter p = kl.createParameter();
    assertTrue( kl.getNumParameters() == 1 );
    assertTrue( (p).getLevel() == 2 );
    assertTrue( (p).getVersion() == 2 );
    kl = null;
  }

  public void test_KineticLaw_setFormula1()
  {
    String formula =  "k1*X0";;
    long i = kl.setFormula(formula);
    assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
    assertTrue(kl.getFormula().equals(formula));
    assertEquals( true, kl.isSetFormula() );
  }

  public void test_KineticLaw_setFormula2()
  {
    long i = kl.setFormula("");
    assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
    assertEquals( false, kl.isSetFormula() );
  }

  public void test_KineticLaw_setFormula3()
  {
    String formula =  "k1 X0";;
    long i = kl.setFormula(formula);
    assertTrue( i == libsbml.LIBSBML_INVALID_OBJECT );
    assertEquals( false, kl.isSetFormula() );
  }

  public void test_KineticLaw_setMath1()
  {
    ASTNode math = new  ASTNode(libsbml.AST_TIMES);
    ASTNode a = new  ASTNode();
    ASTNode b = new  ASTNode();
    a.setName( "a");
    b.setName( "b");
    math.addChild(a);
    math.addChild(b);
    String formula;
    ASTNode math1;
    long i = kl.setMath(math);
    assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
    assertEquals( true, kl.isSetMath() );
    math1 = kl.getMath();
    assertTrue( math1 != null );
    formula = libsbml.formulaToString(math1);
    assertTrue( formula != null );
    assertTrue(formula.equals( "a * b"));
    math = null;
  }

  public void test_KineticLaw_setMath2()
  {
    ASTNode math = new  ASTNode(libsbml.AST_TIMES);
    ASTNode a = new  ASTNode();
    a.setName( "a");
    math.addChild(a);
    long i = kl.setMath(math);
    assertTrue( i == libsbml.LIBSBML_INVALID_OBJECT );
    assertEquals( false, kl.isSetMath() );
    math = null;
  }

  public void test_KineticLaw_setMath3()
  {
    long i = kl.setMath(null);
    assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
    assertEquals( false, kl.isSetMath() );
  }

  public void test_KineticLaw_setSubstanceUnits1()
  {
    long i = kl.setSubstanceUnits( "mole");
    assertTrue( i == libsbml.LIBSBML_UNEXPECTED_ATTRIBUTE );
    assertEquals( false, kl.isSetSubstanceUnits() );
    i = kl.unsetSubstanceUnits();
    assertTrue( i == libsbml.LIBSBML_UNEXPECTED_ATTRIBUTE );
    assertEquals( false, kl.isSetSubstanceUnits() );
  }

  public void test_KineticLaw_setSubstanceUnits2()
  {
    KineticLaw kl1 = new  KineticLaw(1,2);
    long i = kl1.setSubstanceUnits( "mole");
    assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
    assertEquals( true, kl1.isSetSubstanceUnits() );
    i = kl1.unsetSubstanceUnits();
    assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
    assertEquals( false, kl1.isSetSubstanceUnits() );
    kl1 = null;
  }

  public void test_KineticLaw_setSubstanceUnits3()
  {
    KineticLaw kl1 = new  KineticLaw(1,2);
    long i = kl1.setSubstanceUnits( "1second");
    assertTrue( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE );
    assertEquals( false, kl1.isSetSubstanceUnits() );
    i = kl1.unsetSubstanceUnits();
    assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
    assertEquals( false, kl1.isSetSubstanceUnits() );
    kl1 = null;
  }

  public void test_KineticLaw_setSubstanceUnits4()
  {
    KineticLaw kl1 = new  KineticLaw(1,2);
    long i = kl1.setSubstanceUnits("");
    assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
    assertEquals( false, kl1.isSetSubstanceUnits() );
    kl1 = null;
  }

  public void test_KineticLaw_setTimeUnits1()
  {
    long i = kl.setTimeUnits( "second");
    assertTrue( i == libsbml.LIBSBML_UNEXPECTED_ATTRIBUTE );
    assertEquals( false, kl.isSetTimeUnits() );
    i = kl.unsetTimeUnits();
    assertTrue( i == libsbml.LIBSBML_UNEXPECTED_ATTRIBUTE );
    assertEquals( false, kl.isSetTimeUnits() );
  }

  public void test_KineticLaw_setTimeUnits2()
  {
    KineticLaw kl1 = new  KineticLaw(1,2);
    long i = kl1.setTimeUnits( "second");
    assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
    assertEquals( true, kl1.isSetTimeUnits() );
    i = kl1.unsetTimeUnits();
    assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
    assertEquals( false, kl1.isSetTimeUnits() );
    kl1 = null;
  }

  public void test_KineticLaw_setTimeUnits3()
  {
    KineticLaw kl1 = new  KineticLaw(1,2);
    long i = kl1.setTimeUnits( "1second");
    assertTrue( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE );
    assertEquals( false, kl1.isSetTimeUnits() );
    i = kl1.unsetTimeUnits();
    assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
    assertEquals( false, kl1.isSetTimeUnits() );
    kl1 = null;
  }

  public void test_KineticLaw_setTimeUnits4()
  {
    KineticLaw kl1 = new  KineticLaw(1,2);
    long i = kl1.setTimeUnits("");
    assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
    assertEquals( false, kl1.isSetTimeUnits() );
    kl1 = null;
  }

  /**
   * Loads the SWIG-generated libSBML Java module when this class is
   * loaded, or reports a sensible diagnostic message about why it failed.
   */
  static
  {
    String varname;
    String shlibname;

    if (System.getProperty("mrj.version") != null)
    {
      varname = "DYLD_LIBRARY_PATH";    // We're on a Mac.
      shlibname = "libsbmlj.jnilib and/or libsbml.dylib";
    }
    else
    {
      varname = "LD_LIBRARY_PATH";      // We're not on a Mac.
      shlibname = "libsbmlj.so and/or libsbml.so";
    }

    try
    {
      System.loadLibrary("sbmlj");
      // For extra safety, check that the jar file is in the classpath.
      Class.forName("org.sbml.libsbml.libsbml");
    }
    catch (SecurityException e)
    {
      e.printStackTrace();
      System.err.println("Could not load the libSBML library files due to a"+
                         " security exception.\n");
      System.exit(1);
    }
    catch (UnsatisfiedLinkError e)
    {
      e.printStackTrace();
      System.err.println("Error: could not link with the libSBML library files."+
                         " It is likely\nyour " + varname +
                         " environment variable does not include the directories\n"+
                         "containing the " + shlibname + " library files.\n");
      System.exit(1);
    }
    catch (ClassNotFoundException e)
    {
      e.printStackTrace();
      System.err.println("Error: unable to load the file libsbmlj.jar."+
                         " It is likely\nyour -classpath option and CLASSPATH" +
                         " environment variable\n"+
                         "do not include the path to libsbmlj.jar.\n");
      System.exit(1);
    }
  }
}
