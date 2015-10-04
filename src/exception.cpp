/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2015 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      exception.cpp                                               //
//                                                                         //
//  Purpose:   Source file for Exception class                             //
//                                                                         //
//  Author(s): Sysoyev A.                                                  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include "exception.h"

// ------------------------------------------------------------------------------------------------
TException::TException(const char *_File, int _Line, const char *_Function, 
  const char *_Description)
{
  File = new char[strlen(_File) + 1];
  strcpy(File, _File);
  Line = _Line;
  Function = new char[strlen(_Function) + 1];
  strcpy(Function, _Function);
  Description = new char[strlen(_Description) + 1];
  strcpy(Description, _Description);
}

// ------------------------------------------------------------------------------------------------
TException::TException(const TException &e)
{
  File = new char[strlen(e.File) + 1];
  strcpy(File, e.File);
  Line = e.Line;
  Function = new char[strlen(e.Function) + 1];
  strcpy(Function, e.Function);
  Description = new char[strlen(e.Description) + 1];
  strcpy(Description, e.Description);
}

// ------------------------------------------------------------------------------------------------
TException::~TException()
{
  delete [] File;
  delete [] Function;
  delete [] Description;
}

// ------------------------------------------------------------------------------------------------
const char* TException::GetFile() const
{
  return File;
}

// ------------------------------------------------------------------------------------------------
int TException::GetLine() const
{
  return Line;
}

// ------------------------------------------------------------------------------------------------
const char* TException::GetFunction() const
{
  return Function;
}

// ------------------------------------------------------------------------------------------------
const char* TException::GetDescription() const
{
  return Description;
}
// - end of file ----------------------------------------------------------------------------------
