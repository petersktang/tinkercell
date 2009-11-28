/// 
///  @file    TestCompartment.cs
///  @brief   Compartment unit tests
///  @author  Frank Bergmann (Csharp conversion)
///  @author  Akiya Jouraku (Csharp conversion)
///  @author  Ben Bornstein 
/// 
///  $Id: TestCompartment.cs 10124 2009-08-28 12:04:51Z sarahkeating $
///  $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/trunk/libsbml/src/bindings/csharp/test/sbml/TestCompartment.cs $
/// 
///  This test file was converted from src/sbml/test/TestCompartment.c
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

  public class TestCompartment {
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

    private Compartment C;

    public void setUp()
    {
      C = new  Compartment(2,4);
      if (C == null);
      {
      }
    }

    public void tearDown()
    {
      C = null;
    }

    public void test_Compartment_create()
    {
      assertTrue( C.getTypeCode() == libsbml.SBML_COMPARTMENT );
      assertTrue( C.getMetaId() == "" );
      assertTrue( C.getNotes() == null );
      assertTrue( C.getAnnotation() == null );
      assertTrue( C.getId() == "" );
      assertTrue( C.getName() == "" );
      assertTrue( C.getUnits() == "" );
      assertTrue( C.getOutside() == "" );
      assertTrue( C.getSpatialDimensions() == 3 );
      assertTrue( C.getVolume() == 1.0 );
      assertTrue( C.getConstant() == true );
      assertEquals( false, C.isSetId() );
      assertEquals( false, C.isSetName() );
      assertEquals( false, C.isSetSize() );
      assertEquals( false, C.isSetVolume() );
      assertEquals( false, C.isSetUnits() );
      assertEquals( false, C.isSetOutside() );
    }

    public void test_Compartment_createWith()
    {
      Compartment c = new  Compartment(2,4);
      c.setId( "A");
      assertTrue( c.getTypeCode() == libsbml.SBML_COMPARTMENT );
      assertTrue( c.getMetaId() == "" );
      assertTrue( c.getNotes() == null );
      assertTrue( c.getAnnotation() == null );
      assertTrue( c.getName() == "" );
      assertTrue( c.getSpatialDimensions() == 3 );
      assertTrue((  "A"      == c.getId() ));
      assertTrue( c.getConstant() == true );
      assertEquals( true, c.isSetId() );
      assertEquals( false, c.isSetName() );
      c = null;
    }

    public void test_Compartment_createWithNS()
    {
      XMLNamespaces xmlns = new  XMLNamespaces();
      xmlns.add( "http://www.sbml.org", "testsbml");
      SBMLNamespaces sbmlns = new  SBMLNamespaces(2,1);
      sbmlns.addNamespaces(xmlns);
      Compartment c = new  Compartment(sbmlns);
      assertTrue( c.getTypeCode() == libsbml.SBML_COMPARTMENT );
      assertTrue( c.getMetaId() == "" );
      assertTrue( c.getNotes() == null );
      assertTrue( c.getAnnotation() == null );
      assertTrue( c.getLevel() == 2 );
      assertTrue( c.getVersion() == 1 );
      assertTrue( c.getNamespaces() != null );
      assertTrue( c.getNamespaces().getLength() == 2 );
      assertTrue( c.getName() == "" );
      assertTrue( c.getSpatialDimensions() == 3 );
      assertTrue( c.getConstant() == true );
      c = null;
    }

    public void test_Compartment_free_NULL()
    {
    }

    public void test_Compartment_getSpatialDimensions()
    {
      C.setSpatialDimensions(1);
      assertTrue( C.getSpatialDimensions() == 1 );
    }

    public void test_Compartment_getsetConstant()
    {
      C.setConstant(true);
      assertTrue( C.getConstant() == true );
    }

    public void test_Compartment_getsetType()
    {
      C.setCompartmentType( "cell");
      assertTrue((  "cell"  == C.getCompartmentType() ));
      assertEquals( true, C.isSetCompartmentType() );
      C.unsetCompartmentType();
      assertEquals( false, C.isSetCompartmentType() );
    }

    public void test_Compartment_initDefaults()
    {
      Compartment c = new  Compartment(2,4);
      c.setId( "A");
      c.initDefaults();
      assertTrue((  "A" == c.getId() ));
      assertTrue( c.getName() == "" );
      assertTrue( c.getUnits() == "" );
      assertTrue( c.getOutside() == "" );
      assertTrue( c.getSpatialDimensions() == 3 );
      assertTrue( c.getVolume() == 1.0 );
      assertTrue( c.getConstant() == true );
      assertEquals( true, c.isSetId() );
      assertEquals( false, c.isSetName() );
      assertEquals( false, c.isSetSize() );
      assertEquals( false, c.isSetVolume() );
      assertEquals( false, c.isSetUnits() );
      assertEquals( false, c.isSetOutside() );
      c = null;
    }

    public void test_Compartment_setId()
    {
      string id =  "mitochondria";;
      C.setId(id);
      assertTrue(( id == C.getId() ));
      assertEquals( true, C.isSetId() );
      if (C.getId() == id);
      {
      }
      C.setId(C.getId());
      assertTrue(( id == C.getId() ));
      C.setId("");
      assertEquals( false, C.isSetId() );
      if (C.getId() != null);
      {
      }
    }

    public void test_Compartment_setName()
    {
      string name =  "My_Favorite_Factory";;
      C.setName(name);
      assertTrue(( name == C.getName() ));
      assertEquals( true, C.isSetName() );
      if (C.getName() == name);
      {
      }
      C.setName(C.getName());
      assertTrue(( name == C.getName() ));
      C.setName("");
      assertEquals( false, C.isSetName() );
      if (C.getName() != null);
      {
      }
    }

    public void test_Compartment_setOutside()
    {
      string outside =  "cell";;
      C.setOutside(outside);
      assertTrue(( outside == C.getOutside() ));
      assertEquals( true, C.isSetOutside() );
      if (C.getOutside() == outside);
      {
      }
      C.setOutside(C.getOutside());
      assertTrue(( outside == C.getOutside() ));
      C.setOutside("");
      assertEquals( false, C.isSetOutside() );
      if (C.getOutside() != null);
      {
      }
    }

    public void test_Compartment_setUnits()
    {
      string units =  "volume";;
      C.setUnits(units);
      assertTrue(( units == C.getUnits() ));
      assertEquals( true, C.isSetUnits() );
      if (C.getUnits() == units);
      {
      }
      C.setUnits(C.getUnits());
      assertTrue(( units == C.getUnits() ));
      C.setUnits("");
      assertEquals( false, C.isSetUnits() );
      if (C.getUnits() != null);
      {
      }
    }

    public void test_Compartment_unsetSize()
    {
      C.setSize(0.2);
      assertTrue( C.getSize() == 0.2 );
      assertEquals( true, C.isSetSize() );
      C.unsetSize();
      assertEquals( false, C.isSetSize() );
    }

    public void test_Compartment_unsetVolume()
    {
      C.setVolume(1.0);
      assertTrue( C.getVolume() == 1.0 );
      C.unsetVolume();
      assertEquals( false, C.isSetVolume() );
    }

  }
}
