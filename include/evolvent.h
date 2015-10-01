/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2015 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      evolvent.h                                                  //
//                                                                         //
//  Purpose:   Header file for evolvent classes                            //
//                                                                         //
//  Author(s): Barkalov K., Sysoyev A.                                     //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#ifndef __EVOLVENT_H__
#define __EVOLVENT_H__

#include "common.h"
#include "extended.h"

// ------------------------------------------------------------------------------------------------
class TEvolvent
{
protected:
  int      m;             // accuracy of decomposition of hypercube
  int      N;             // dimension
  double   A[MaxDim];     // left and
  double   B[MaxDim];     // right bounds of search area

  double*  y;             // y point from hypercube [-1/2, 1/2]^N

  const Extended extNull; // = 0.0; //Extended(0.0);
  const Extended extOne;  // = 1.0; //Extended(1.0);
  const Extended extHalf; // = 0.5; //Extended(0.5);
  Extended nexpExtended;

  void CalculateNumbr(Extended *s, int *u, int *v, int *l);
  void CalculateNode(Extended is, int n, int *u, int *v, int *l);
  void transform_P_to_D(); // transformation from hypercube P to hyperinterval D
  void transform_D_to_P(); // transformation from hyperinterval D to hypercube P
  double* GetYOnX(const Extended& _x);
  Extended GetXOnY();
public:
  TEvolvent(int _N = 2, int _m = 10);
  virtual ~TEvolvent();
  void SetBounds(const double* _A, const double* _B);
  void GetImage(const Extended& x, double* _y);
};

class TShiftedEvolvent: public TEvolvent
{
protected:
  int    L; // number of evolvents - 1, 0 by default, means one evolvent is used
  double PowOf2[MaxDim * MaxL + 1]; // degrees of 2
public:
  TShiftedEvolvent(int _N = 2, int _m = 10, int _L = 0);
  virtual ~TShiftedEvolvent();
  void GetImage(const Extended& x, int EvolventNum, double* _y);
  void GetPreimages(double* _y, Extended *x);
};

class TRotatedEvolvent: public TEvolvent
{
protected:
  int L;          // number of evolvents, 1 by default, means one evolvent is used
  int PlaneCount; // current number of planes
  int Planes[MaxDim * (MaxDim - 1) / 2][2]; // axes array
  double PowOfHalf[MaxM + 2]; // degrees of 1/2

  void GetAllPlanes();
public:
  TRotatedEvolvent(int _N = 2, int _m = 10, int _L = 0);
  virtual ~TRotatedEvolvent();
  void GetImage(const Extended& x, int EvolventNum, double* _y);
  void GetPreimages(double* _y, Extended *x);
};

#endif
// - end of file ----------------------------------------------------------------------------------
