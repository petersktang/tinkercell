#
# @file    TestModelHistory.rb
# @brief   ModelHistory unit tests
#
# @author  Akiya Jouraku (Ruby conversion)
# @author  Sarah Keating 
#
# $Id: TestModelHistory.rb 9762 2009-07-13 06:51:18Z ajouraku $
# $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/trunk/libsbml/src/bindings/ruby/test/annotation/TestModelHistory.rb $
#
# This test file was converted from src/sbml/test/TestModelHistory.c
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

class TestModelHistory < Test::Unit::TestCase

  def test_Date_create
    date = LibSBML::Date.new(2005,12,30,12,15,45,1,2,0)
    assert( date != nil )
    assert( date.getYear() == 2005 )
    assert( date.getMonth() == 12 )
    assert( date.getDay() == 30 )
    assert( date.getHour() == 12 )
    assert( date.getMinute() == 15 )
    assert( date.getSecond() == 45 )
    assert( date.getSignOffset() == 1 )
    assert( date.getHoursOffset() == 2 )
    assert( date.getMinutesOffset() == 0 )
    date = nil
  end

  def test_Date_createFromString
    dd =  "2012-12-02T14:56:11Z";
    date = LibSBML::Date.new(dd)
    assert( date != nil )
    assert ((  "2012-12-02T14:56:11Z" == date.getDateAsString() ))
    assert( date.getYear() == 2012 )
    assert( date.getMonth() == 12 )
    assert( date.getDay() == 2 )
    assert( date.getHour() == 14 )
    assert( date.getMinute() == 56 )
    assert( date.getSecond() == 11 )
    assert( date.getSignOffset() == 0 )
    assert( date.getHoursOffset() == 0 )
    assert( date.getMinutesOffset() == 0 )
    date = nil
  end

  def test_Date_getDateAsString
    dd =  "2005-02-02T14:56:11Z";
    date = LibSBML::Date.new(dd)
    assert( date != nil )
    assert( date.getYear() == 2005 )
    assert( date.getMonth() == 2 )
    assert( date.getDay() == 2 )
    assert( date.getHour() == 14 )
    assert( date.getMinute() == 56 )
    assert( date.getSecond() == 11 )
    assert( date.getSignOffset() == 0 )
    assert( date.getHoursOffset() == 0 )
    assert( date.getMinutesOffset() == 0 )
    date.setYear(2012)
    date.setMonth(3)
    date.setDay(28)
    date.setHour(23)
    date.setMinute(4)
    date.setSecond(32)
    date.setSignOffset(1)
    date.setHoursOffset(2)
    date.setMinutesOffset(32)
    assert ((  "2012-03-28T23:04:32+02:32" == date.getDateAsString() ))
    date = nil
  end

  def test_Date_setters
    date = LibSBML::Date.new(2005,12,30,12,15,45,1,2,0)
    assert( date != nil )
    date.setYear(2012)
    date.setMonth(3)
    date.setDay(28)
    date.setHour(23)
    date.setMinute(4)
    date.setSecond(32)
    date.setSignOffset(1)
    date.setHoursOffset(2)
    date.setMinutesOffset(32)
    assert( date.getYear() == 2012 )
    assert( date.getMonth() == 3 )
    assert( date.getDay() == 28 )
    assert( date.getHour() == 23 )
    assert( date.getMinute() == 4 )
    assert( date.getSecond() == 32 )
    assert( date.getSignOffset() == 1 )
    assert( date.getHoursOffset() == 2 )
    assert( date.getMinutesOffset() == 32 )
    assert ((  "2012-03-28T23:04:32+02:32" == date.getDateAsString() ))
    date = nil
  end

  def test_ModelCreator_create
    mc = LibSBML::ModelCreator.new()
    assert( mc != nil )
    mc = nil
  end

  def test_ModelCreator_setters
    mc = LibSBML::ModelCreator.new()
    assert( mc != nil )
    assert( mc.isSetFamilyName() == false )
    assert( mc.isSetGivenName() == false )
    assert( mc.isSetEmail() == false )
    assert( mc.isSetOrganisation() == false )
    mc.setFamilyName( "Keating")
    mc.setGivenName( "Sarah")
    mc.setEmail( "sbml-team@caltech.edu")
    mc.setOrganisation( "UH")
    assert ((  "Keating" == mc.getFamilyName() ))
    assert ((  "Sarah" == mc.getGivenName() ))
    assert ((  "sbml-team@caltech.edu" == mc.getEmail() ))
    assert ((  "UH" == mc.getOrganisation() ))
    assert( mc.isSetFamilyName() == true )
    assert( mc.isSetGivenName() == true )
    assert( mc.isSetEmail() == true )
    assert( mc.isSetOrganisation() == true )
    mc.unsetFamilyName()
    mc.unsetGivenName()
    mc.unsetEmail()
    mc.unsetOrganisation()
    assert ((  "" == mc.getFamilyName() ))
    assert ((  "" == mc.getGivenName() ))
    assert ((  "" == mc.getEmail() ))
    assert ((  "" == mc.getOrganisation() ))
    assert( mc.isSetFamilyName() == false )
    assert( mc.isSetGivenName() == false )
    assert( mc.isSetEmail() == false )
    assert( mc.isSetOrganisation() == false )
    assert( mc.isSetOrganization() == false )
    mc.setOrganization( "UH")
    assert ((  "UH" == mc.getOrganization() ))
    assert( mc.isSetOrganization() == true )
    mc.unsetOrganisation()
    assert ((  "" == mc.getOrganization() ))
    assert( mc.isSetOrganization() == false )
    mc = nil
  end

  def test_ModelHistory_addCreator
    history = LibSBML::ModelHistory.new()
    assert( history.getNumCreators() == 0 )
    assert( history != nil )
    mc = LibSBML::ModelCreator.new()
    assert( mc != nil )
    mc.setFamilyName( "Keating")
    mc.setGivenName( "Sarah")
    mc.setEmail( "sbml-team@caltech.edu")
    mc.setOrganisation( "UH")
    history.addCreator(mc)
    assert( history.getNumCreators() == 1 )
    mc = nil
    newMC = history.getListCreators().get(0)
    assert( newMC != nil )
    assert ((  "Keating" == newMC.getFamilyName() ))
    assert ((  "Sarah" == newMC.getGivenName() ))
    assert ((  "sbml-team@caltech.edu" == newMC.getEmail() ))
    assert ((  "UH" == newMC.getOrganisation() ))
    history = nil
  end

  def test_ModelHistory_addModifiedDate
    history = LibSBML::ModelHistory.new()
    assert( history != nil )
    assert( history.isSetModifiedDate() == false )
    assert( history.getNumModifiedDates() == 0 )
    date = LibSBML::Date.new(2005,12,30,12,15,45,1,2,0)
    history.addModifiedDate(date)
    date = nil
    assert( history.getNumModifiedDates() == 1 )
    assert( history.isSetModifiedDate() == true )
    newdate = history.getListModifiedDates().get(0)
    assert( newdate.getYear() == 2005 )
    assert( newdate.getMonth() == 12 )
    assert( newdate.getDay() == 30 )
    assert( newdate.getHour() == 12 )
    assert( newdate.getMinute() == 15 )
    assert( newdate.getSecond() == 45 )
    assert( newdate.getSignOffset() == 1 )
    assert( newdate.getHoursOffset() == 2 )
    assert( newdate.getMinutesOffset() == 0 )
    date1 = LibSBML::Date.new(2008,11,2,16,42,40,1,2,0)
    history.addModifiedDate(date1)
    date1 = nil
    assert( history.getNumModifiedDates() == 2 )
    assert( history.isSetModifiedDate() == true )
    newdate1 = history.getModifiedDate(1)
    assert( newdate1.getYear() == 2008 )
    assert( newdate1.getMonth() == 11 )
    assert( newdate1.getDay() == 2 )
    assert( newdate1.getHour() == 16 )
    assert( newdate1.getMinute() == 42 )
    assert( newdate1.getSecond() == 40 )
    assert( newdate1.getSignOffset() == 1 )
    assert( newdate1.getHoursOffset() == 2 )
    assert( newdate1.getMinutesOffset() == 0 )
    history = nil
  end

  def test_ModelHistory_create
    history = LibSBML::ModelHistory.new()
    assert( history != nil )
    assert( history.getListCreators() != nil )
    assert( history.getCreatedDate() == nil )
    assert( history.getModifiedDate() == nil )
    history = nil
  end

  def test_ModelHistory_setCreatedDate
    history = LibSBML::ModelHistory.new()
    assert( history != nil )
    assert( history.isSetCreatedDate() == false )
    date = LibSBML::Date.new(2005,12,30,12,15,45,1,2,0)
    history.setCreatedDate(date)
    assert( history.isSetCreatedDate() == true )
    date = nil
    newdate = history.getCreatedDate()
    assert( newdate.getYear() == 2005 )
    assert( newdate.getMonth() == 12 )
    assert( newdate.getDay() == 30 )
    assert( newdate.getHour() == 12 )
    assert( newdate.getMinute() == 15 )
    assert( newdate.getSecond() == 45 )
    assert( newdate.getSignOffset() == 1 )
    assert( newdate.getHoursOffset() == 2 )
    assert( newdate.getMinutesOffset() == 0 )
    history = nil
  end

  def test_ModelHistory_setModifiedDate
    history = LibSBML::ModelHistory.new()
    assert( history != nil )
    assert( history.isSetModifiedDate() == false )
    date = LibSBML::Date.new(2005,12,30,12,15,45,1,2,0)
    history.setModifiedDate(date)
    date = nil
    assert( history.isSetModifiedDate() == true )
    newdate = history.getModifiedDate()
    assert( newdate.getYear() == 2005 )
    assert( newdate.getMonth() == 12 )
    assert( newdate.getDay() == 30 )
    assert( newdate.getHour() == 12 )
    assert( newdate.getMinute() == 15 )
    assert( newdate.getSecond() == 45 )
    assert( newdate.getSignOffset() == 1 )
    assert( newdate.getHoursOffset() == 2 )
    assert( newdate.getMinutesOffset() == 0 )
    history = nil
  end

end
