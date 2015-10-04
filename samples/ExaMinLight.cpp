/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2015 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      Main.cpp                                                    //
//                                                                         //
//  Purpose:   Console version of ExaMin system                            //
//                                                                         //
//  Author(s): Sysoyev A., Barkalov K.                                     //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////


//#include <exception>
//#include <cstdlib>
#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

//#define _USE_MATH_DEFINES
//#include <math.h>

//#ifdef WIN32
//#include <windows.h>
//#endif

#include "common.h"
#include "exception.h"

/*
// ------------------------------------------------------------------------------------------------
double func(const double *y, int N)
{
double f;
int i;

f =10*N;
for(i=0 ; i < N; ++i)
{
//f += ((y[i]-(N-i)/(double)N)*(y[i]-(N-i)/(double)N) - 10 * cos(2 * M_PI * (y[i]-(N-i)/(double)N)));
f += ((y[i])*(y[i]) - 10 * cos(2 * M_PI * (y[i])));
}

return f;
}

double function(const double *y)
{
double res;// = (y[0]-0.1)*(y[0]-0.1)+0.1;

res = func(y, 3);

return res;
}*/


int main(int argc, char* argv[])
{
//  double A[MaxDim] = {-1.1, -1.1, -1.1, -1.1, -1.1, -1.1, -1.1, -1.1, -1, -1, -1, -1, -1, -1, -1, -1};
//  double B[MaxDim] = {1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1, 1, 1, 1, 1, 1, 1, 1};

//  TProcess *Process;

//#ifdef WIN32
//  unexpected_function prev, cur;
//  cur = &Unexpected;
//  prev = set_unexpected(cur);
//  set_terminate(Terminate);
//#endif
  try
  {
    //if (parameters.TypeProcess == SynchronousProcess)
    //  Process = new TProcess(A, B, NumOfFunc, F, parameters);
    //if (parameters.TypeProcess == SynchronousProcessNew)
    //  Process = new TNewProcess(A, B, NumOfFunc, F, parameters);
    //if (parameters.TypeProcess == AsynchronousProcess)
    //  Process = new TAsyncProcess(A, B, NumOfFunc, F, parameters);

    //Process->Solve();
    //delete Process;
  }
  catch(TException e)
  {
    printf("\nEXCEPTION in file: %s, line %d, function: %s", e.GetFile(), e.GetLine(),
      e.GetFunction());
    printf("\nDESCRIPTION: %s", e.GetDescription());

    //char ExcFname[256];
    //sprintf(ExcFname, "exception_%d.txt", ProcRank);
    //FILE* pException = fopen(ExcFname, "w");
    //if (pException != NULL)
    //{
    //  fprintf(pException, "EXCEPTION in file: %s, line: %d, function: %s",
    //    e.GetFile(), e.GetLine(), e.GetFunction());
    //  fprintf(pException, "\nDESCRIPTION: %s\n", e.GetDescription());
    //  fclose(pException);
    //}
    return 1;
  }
  catch(...)
  {
    printf("\nUNKNOWN EXCEPTION !!!");
    //char ExcFname[256];
    //sprintf(ExcFname, "exception_%d.txt", ProcRank);
    //FILE* pException = fopen(ExcFname, "w");
    //if (pException != NULL)
    //{
    //  fprintf(pException, "\nUNKNOWN EXCEPTION");
    //  fclose(pException);
    //}
    return 1;
  }

  return 0;
}
// - end of file ----------------------------------------------------------------------------------
