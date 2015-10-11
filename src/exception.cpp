/*
* Copyright (C) 2015 University of Nizhni Novgorod
* This file is part of the Globalizer Light library, v 1.0
* 
* exception.cpp - source file for Exception class
* 
* This file may be used under the terms of the GNU Lesser General Public 
* License version 2.1 as published by the Free Software Foundation 
* and appearing in the file LICENSE.LGPL included in the packaging of this 
* file. Please review the following information to ensure the GNU Lesser 
* General Public License version 2.1 requirements will be met: 
* http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
*/

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
