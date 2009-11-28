/// 
///  @file    TestSpeciesReference.cs
///  @brief   SpeciesReference unit tests
///  @author  Frank Bergmann (Csharp conversion)
///  @author  Akiya Jouraku (Csharp conversion)
///  @author  Ben Bornstein 
/// 
///  $Id: TestSpeciesReference.cs 10124 2009-08-28 12:04:51Z sarahkeating $
///  $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/trunk/libsbml/src/bindings/csharp/test/sbml/TestSpeciesReference.cs $
/// 
///  This test file was converted from src/sbml/test/TestSpeciesReference.c
///  with the help of conversion sciprt (ctest_converter.pl).
/// 
/// <!---------------------------------------------------------------------------
///  This file is part of libSBML.  Please visit http://sbml.org for more
///  information about SBML, and the latest version of libSBML.
/// 
///  Copyright 2005-2009 California Institute of Technology.
///  Copyright 2002-2005 California Institute of Technology and
///                      Japan Science and Technology Corporation.
///  
///  This library is free software; you can redistribute it and/or modify it
///  under the terms of the GNU Lesser General Public License as published by
///  the Free Software Foundation.  A copy of the license agreement is provided
///  in the file named "LICENSE.txt" included with this software distribution
///  and also available online as http://sbml.org/software/libsbml/license.html
/// --------------------------------------------------------------------------->*/


namespace LibSBMLCSTest {

  using libsbml;

  using  System.IO;

  public class TestSpeciesReference {
    public class AssertionError : System.Exception 
    {
      public AssertionError() : base()
      {
        
      }
    }


    static void assertTrue(bool condition)
    {
      if (condition == true)
      {
        return;
      }
      throw new AssertionError();
    }

    static void assertEquals(object a, object b)
    {
      if ( (a == null) && (b == null) )
      {
        return;
      }
      else if ( (a == null) || (b == null) )
      {
        throw new AssertionError();
      }
      else if (a.Equals(b))
      {
        return;
      }
  
      throw new AssertionError();
    }

    static void assertNotEquals(object a, object b)
    {
      if ( (a == null) && (b == null) )
      {
        throw new AssertionError();
      }
      else if ( (a == null) || (b == null) )
      {
        return;
      }
      else if (a.Equals(b))
      {
        throw new AssertionError();
      }
    }

    static void assertEquals(bool a, bool b)
    {
      if ( a == b )
      {
        return;
      }
      throw new AssertionError();
    }

    static void assertNotEquals(bool a, bool b)
    {
      if ( a != b )
      {
        return;
      }
      throw new AssertionError();
    }

    static void assertEquals(int a, int b)
    {
      if ( a == b )
      {
        return;
      }
      throw new AssertionError();
    }

    static void assertNotEquals(int a, int b)
    {
      if ( a != b )
      {
        return;
      }
      throw new AssertionError();
    }

    private SpeciesReference SR;

    public void setUp()
    {
      SR = new  SpeciesReference(2,4);
      if (SR == null);
      {
      }
    }

    public void tearDown()
    {
      SR = null;
    }

    public void test_SpeciesReference_create()
    {
      assertTrue( SR.getTypeCode() == libsbml.SBML_SPECIES_REFERENCE );
      assertTrue( SR.getMetaId() == "" );
      assertTrue( SR.getNotes() == null );
      assertTrue( SR.getAnnotation() == null );
      assertTrue( SR.getSpecies() == "" );
      assertTrue( SR.getStoichiometry() == 1 );
      assertEquals(SR.getStoichiometryMath(),null);
      assertTrue( SR.getDenominator() == 1 );
      assertEquals( false, SR.isSetSpecies() );
      assertEquals( false, SR.isSetStoichiometryMath() );
    }

    public void test_SpeciesReference_createModifier()
    {
      ModifierSpeciesReference sr = new  ModifierSpeciesReference(2,4);
      assertTrue( sr.getTypeCode() == libsbml.SBML_MODIFIER_SPECIES_REFERENCE );
      assertTrue( sr.getMetaId() == "" );
      assertTrue( sr.getNotes() == null );
      assertTrue( sr.getAnnotation() == null );
      assertEquals( true, sr.isModifier() );
      sr = null;
    }

    public void test_SpeciesReference_createWithNS()
    {
      XMLNamespaces xmlns = new  XMLNamespaces();
      xmlns.add( "http://www.sbml.org", "testsbml");
      SBMLNamespaces sbmlns = new  SBMLNamespaces(2,1);
      sbmlns.addNamespaces(xmlns);
      SpeciesReference object1 = new  SpeciesReference(sbmlns);
      assertTrue( object1.getTypeCode() == libsbml.SBML_SPECIES_REFERENCE );
      assertTrue( object1.getMetaId() == "" );
      assertTrue( object1.getNotes() == null );
      assertTrue( object1.getAnnotation() == null );
      assertTrue( object1.getLevel() == 2 );
      assertTrue( object1.getVersion() == 1 );
      assertTrue( object1.getNamespaces() != null );
      assertTrue( object1.getNamespaces().getLength() == 2 );
      object1 = null;
    }

    public void test_SpeciesReference_free_NULL()
    {
    }

    public void test_SpeciesReference_setId()
    {
      string species =  "X0";;
      SR.setId(species);
      assertTrue(( species == SR.getId() ));
      assertEquals( true, SR.isSetId() );
      if (SR.getId() == species);
      {
      }
      SR.setId(SR.getId());
      assertTrue(( species == SR.getId() ));
      SR.setId("");
      assertEquals( false, SR.isSetId() );
      if (SR.getId() != null);
      {
      }
    }

    public void test_SpeciesReference_setSpecies()
    {
      string species =  "X0";;
      SR.setSpecies(species);
      assertTrue(( species == SR.getSpecies() ));
      assertEquals( true, SR.isSetSpecies() );
      if (SR.getSpecies() == species);
      {
      }
      SR.setSpecies(SR.getSpecies());
      assertTrue(( species == SR.getSpecies() ));
      SR.setSpecies("");
      assertEquals( false, SR.isSetSpecies() );
      if (SR.getSpecies() != null);
      {
      }
    }

    public void test_SpeciesReference_setStoichiometryMath()
    {
      ASTNode math = libsbml.parseFormula("k3 / k2");
      StoichiometryMath stoich = new  StoichiometryMath(2,4);
      stoich.setMath(math);
      StoichiometryMath math1;
      string formula;
      SR.setStoichiometryMath(stoich);
      math1 = SR.getStoichiometryMath();
      assertTrue( math1 != null );
      formula = libsbml.formulaToString(math1.getMath());
      assertTrue( formula != null );
      assertTrue((  "k3 / k2" == formula ));
      assertEquals( true, SR.isSetStoichiometryMath() );
    }

  }
}
