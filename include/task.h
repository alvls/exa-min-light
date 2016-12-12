/*
* Copyright (C) 2015 University of Nizhni Novgorod
* This file is part of the Globalizer Light library, v 1.0
* 
* task.h - header file for optimization task class
* 
* This file may be used under the terms of the GNU Lesser General Public 
* License version 2.1 as published by the Free Software Foundation 
* and appearing in the file LICENSE.LGPL included in the packaging of this 
* file. Please review the following information to ensure the GNU Lesser 
* General Public License version 2.1 requirements will be met: 
* http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
*/

#ifndef __TASK_H__
#define __TASK_H__

#include "common.h"
#include "problem_interface.h"

// ------------------------------------------------------------------------------------------------
class TTask
{
protected:
  int        N;              // полная размерность задачи
  double     A[MaxDim];      // левая граница области поиска
  double     B[MaxDim];      // правая граница области поиска
  int        NumOfFunc;      // число функционалов (последний - критерий)
  IProblem*  pProblem;       // указатель на саму задачу оптимизации
//  tFunction* Funcs;          // фунционалы
  int        FreeN;          // размерность подзадачи

  int        FixedN;         // число фиксированных размерностей
                             //   чем "ниже" уровень задача в дереве задач, тем больше FixedN
  double     FixedY[MaxDim]; // значения фиксированных переменных
                             // включая значения переменных, зафиксированных на уровнях выше
  double     OptimumValue;   // оптимальное значение целевой функции (определено, если известно из задачи)
  double     OptimumPoint[MaxDim]; //координаты глобального минимума целевой функции (определено, если известно)
  bool       IsOptimumValueDefined; //true, если в задаче известно оптимальное значение критерия
  bool       IsOptimumPointDefined; //true, если в задаче известна точка глобального минимума

  void CheckBounds() const;
public:
  TTask(int _N, int _FreeN, IProblem* _problem);
  ~TTask();
  void SetFixed(int _FixedN, double *_FixedY);
  int GetN() const { return N; }
  int GetFreeN() const { return FreeN; }
  int GetNumOfFunc() const { return NumOfFunc; }
  double* GetA() { return A; }
  double* GetB() { return B; }
  int GetFixedN() const { return FixedN; }
  double* GetFixedY() { return FixedY; }
  //tFunction* GetFuncs(){ return Funcs; }
  double GetOptimumValue() const { return OptimumValue; }
  const double* GetOptimumPoint() const { return OptimumPoint; }
  bool GetIsOptimumValueDefined() const { return IsOptimumValueDefined; }
  bool GetIsOptimumPointDefined() const { return IsOptimumPointDefined; }
  double CalculateFuncs(const double *y, int fNumber)
    { return pProblem->CalculateFunctionals(y, fNumber); }
};

#endif
// - end of file ----------------------------------------------------------------------------------
