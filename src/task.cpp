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

#include "exception.h"
#include "task.h"
#include <cstring>

// ------------------------------------------------------------------------------------------------
TTask::TTask(int _N, int _FreeN, IProblem *_problem)
{
  if ((_N <= 0) || (_N > MaxDim))
    throw EXCEPTION("N is out of range");
  N = _N;
  if ((_FreeN <= 0) || (_FreeN > N))
    throw EXCEPTION("FreeN is out of range");
  FreeN = _FreeN;
  NumOfFunc = _problem->GetNumberOfFunctions();
  if ((NumOfFunc <= 0) || (NumOfFunc > MaxNumOfFunc))
    throw EXCEPTION("NumOfFunc is out of range");
  _problem->GetBounds(A, B);
  IsOptimumPointDefined = _problem->GetOptimumPoint(OptimumPoint) == IProblem::OK ? true : false;
  IsOptimumValueDefined = _problem->GetOptimumValue(OptimumValue) == IProblem::OK ? true : false;
  pProblem = _problem;
  if (A == NULL)
    throw EXCEPTION("Pointer A is NULL");
  if (B == NULL)
    throw EXCEPTION("Pointer B is NULL");
  if (pProblem == NULL)
    throw EXCEPTION("Pointer pProblem is NULL");

  // По умолчанию фиксированные переменные отсутствуют
  FixedN = 0;
}

// ------------------------------------------------------------------------------------------------
TTask::~TTask()
{
}

// ------------------------------------------------------------------------------------------------
void TTask::SetFixed(int _FixedN, double *_FixedY)
{
  /*if (_FixedN != N - FreeN)
  {
    throw EXCEPTION("Not correct FixedN");
  }*/
  FixedN = _FixedN;
  if (_FixedY == NULL)
    throw EXCEPTION("Pointer FixedY is NULL");
  memcpy(FixedY, _FixedY, FixedN * sizeof(double));
}
// - end of file ----------------------------------------------------------------------------------
