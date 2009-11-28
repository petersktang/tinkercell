#
# @file    TestXMLToken_newSetters.py
# @brief   XMLToken_newSetters unit tests
#
# @author  Akiya Jouraku (Python conversion)
# @author  Sarah Keating 
#
# $Id$
# $HeadURL$
#
# This test file was converted from src/sbml/test/TestXMLToken_newSetters.c
# with the help of conversion sciprt (ctest_converter.pl).
#
#<!---------------------------------------------------------------------------
# This file is part of libSBML.  Please visit http://sbml.org for more
# information about SBML, and the latest version of libSBML.
#
# Copyright 2005-2009 California Institute of Technology.
# Copyright 2002-2005 California Institute of Technology and
#                     Japan Science and Technology Corporation.
# 
# This library is free software; you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation.  A copy of the license agreement is provided
# in the file named "LICENSE.txt" included with this software distribution
# and also available online as http://sbml.org/software/libsbml/license.html
#--------------------------------------------------------------------------->*/
import sys
import unittest
import libsbml

class TestXMLToken_newSetters(unittest.TestCase):


  def test_XMLToken_newSetters_addAttributes1(self):
    triple = libsbml.XMLTriple("test","","")
    attr = libsbml.XMLAttributes()
    token = libsbml.XMLToken(triple,attr)
    xt2 = libsbml.XMLTriple("name3", "http://name3.org/", "p3")
    i = token.addAttr( "name1", "val1")
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( token.getAttributesLength() == 1 )
    self.assert_( token.isAttributesEmpty() == False )
    self.assert_( (  "name1" != token.getAttrName(0) ) == False )
    self.assert_( (  "val1"  != token.getAttrValue(0) ) == False )
    i = token.addAttr( "name2", "val2", "http://name1.org/", "p1")
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( token.getAttributesLength() == 2 )
    self.assert_( token.isAttributesEmpty() == False )
    self.assert_( (  "name2" != token.getAttrName(1) ) == False )
    self.assert_( (  "val2"  != token.getAttrValue(1) ) == False )
    self.assert_( (  "http://name1.org/" != token.getAttrURI(1) ) == False )
    self.assert_( (  "p1"    != token.getAttrPrefix(1) ) == False )
    i = token.addAttr(xt2, "val2")
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( token.getAttributesLength() == 3 )
    self.assert_( token.isAttributesEmpty() == False )
    self.assert_( (  "name3" != token.getAttrName(2) ) == False )
    self.assert_( (  "val2"  != token.getAttrValue(2) ) == False )
    self.assert_( (  "http://name3.org/" != token.getAttrURI(2) ) == False )
    self.assert_( (  "p3"    != token.getAttrPrefix(2) ) == False )
    xt2 = None
    triple = None
    attr = None
    token = None
    pass  

  def test_XMLToken_newSetters_addAttributes2(self):
    triple = libsbml.XMLTriple("test","","")
    token = libsbml.XMLToken(triple)
    xt2 = libsbml.XMLTriple("name3", "http://name3.org/", "p3")
    i = token.addAttr( "name1", "val1")
    self.assert_( i == libsbml.LIBSBML_INVALID_XML_OPERATION )
    self.assert_( token.getAttributesLength() == 0 )
    self.assert_( token.isAttributesEmpty() == True )
    i = token.addAttr( "name2", "val2", "http://name1.org/", "p1")
    self.assert_( i == libsbml.LIBSBML_INVALID_XML_OPERATION )
    self.assert_( token.getAttributesLength() == 0 )
    self.assert_( token.isAttributesEmpty() == True )
    i = token.addAttr(xt2, "val2")
    self.assert_( i == libsbml.LIBSBML_INVALID_XML_OPERATION )
    self.assert_( token.getAttributesLength() == 0 )
    self.assert_( token.isAttributesEmpty() == True )
    xt2 = None
    triple = None
    token = None
    pass  

  def test_XMLToken_newSetters_addNamespaces1(self):
    triple = libsbml.XMLTriple("test","","")
    attr = libsbml.XMLAttributes()
    token = libsbml.XMLToken(triple,attr)
    self.assert_( token.getNamespacesLength() == 0 )
    self.assert_( token.isNamespacesEmpty() == True )
    i = token.addNamespace( "http://test1.org/", "test1")
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( token.getNamespacesLength() == 1 )
    self.assert_( token.isNamespacesEmpty() == False )
    attr = None
    triple = None
    token = None
    pass  

  def test_XMLToken_newSetters_addNamespaces2(self):
    triple = libsbml.XMLTriple("test","","")
    token = libsbml.XMLToken(triple)
    self.assert_( token.getNamespacesLength() == 0 )
    self.assert_( token.isNamespacesEmpty() == True )
    i = token.addNamespace( "http://test1.org/", "test1")
    self.assert_( i == libsbml.LIBSBML_INVALID_XML_OPERATION )
    self.assert_( token.getNamespacesLength() == 0 )
    self.assert_( token.isNamespacesEmpty() == True )
    triple = None
    token = None
    pass  

  def test_XMLToken_newSetters_clearAttributes1(self):
    triple = libsbml.XMLTriple("test","","")
    attr = libsbml.XMLAttributes()
    token = libsbml.XMLToken(triple,attr)
    nattr = libsbml.XMLAttributes()
    xt1 = libsbml.XMLTriple("name1", "http://name1.org/", "p1")
    nattr.add(xt1, "val1")
    i = token.setAttributes(nattr)
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( token.isAttributesEmpty() == False )
    i = token.clearAttributes()
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( token.isAttributesEmpty() == True )
    nattr = None
    attr = None
    triple = None
    token = None
    xt1 = None
    pass  

  def test_XMLToken_newSetters_clearNamespaces1(self):
    triple = libsbml.XMLTriple("test","","")
    attr = libsbml.XMLAttributes()
    token = libsbml.XMLToken(triple,attr)
    ns = libsbml.XMLNamespaces()
    self.assert_( token.getNamespacesLength() == 0 )
    self.assert_( token.isNamespacesEmpty() == True )
    ns.add( "http://test1.org/", "test1")
    i = token.setNamespaces(ns)
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( token.getNamespacesLength() == 1 )
    self.assert_( token.isNamespacesEmpty() == False )
    i = token.clearNamespaces()
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( token.getNamespacesLength() == 0 )
    self.assert_( token.isNamespacesEmpty() == True )
    attr = None
    triple = None
    token = None
    ns = None
    pass  

  def test_XMLToken_newSetters_removeAttributes1(self):
    triple = libsbml.XMLTriple("test","","")
    attr = libsbml.XMLAttributes()
    token = libsbml.XMLToken(triple,attr)
    xt2 = libsbml.XMLTriple("name3", "http://name3.org/", "p3")
    xt1 = libsbml.XMLTriple("name5", "http://name5.org/", "p5")
    i = token.addAttr( "name1", "val1")
    i = token.addAttr( "name2", "val2", "http://name1.org/", "p1")
    i = token.addAttr(xt2, "val2")
    i = token.addAttr( "name4", "val4")
    self.assert_( token.getAttributes().getLength() == 4 )
    i = token.removeAttr(7)
    self.assert_( i == libsbml.LIBSBML_INDEX_EXCEEDS_SIZE )
    i = token.removeAttr( "name7")
    self.assert_( i == libsbml.LIBSBML_INDEX_EXCEEDS_SIZE )
    i = token.removeAttr( "name7", "namespaces7")
    self.assert_( i == libsbml.LIBSBML_INDEX_EXCEEDS_SIZE )
    i = token.removeAttr(xt1)
    self.assert_( i == libsbml.LIBSBML_INDEX_EXCEEDS_SIZE )
    self.assert_( token.getAttributes().getLength() == 4 )
    i = token.removeAttr(3)
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( token.getAttributes().getLength() == 3 )
    i = token.removeAttr( "name1")
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( token.getAttributes().getLength() == 2 )
    i = token.removeAttr( "name2", "http://name1.org/")
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( token.getAttributes().getLength() == 1 )
    i = token.removeAttr(xt2)
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( token.getAttributes().getLength() == 0 )
    xt1 = None
    xt2 = None
    triple = None
    attr = None
    token = None
    pass  

  def test_XMLToken_newSetters_removeNamespaces(self):
    triple = libsbml.XMLTriple("test","","")
    attr = libsbml.XMLAttributes()
    token = libsbml.XMLToken(triple,attr)
    token.addNamespace( "http://test1.org/", "test1")
    self.assert_( token.getNamespacesLength() == 1 )
    i = token.removeNamespace(4)
    self.assert_( i == libsbml.LIBSBML_INDEX_EXCEEDS_SIZE )
    self.assert_( token.getNamespacesLength() == 1 )
    i = token.removeNamespace(0)
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( token.getNamespacesLength() == 0 )
    token = None
    triple = None
    attr = None
    pass  

  def test_XMLToken_newSetters_removeNamespaces1(self):
    triple = libsbml.XMLTriple("test","","")
    attr = libsbml.XMLAttributes()
    token = libsbml.XMLToken(triple,attr)
    token.addNamespace( "http://test1.org/", "test1")
    self.assert_( token.getNamespacesLength() == 1 )
    i = token.removeNamespace( "test2")
    self.assert_( i == libsbml.LIBSBML_INDEX_EXCEEDS_SIZE )
    self.assert_( token.getNamespacesLength() == 1 )
    i = token.removeNamespace( "test1")
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( token.getNamespacesLength() == 0 )
    token = None
    triple = None
    attr = None
    pass  

  def test_XMLToken_newSetters_setAttributes1(self):
    triple = libsbml.XMLTriple("test","","")
    attr = libsbml.XMLAttributes()
    token = libsbml.XMLToken(triple,attr)
    nattr = libsbml.XMLAttributes()
    xt1 = libsbml.XMLTriple("name1", "http://name1.org/", "p1")
    nattr.add(xt1, "val1")
    i = token.setAttributes(nattr)
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( token.isAttributesEmpty() == False )
    nattr = None
    attr = None
    triple = None
    token = None
    xt1 = None
    pass  

  def test_XMLToken_newSetters_setAttributes2(self):
    triple = libsbml.XMLTriple("test","","")
    token = libsbml.XMLToken(triple)
    nattr = libsbml.XMLAttributes()
    xt1 = libsbml.XMLTriple("name1", "http://name1.org/", "p1")
    nattr.add(xt1, "val1")
    i = token.setAttributes(nattr)
    self.assert_( i == libsbml.LIBSBML_INVALID_XML_OPERATION )
    self.assert_( token.isAttributesEmpty() == True )
    nattr = None
    triple = None
    token = None
    xt1 = None
    pass  

  def test_XMLToken_newSetters_setEOF(self):
    token = libsbml.XMLToken()
    self.assert_( token.isEnd() == False )
    i = token.setEOF()
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( token.isEnd() == False )
    self.assert_( token.isStart() == False )
    self.assert_( token.isText() == False )
    token = None
    pass  

  def test_XMLToken_newSetters_setEnd(self):
    token = libsbml.XMLToken()
    self.assert_( token.isEnd() == False )
    i = token.setEnd()
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( token.isEnd() == True )
    i = token.unsetEnd()
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( token.isEnd() == False )
    token = None
    pass  

  def test_XMLToken_newSetters_setNamespaces1(self):
    triple = libsbml.XMLTriple("test","","")
    attr = libsbml.XMLAttributes()
    token = libsbml.XMLToken(triple,attr)
    ns = libsbml.XMLNamespaces()
    self.assert_( token.getNamespacesLength() == 0 )
    self.assert_( token.isNamespacesEmpty() == True )
    ns.add( "http://test1.org/", "test1")
    i = token.setNamespaces(ns)
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( token.getNamespacesLength() == 1 )
    self.assert_( token.isNamespacesEmpty() == False )
    attr = None
    triple = None
    token = None
    ns = None
    pass  

  def test_XMLToken_newSetters_setNamespaces2(self):
    triple = libsbml.XMLTriple("test","","")
    token = libsbml.XMLToken(triple)
    ns = libsbml.XMLNamespaces()
    self.assert_( token.getNamespacesLength() == 0 )
    self.assert_( token.isNamespacesEmpty() == True )
    ns.add( "http://test1.org/", "test1")
    i = token.setNamespaces(ns)
    self.assert_( i == libsbml.LIBSBML_INVALID_XML_OPERATION )
    self.assert_( token.getNamespacesLength() == 0 )
    self.assert_( token.isNamespacesEmpty() == True )
    triple = None
    token = None
    ns = None
    pass  

  def test_XMLToken_newSetters_setTriple1(self):
    triple = libsbml.XMLTriple("test","","")
    token = libsbml.XMLToken()
    i = token.setTriple(triple)
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_((  "test" == token.getName() ))
    triple = None
    token = None
    pass  

  def test_XMLToken_newSetters_setTriple2(self):
    triple = libsbml.XMLTriple("test","","")
    token = libsbml.XMLToken("This is text")
    i = token.setTriple(triple)
    self.assert_( i == libsbml.LIBSBML_INVALID_XML_OPERATION )
    triple = None
    token = None
    pass  

def suite():
  suite = unittest.TestSuite()
  suite.addTest(unittest.makeSuite(TestXMLToken_newSetters))

  return suite

if __name__ == "__main__":
  if unittest.TextTestRunner(verbosity=1).run(suite()).wasSuccessful() :
    sys.exit(0)
  else:
    sys.exit(1)
