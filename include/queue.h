/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2015 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      queue.h                                                     //
//                                                                         //
//  Purpose:   Header file for priority queue class                        //
//                                                                         //
//  Author(s): Sysoyev A.                                                  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "common.h"

// ------------------------------------------------------------------------------------------------
struct TQueueElement
{
  double Key;
  void *pValue;
};

// ------------------------------------------------------------------------------------------------
// Приоритетная очередь на двоичной куче
class TPriorityQueue
{
protected:
  int MaxSize;
  int CurSize;
  TQueueElement *pMem;
  int GetIndOfMinElem();  // находит индекс минимального элемента в очереди
  void DeleteMinElem();   // удаляет минимальный элемент в очереди
  void ReBuild(int Index);
public:
  // размер очереди должен быть равен 2^k - 1
  TPriorityQueue(int _MaxSize = DefaultQueueSize);
  ~TPriorityQueue();
  int GetSize();
  bool IsEmpty();
  bool IsFull();
  // обычная вставка в очередь, пока она не полна
  //   если очередь полна, то вставка, только если новый элемент больше минимального в очереди
  // можно использовать этот метод только при перезаполнении очереди
  void Push(double key, void *value);
  // вставка, если новый элемент больше минимального в очереди
  //   если при этом очередь полна, то замещение минимального
  void PushWithPriority(double key, void *value);
  void Pop(double *key, void **value);
  void Clear();
};

#endif
// - end of file ----------------------------------------------------------------------------------
