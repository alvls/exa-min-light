/*
* Copyright (C) 2015 University of Nizhni Novgorod
* This file is part of the Globalizer Light library, v 1.0
* 
* task.cpp - source file for optimization task class
* 
* This file may be used under the terms of the GNU Lesser General Public 
* License version 2.1 as published by the Free Software Foundation 
* and appearing in the file LICENSE.LGPL included in the packaging of this 
* file. Please review the following information to ensure the GNU Lesser 
* General Public License version 2.1 requirements will be met: 
* http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
*/

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
