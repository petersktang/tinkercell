/// 
///  @file    TestCopyAndClone.cs
///  @brief   Test the copy and clone methods for annotation classes
///  @author  Frank Bergmann (Csharp conversion)
///  @author  Akiya Jouraku (Csharp conversion)
///  @author  Sarah Keating 
/// 
///  $Id: TestCopyAndClone.cs 10124 2009-08-28 12:04:51Z sarahkeating $
///  $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/trunk/libsbml/src/bindings/csharp/test/annotation/TestCopyAndClone.cs $
/// 
///  This test file was converted from src/sbml/test/TestCopyAndClone.cpp
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

  public class TestCopyAndClone {
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


    public void test_CVTerm_assignmentOperator()
    {
      CVTerm CVTerm1 = new CVTerm(libsbml.BIOLOGICAL_QUALIFIER);
      CVTerm1.addResource("http://www.geneontology.org/#GO:0005892");
      assertTrue( CVTerm1.getQualifierType() == libsbml.BIOLOGICAL_QUALIFIER );
      assertTrue( CVTerm1.getResources().getLength() == 1 );
      assertTrue( CVTerm1.getResources().getValue(0) ==  "http://www.geneontology.org/#GO:0005892" );
      CVTerm CVTerm2 = new CVTerm();
      CVTerm2 = CVTerm1;
      assertTrue( CVTerm2.getQualifierType() == libsbml.BIOLOGICAL_QUALIFIER );
      assertTrue( CVTerm2.getResources().getLength() == 1 );
      assertTrue( CVTerm2.getResources().getValue(0) ==  "http://www.geneontology.org/#GO:0005892" );
      CVTerm2 = null;
      CVTerm1 = null;
    }

    public void test_CVTerm_clone()
    {
      CVTerm CVTerm1 = new CVTerm(libsbml.BIOLOGICAL_QUALIFIER);
      CVTerm1.addResource("http://www.geneontology.org/#GO:0005892");
      assertTrue( CVTerm1.getQualifierType() == libsbml.BIOLOGICAL_QUALIFIER );
      assertTrue( CVTerm1.getResources().getLength() == 1 );
      assertTrue( CVTerm1.getResources().getValue(0) ==  "http://www.geneontology.org/#GO:0005892" );
      CVTerm CVTerm2 = (CVTerm) CVTerm1.clone();
      assertTrue( CVTerm2.getQualifierType() == libsbml.BIOLOGICAL_QUALIFIER );
      assertTrue( CVTerm2.getResources().getLength() == 1 );
      assertTrue( CVTerm2.getResources().getValue(0) ==  "http://www.geneontology.org/#GO:0005892" );
      CVTerm2 = null;
      CVTerm1 = null;
    }

    public void test_CVTerm_copyConstructor()
    {
      CVTerm CVTerm1 = new CVTerm(libsbml.BIOLOGICAL_QUALIFIER);
      CVTerm1.addResource("http://www.geneontology.org/#GO:0005892");
      assertTrue( CVTerm1.getQualifierType() == libsbml.BIOLOGICAL_QUALIFIER );
      assertTrue( CVTerm1.getResources().getLength() == 1 );
      assertTrue( CVTerm1.getResources().getValue(0) ==  "http://www.geneontology.org/#GO:0005892" );
      CVTerm CVTerm2 = new CVTerm(CVTerm1);
      assertTrue( CVTerm2.getQualifierType() == libsbml.BIOLOGICAL_QUALIFIER );
      assertTrue( CVTerm2.getResources().getLength() == 1 );
      assertTrue( CVTerm2.getResources().getValue(0) ==  "http://www.geneontology.org/#GO:0005892" );
      CVTerm2 = null;
      CVTerm1 = null;
    }

    public void test_Date_assignmentOperator()
    {
      Date date = new Date(2005,12,30,12,15,45,1,2,0);
      assertTrue( date.getMonth() == 12 );
      assertTrue( date.getSecond() == 45 );
      Date date2 = new Date();
      date2 = date;
      assertTrue( date2.getMonth() == 12 );
      assertTrue( date2.getSecond() == 45 );
      date2 = null;
      date = null;
    }

    public void test_Date_clone()
    {
      Date date = new Date(2005,12,30,12,15,45,1,2,0);
      assertTrue( date.getMonth() == 12 );
      assertTrue( date.getSecond() == 45 );
      Date date2 = (Date) date.clone();
      assertTrue( date2.getMonth() == 12 );
      assertTrue( date2.getSecond() == 45 );
      date2 = null;
      date = null;
    }

    public void test_Date_copyConstructor()
    {
      Date date = new Date(2005,12,30,12,15,45,1,2,0);
      assertTrue( date.getMonth() == 12 );
      assertTrue( date.getSecond() == 45 );
      Date date2 = new Date(date);
      assertTrue( date2.getMonth() == 12 );
      assertTrue( date2.getSecond() == 45 );
      date2 = null;
      date = null;
    }

    public void test_ModelCreator_assignmentOperator()
    {
      ModelCreator mc = new ModelCreator();
      mc.setFamilyName("Keating");
      mc.setEmail("sbml-team@caltech.edu");
      assertTrue( mc.getFamilyName() ==  "Keating" );
      assertTrue( mc.getEmail() ==  "sbml-team@caltech.edu" );
      ModelCreator mc2 = new ModelCreator();
      mc2 = mc;
      assertTrue( mc2.getFamilyName() ==  "Keating" );
      assertTrue( mc2.getEmail() ==  "sbml-team@caltech.edu" );
      mc2 = null;
      mc = null;
    }

    public void test_ModelCreator_clone()
    {
      ModelCreator mc = new ModelCreator();
      mc.setFamilyName("Keating");
      mc.setEmail("sbml-team@caltech.edu");
      assertTrue( mc.getFamilyName() ==  "Keating" );
      assertTrue( mc.getEmail() ==  "sbml-team@caltech.edu" );
      ModelCreator mc2 = (ModelCreator) mc.clone();
      assertTrue( mc2.getFamilyName() ==  "Keating" );
      assertTrue( mc2.getEmail() ==  "sbml-team@caltech.edu" );
      mc2 = null;
      mc = null;
    }

    public void test_ModelCreator_copyConstructor()
    {
      ModelCreator mc = new ModelCreator();
      mc.setFamilyName("Keating");
      mc.setEmail("sbml-team@caltech.edu");
      assertTrue( mc.getFamilyName() ==  "Keating" );
      assertTrue( mc.getEmail() ==  "sbml-team@caltech.edu" );
      ModelCreator mc2 = new ModelCreator(mc);
      assertTrue( mc2.getFamilyName() ==  "Keating" );
      assertTrue( mc2.getEmail() ==  "sbml-team@caltech.edu" );
      mc2 = null;
      mc = null;
    }

    public void test_ModelHistory_assignmentOperator()
    {
      ModelHistory mh = new ModelHistory();
      ModelCreator mc = new ModelCreator();
      mc.setGivenName("Sarah");
      mc.setFamilyName("Keating");
      mc.setEmail("sbml-team@caltech.edu");
      mh.addCreator(mc);
      mc = null;
      Date date = new Date(2005,12,30,12,15,45,1,2,0);
      mh.setCreatedDate(date);
      date = null;
      assertTrue( mh.getCreatedDate().getMonth() == 12 );
      assertTrue( mh.getCreatedDate().getSecond() == 45 );
      assertTrue( ((ModelCreator) mh.getCreator(0)).getFamilyName() ==  "Keating" );
      ModelHistory mh2 = new ModelHistory();
      mh2 = mh;
      assertTrue( mh2.getCreatedDate().getMonth() == 12 );
      assertTrue( mh2.getCreatedDate().getSecond() == 45 );
      assertTrue( ((ModelCreator) mh2.getCreator(0)).getFamilyName() ==  "Keating" );
      mh2 = null;
      mh = null;
    }

    public void test_ModelHistory_clone()
    {
      ModelHistory mh = new ModelHistory();
      ModelCreator mc = new ModelCreator();
      mc.setFamilyName("Keating");
      mc.setGivenName("Sarah");
      mc.setEmail("sbml-team@caltech.edu");
      mh.addCreator(mc);
      mc = null;
      Date date = new Date(2005,12,30,12,15,45,1,2,0);
      mh.setCreatedDate(date);
      date = null;
      assertTrue( mh.getCreatedDate().getMonth() == 12 );
      assertTrue( mh.getCreatedDate().getSecond() == 45 );
      assertTrue( ((ModelCreator) mh.getCreator(0)).getFamilyName() ==  "Keating" );
      ModelHistory mh2 = (ModelHistory) mh.clone();
      assertTrue( mh2.getCreatedDate().getMonth() == 12 );
      assertTrue( mh2.getCreatedDate().getSecond() == 45 );
      assertTrue( ((ModelCreator) mh2.getCreator(0)).getFamilyName() ==  "Keating" );
      mh2 = null;
      mh = null;
    }

    public void test_ModelHistory_copyConstructor()
    {
      ModelHistory mh = new ModelHistory();
      ModelCreator mc = new ModelCreator();
      mc.setFamilyName("Keating");
      mc.setGivenName("Sarah");
      mc.setEmail("sbml-team@caltech.edu");
      mh.addCreator(mc);
      mc = null;
      Date date = new Date(2005,12,30,12,15,45,1,2,0);
      mh.setCreatedDate(date);
      date = null;
      assertTrue( mh.getCreatedDate().getMonth() == 12 );
      assertTrue( mh.getCreatedDate().getSecond() == 45 );
      assertTrue( ((ModelCreator) mh.getCreator(0)).getFamilyName() ==  "Keating" );
      ModelHistory mh2 = new ModelHistory(mh);
      assertTrue( mh2.getCreatedDate().getMonth() == 12 );
      assertTrue( mh2.getCreatedDate().getSecond() == 45 );
      assertTrue( ((ModelCreator) mh2.getCreator(0)).getFamilyName() ==  "Keating" );
      mh2 = null;
      mh = null;
    }

  }
}
