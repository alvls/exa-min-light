/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2013 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      Data.cpp                                                    //
//                                                                         //
//  Purpose:   Source file for search data classes                         //
//                                                                         //
//  Author(s): Sysoyev A., Barkalov K.                                     //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#include "data.h"
#include "exception.h"

bool operator<(const TSearchInterval& i1,const TSearchInterval& i2){return (i1.xl<i2.xl);}

// ------------------------------------------------------------------------------------------------
// TSearchData Methods
// ------------------------------------------------------------------------------------------------
TSearchData::TSearchData(TParameters _parameters, int _NumOfFuncs,int _MaxSize) : parameters(_parameters)
{
	MaxSize = _MaxSize;
	Count = 0;
	pRoot = pCur = NULL;
	pQueue = new TPriorityQueue();
	//
	NumOfFuncs = _NumOfFuncs;
	for(int i=0;i<NumOfFuncs;i++)
	{
		M[i] = parameters.M;			//Ќачальное значение оценок констант Ћипшица равно 1 
		Z[i] = MaxDouble;	//Ќачальное значение минимумов - максимальное
	}
}

// ------------------------------------------------------------------------------------------------
TSearchData::~TSearchData()
{
  DeleteTree(pRoot);
  delete pQueue;
}

// ------------------------------------------------------------------------------------------------
void TSearchData::Clear()
{
	DeleteTree(pRoot);
	Count = 0;
	pRoot = pCur = NULL;
	ClearQueue();
	for(int i=0;i<NumOfFuncs;i++)
	{
		M[i] = parameters.M;			//Ќачальное значение оценок констант Ћипшица равно 1 
		Z[i] = MaxDouble;	//Ќачальное значение минимумов - максимальное
	}
}
// ------------------------------------------------------------------------------------------------
void TSearchData::GetBestIntervals(TSearchInterval** intervals,int count)
{
	//«десь надо вз€ть count лучших характеристик их очереди
	//ќчередь пока одна - очередь глобальных характеристик
	for(int i=0;i<count;i++)
	{
		intervals[i] = GetIntervalWithMaxR();
	}
}

// ------------------------------------------------------------------------------------------------
void TSearchData::DeleteTree(TTreeNode *pNode)
{
  if (pNode != NULL)
  {
    DeleteTree(pNode->pLeft);
    DeleteTree(pNode->pRight);
    delete pNode;
  }
}

// ------------------------------------------------------------------------------------------------
unsigned char TSearchData::GetHeight(TTreeNode *p)
{
  return p ? p->Height: 0; 
}

// ------------------------------------------------------------------------------------------------
int TSearchData::GetBalance(TTreeNode *p)
{
  return GetHeight(p->pRight) - GetHeight(p->pLeft); 
}

// ------------------------------------------------------------------------------------------------
void TSearchData::FixHeight(TTreeNode *p)
{
  unsigned char hl = GetHeight(p->pLeft);
  unsigned char hr = GetHeight(p->pRight);
  p->Height = (hl > hr ? hl: hr) + 1;
}

// ------------------------------------------------------------------------------------------------
TTreeNode* TSearchData::RotateRight(TTreeNode *p)
{
  TTreeNode *pTmp = p->pLeft;
  p->pLeft = pTmp->pRight;
  pTmp->pRight = p;
  FixHeight(p);
  FixHeight(pTmp);

  return pTmp;
}

// ------------------------------------------------------------------------------------------------
TTreeNode* TSearchData::RotateLeft(TTreeNode *p)
{
  TTreeNode *pTmp = p->pRight;
  p->pRight = pTmp->pLeft;
  pTmp->pLeft = p;
  FixHeight(p);
  FixHeight(pTmp);

  return pTmp;
}

// ------------------------------------------------------------------------------------------------
TTreeNode* TSearchData::Balance(TTreeNode *p)
{
  FixHeight(p);
  if (GetBalance(p) == 2)
  {
    if (GetBalance(p->pRight) < 0)
      p->pRight = RotateRight(p->pRight);
    return RotateLeft(p);
  }
  if (GetBalance(p) == -2)
  {
    if (GetBalance(p->pLeft) > 0)
      p->pLeft = RotateLeft(p->pLeft);
    return RotateRight(p);
  }
  return p; // балансировка не нужна
}

// ------------------------------------------------------------------------------------------------
TTreeNode* TSearchData::Insert(TTreeNode *p, TSearchInterval &pInterval)
{
  if (!p)
  {
    // не безопасно, если будет несколько потоков
    pCur = new TTreeNode(pInterval);
    return pCur;
  }
  if (pInterval.xl == p->pInterval->xl)
    throw EXCEPTION("Interval already exists!");
  if (pInterval.xl < p->pInterval->xl)
    p->pLeft = Insert(p->pLeft, pInterval);
  else
//  if (pInterval.xl > p->pInterval->xl)
    p->pRight = Insert(p->pRight, pInterval);

  return Balance(p);
}

// ------------------------------------------------------------------------------------------------
//TTreeNode* TSearchData::Find(Extended x)
TTreeNode* TSearchData::Find(TTreeNode *p, Extended x)
{
  TTreeNode *res;
  if (!p)
    return p;
  if (x < p->pInterval->xl)
    res = Find(p->pLeft, x);
  else if (x > p->pInterval->xl)
    res = Find(p->pRight, x);
  else
    res = p;

  return res;
}

