/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2015 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      exception.h                                                 //
//                                                                         //
//  Purpose:   Header file for exception handling class                    //
//                                                                         //
//  Author(s): Sysoyev A.                                                  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

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
