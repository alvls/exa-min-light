/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2015 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      task.cpp                                                    //
//                                                                         //
//  Purpose:   Source file for optimization task class                     //
//                                                                         //
//  Author(s): Sysoyev A., Barkalov K.                                     //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#include "string.h"
#include "exception.h"
#include "task.h"

// ------------------------------------------------------------------------------------------------
TTask::TTask(int _N, int _FreeN, int _NumOfFunc, double *_A, double *_B, const tFunction *_Funcs)
{
  N = _N;
  FreeN = _FreeN;
  NumOfFunc = _NumOfFunc;
  memcpy(A, _A, N * sizeof(double));
  memcpy(B, _B, N * sizeof(double));
  Funcs = new tFunction[NumOfFunc];
  if (Funcs == NULL)
    throw EXCEPTION("Not enough memory to store Funcs");
  memcpy(Funcs, _Funcs, NumOfFunc * sizeof(tFunction));

  // По умолчанию фиксированные переменные отсутствуют
  FixedN =  0;
}

// ------------------------------------------------------------------------------------------------
TTask::~TTask()
{
  delete [] Funcs;
}

// ------------------------------------------------------------------------------------------------
void TTask::SetFixed(int _FixedN, double *_FixedY)
{
  FixedN = _FixedN;
  memcpy(FixedY, _FixedY, FixedN * sizeof(double));
}
// - end of file ----------------------------------------------------------------------------------