// ------------------------------------------------------------------------------------------------
//TTreeNode* TSearchData::Find(Extended x)
/*
TTreeNode* TSearchData::FindR(TTreeNode *p, Extended x)
{
  TTreeNode *res;
  if (!p)
    return p;
  if (x < p->pInterval->xr)
    res = Find(p->pLeft, x);
  else if (x > p->pInterval->xr)
    res = Find(p->pRight, x);
  else
    res = p;

  return res;
}
*/
// ------------------------------------------------------------------------------------------------
TSearchInterval* TSearchData::InsertInterval(TSearchInterval &pInterval)
{
  pRoot = Insert(pRoot, pInterval);
  Count++;
  return pCur->pInterval;
}

// ------------------------------------------------------------------------------------------------
void TSearchData::UpdateInterval(TSearchInterval &pInterval)
{
  pCur = Find(pRoot, pInterval.xl);
  if (pCur)
  {
    (*pCur->pInterval) = pInterval;
  }
}

// ------------------------------------------------------------------------------------------------
//  TSearchInterval* GetIntervalByX(Extended x);
TSearchInterval* TSearchData::GetIntervalByX(Extended x)
{
  pCur = Find(pRoot, x);
  if (pCur)
    return pCur->pInterval;
  else
    return NULL;
}

// ------------------------------------------------------------------------------------------------
TSearchInterval* TSearchData::Reset()
{
  TTreeNode *pNode = pCurIter = pRoot;
  CurIndex = 0;

  while (!Stack.empty())
    Stack.pop();
  while (pNode != NULL)
  { 
    Stack.push(pNode);
    pCurIter = pNode;
    pNode = pNode->pLeft;
  }
  if (pCurIter)
    return pCurIter->pInterval;
  else 
    return NULL;
}

// ------------------------------------------------------------------------------------------------
TSearchInterval* TSearchData::GetNext()
{
  if (!IsEnd())
  {
    TTreeNode *pNode = pCurIter = pCurIter->pRight;
    Stack.pop();
    while (pNode != NULL)
    {
      Stack.push(pNode);
      pCurIter = pNode;
      pNode = pNode->pLeft;
    }
    if ((pCurIter == NULL) && !Stack.empty())
      pCurIter = Stack.top();
    CurIndex++;
    if (pCurIter)//ј не надо ли тут pCurIter?
      return pCurIter->pInterval;
    else 
      return NULL;
  }
    else 
      return NULL;
  }
/*
// ------------------------------------------------------------------------------------------------
TSearchInterval* TSearchData::GetPrev(TSearchInterval &pInterval)
{
// ищем интервал, у которого pInterval.xl €вл€етс€ правой границей
//   это и будет предыдущий 
// реализаци€ не оптимальна (но и не безумна€, благодар€ сбалансированности дерева
//   чтобы сделать лучше, нужно перестраивать дерево (например, добавл€ть указатель на предка)
  if (CurIndex == 0)
    return NULL;
  pCur = FindR(pRoot, pInterval.xl);
  if (pCur)
    return pCur->pInterval;
  else
    return NULL;
}
*/
// ------------------------------------------------------------------------------------------------
bool TSearchData::IsEnd()
{
  return CurIndex == Count;
}

// ------------------------------------------------------------------------------------------------
TSearchInterval* TSearchData::GetIntervalWithMaxR()
{
  TSearchInterval *pRes = NULL;
  if (pQueue->IsEmpty() || pQueue->GetSize()==1)
    RefillQueue();
//  else
  PopFromQueue(&pRes);
  return pRes;
}

// ------------------------------------------------------------------------------------------------
void TSearchData::RefillQueue()
{
  TSearchInterval *p;

  pQueue->Clear(); // ≈сли очередь уже была пуста, то вызов лишний, но он из одного действи€, так
                   //   что ставить проверку нет смысла
  // ќбход всех интервалов, вставка их в очередь
  //   Push() сначала заполн€ет очередь, потом вставл€ет с замещением
  for (p = Reset(); !IsEnd(); p = GetNext())
    pQueue->Push(p->R, p);
}

// ------------------------------------------------------------------------------------------------
void TSearchData::PushToQueue(TSearchInterval *pInterval)
{
	//Ќа начальном этапе в очередь записываем все данные
	if( Count <= DefaultQueueSize ) pQueue->Push(pInterval->R, pInterval);
	else
		pQueue->PushWithPriority(pInterval->R, pInterval);
}

// ------------------------------------------------------------------------------------------------
bool TSearchData::IsQueueEmpty()
{
  return pQueue->IsEmpty();
}

// ------------------------------------------------------------------------------------------------
bool TSearchData::IsQueueFull()
{
  return pQueue->IsFull();
}

// ------------------------------------------------------------------------------------------------
void TSearchData::PopFromQueue(TSearchInterval **pInterval)
{
  void *p;
  double R;
  pQueue->Pop(&R, &p);
  *pInterval = (TSearchInterval*)p;
}

// ------------------------------------------------------------------------------------------------
void TSearchData::ClearQueue()
{
  pQueue->Clear();
}
// ------------------------------------------------------------------------------------------------
int TSearchData::GetCount()
{
  return Count;
}
