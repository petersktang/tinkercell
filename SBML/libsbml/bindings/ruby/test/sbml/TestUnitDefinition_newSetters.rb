#
# @file    TestUnitDefinition_newSetters.rb
# @brief   SBML UnitDefinition unit tests for new API
#
# @author  Akiya Jouraku (Ruby conversion)
# @author  sarah Keating 
#
# $Id$
# $HeadURL$
#
# This test file was converted from src/sbml/test/TestUnitDefinition_newSetters.c
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
require 'test/unit'
require 'libSBML'

class TestUnitDefinition_newSetters < Test::Unit::TestCase

  def setup
    @@ud = LibSBML::UnitDefinition.new(2,4)
    if (@@ud == nil)
    end
  end

  def teardown
    @@ud = nil
  end

  def test_UnitDefinition_addUnit1
    m = LibSBML::UnitDefinition.new(2,2)
    p = LibSBML::Unit.new(2,2)
    i = m.addUnit(p)
    assert( i == LibSBML::LIBSBML_INVALID_OBJECT )
    p.setKind(LibSBML::UNIT_KIND_MOLE)
    i = m.addUnit(p)
    assert( i == LibSBML::LIBSBML_OPERATION_SUCCESS )
    assert( m.getNumUnits() == 1 )
    p = nil
    m = nil
  end

  def test_UnitDefinition_addUnit2
    m = LibSBML::UnitDefinition.new(2,2)
    p = LibSBML::Unit.new(2,1)
    p.setKind(LibSBML::UNIT_KIND_MOLE)
    i = m.addUnit(p)
    assert( i == LibSBML::LIBSBML_VERSION_MISMATCH )
    assert( m.getNumUnits() == 0 )
    p = nil
    m = nil
  end

  def test_UnitDefinition_addUnit3
    m = LibSBML::UnitDefinition.new(2,2)
    p = LibSBML::Unit.new(1,2)
    p.setKind(LibSBML::UNIT_KIND_MOLE)
    i = m.addUnit(p)
    assert( i == LibSBML::LIBSBML_LEVEL_MISMATCH )
    assert( m.getNumUnits() == 0 )
    p = nil
    m = nil
  end

  def test_UnitDefinition_addUnit4
    m = LibSBML::UnitDefinition.new(2,2)
    p = nil
    i = m.addUnit(p)
    assert( i == LibSBML::LIBSBML_OPERATION_FAILED )
    assert( m.getNumUnits() == 0 )
    m = nil
  end

  def test_UnitDefinition_createUnit
    m = LibSBML::UnitDefinition.new(2,2)
    p = m.createUnit()
    assert( m.getNumUnits() == 1 )
    assert( (p).getLevel() == 2 )
    assert( (p).getVersion() == 2 )
    m = nil
  end

  def test_UnitDefinition_setId1
    i = @@ud.setId( "mmls")
    assert( i == LibSBML::LIBSBML_OPERATION_SUCCESS )
    assert ((  "mmls" == @@ud.getId() ))
    assert_equal true, @@ud.isSetId()
    i = @@ud.setId("")
    assert( i == LibSBML::LIBSBML_OPERATION_SUCCESS )
    assert_equal false, @@ud.isSetId()
    i = @@ud.setId( "123")
    assert( i == LibSBML::LIBSBML_INVALID_ATTRIBUTE_VALUE )
    assert_equal false, @@ud.isSetId()
  end

  def test_UnitDefinition_setName1
    i = @@ud.setName( "mmls")
    assert( i == LibSBML::LIBSBML_OPERATION_SUCCESS )
    assert ((  "mmls" == @@ud.getName() ))
    assert_equal true, @@ud.isSetName()
    i = @@ud.setName("")
    assert( i == LibSBML::LIBSBML_OPERATION_SUCCESS )
    assert_equal false, @@ud.isSetName()
    i = @@ud.setName( "123")
    assert( i == LibSBML::LIBSBML_OPERATION_SUCCESS )
    assert_equal true, @@ud.isSetName()
  end

  def test_UnitDefinition_setName2
    i = @@ud.setName( "mmls")
    assert( i == LibSBML::LIBSBML_OPERATION_SUCCESS )
    assert ((  "mmls" == @@ud.getName() ))
    assert_equal true, @@ud.isSetName()
    i = @@ud.unsetName()
    assert( i == LibSBML::LIBSBML_OPERATION_SUCCESS )
    assert_equal false, @@ud.isSetName()
  end

end
