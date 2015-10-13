/*
* Copyright (C) 2015 University of Nizhni Novgorod
* This file is part of the Globalizer Light library, v 1.0
* 
* exception.h - header file for exception handling class
* 
* This file may be used under the terms of the GNU Lesser General Public 
* License version 2.1 as published by the Free Software Foundation 
* and appearing in the file LICENSE.LGPL included in the packaging of this 
* file. Please review the following information to ensure the GNU Lesser 
* General Public License version 2.1 requirements will be met: 
* http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
*/

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

// ------------------------------------------------------------------------------------------------
class TException
{
private:
  char *File;
  int Line;
  char *Function;
  char *Description;
public:
  TException(const char *_File, int _Line, const char *_Function, const char *_Description);
  TException(const TException &e);
  ~TException();
  const char* GetFile() const;
  int GetLine() const;
  const char* GetFunction() const;
  const char* GetDescription() const;
};

#define EXCEPTION(msg) TException(__FILE__, __LINE__, __FUNCTION__, msg)

#endif // __EXCEPTION_H__
// - end of file ----------------------------------------------------------------------------------
