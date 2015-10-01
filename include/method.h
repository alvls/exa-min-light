/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2015 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      method.h                                                    //
//                                                                         //
//  Purpose:   Header file for method class                                //
//                                                                         //
//  Author(s): Barkalov K., Sysoyev A.                                     //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#ifndef __METHOD_H__
#define __METHOD_H__

#include "common.h"
#include "task.h"
#include "data.h"
#include "evolvent.h"
//#include "parameters.h"

// ------------------------------------------------------------------------------------------------
class TMethod
{
protected:
  int               MaxNumOfTrials;   // максимальное число итераций (испытаний)
  int               IterationCount;   // число выполненных итераций
  double            Epsilon;              // точность решени€ задачи
  double            AchievedAccuracy; // достигнута€ точность
  double            r;                // надежность метода (> 1)
  int               m;                // плотность построени€ развертки (точность 1/2^m по к-те)
  double            reserv;           // параметр eps-резервировани€, 0<=reserv<=0.1
  int               L;                // 1 <= число разверток (<= m - дл€ сдвиговой)
  int               CurL;             // номер текущей развертки - нумераци€ с 0
  int               NumPoints;        // число точек, порождаемых методом на 1 итерации
//  EMapType          MapType;          // тип развертки (сдвигова€, вращаема€)
  bool              recalc;           // истина, если нужен пересчет характеристик

  TTask             *pTask;
  TSearchData       *pData;
  TEvolvent         *Evolvent;        // развертка

  tIterationHandler OnIteration;

  TTrial            *pCurTrials;
  TTrial            BestTrial;

//  TParameters parameters;             // параметры метода

  TSearchInterval** BestIntervals;    // массив указателей на лучше интервалы (лева€!!! точка)

  int alfa;                           //  оэффициент локальной адаптации, от 1(глоб.) до 20(лок.) поиск

  //»нициализаци€ чисел с расширенной точностью
  virtual void InitAutoPrecision();
  //¬ычисление "глобальной" характеристики
  virtual double CalculateGlobalR(TSearchInterval* i);
  //¬ычисление "локальной" характеристики - должна быть вычислена глобальна€!!!
  virtual double CalculateLocalR(TSearchInterval *p);
  //¬ычисление оценки константы Ћипшица
  virtual void CalculateM(TSearchInterval* p);
public:
  TMethod(int _MaxNumOfTrials, double _Eps, double _r, double _reserv, int _m, int _L, int _CurL, 
    /*EMapType _MapType, /*TParameters _parameters, */TTask *_pTask, TSearchData *_pData);
  virtual ~TMethod();
  /*
  void SetTask(TTask *_pTask);
  void SetSearchData(TSearchData *_pData);
  void SetEstimation(TOptimEstimation *_pEstimation);
  */
  void SetIterationHandler(tIterationHandler _OnIteration);

  void FirstIteration();
  void InitIteration();
  //  void ReceiveLockPoints();
  void CalculateIterationPoints();
  bool CheckStopCondition();
  virtual void CalculateFunctionals();
  //  void ReceiveCalcPoints();
  void RenewSearchData();
  void EstimateOptimum();
  void IterationHandler(TProcess *pProcess); // call-back функци€ дл€ обработки результатов итерации метода
  void FinalizeIteration();
  int GetIterationCount(){return IterationCount;}

  TTrial GetOptimEstimation();
  TTrial* GetCurTrials();
  void SetBounds();
  //—бор статистики
  int GetNumberOfTrials();
  double GetMu();
  //Ћокальное уточнение из текущей лучшей точки
  void LocalSearch();

  void SetNumPoints(int _NumPoints);
  int GetNumPoints();
  TSearchInterval **GetBestIntervals();

  //отладка
  int pn;
};

#endif
// - end of file ----------------------------------------------------------------------------------
