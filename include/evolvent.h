/*
* Copyright (C) 2015 University of Nizhni Novgorod
* This file is part of the Globalizer Light library, v 1.0
* 
* evolvent.h - header file for evolvent classes
* 
* This file may be used under the terms of the GNU Lesser General Public 
* License version 2.1 as published by the Free Software Foundation 
* and appearing in the file LICENSE.LGPL included in the packaging of this 
* file. Please review the following information to ensure the GNU Lesser 
* General Public License version 2.1 requirements will be met: 
* http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
*/

#ifndef __EVOLVENT_H__
#define __EVOLVENT_H__

#include "common.h"
//#include "extended.h"

// ------------------------------------------------------------------------------------------------
class TEvolvent
{
protected:
  int      m;             // accuracy of decomposition of hypercube
  int      N;             // dimension
  double   A[MaxDim];     // left and
  double   B[MaxDim];     // right bounds of search area

  double*  y;             // y point from hypercube [-1/2, 1/2]^N

  const double extNull; // = 0.0; //Extended(0.0);
  const double extOne;  // = 1.0; //Extended(1.0);
  const double extHalf; // = 0.5; //Extended(0.5);
  double nexpExtended;

  void CalculateNumbr(double *s, int *u, int *v, int *l);
  void CalculateNode(double is, int n, int *u, int *v, int *l);
  void transform_P_to_D(); // transformation from hypercube P to hyperinterval D
  void transform_D_to_P(); // transformation from hyperinterval D to hypercube P
  double* GetYOnX(const double& _x);
  double GetXOnY();
public:
  TEvolvent(int _N = 2, int _m = 10);
  virtual ~TEvolvent();
  void SetBounds(const double* _A, const double* _B);
  virtual void GetImage(const double& x, double* _y, int EvolventNum = 0);
  virtual void GetPreimages(double* _y, double *x);
};

class TShiftedEvolvent: public TEvolvent
{
protected:
  int    L; // number of evolvents - 1, 0 by default, means one evolvent is used
  double PowOf2[MaxDim * MaxL + 1]; // degrees of 2
public:
  TShiftedEvolvent(int _N = 2, int _m = 10, int _L = 0);
  virtual ~TShiftedEvolvent();
  virtual void GetImage(const double& x, double* _y, int EvolventNum = 0);
  virtual void GetPreimages(double* _y, double *x);
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
  TRotatedEvolvent(int _N = 2, int _m = 10, int _L = 1);
  virtual ~TRotatedEvolvent();
  virtual void GetImage(const double& x, double* _y, int EvolventNum = 0);
  virtual void GetPreimages(double* _y, double *x);
};

#endif
// - end of file ----------------------------------------------------------------------------------
