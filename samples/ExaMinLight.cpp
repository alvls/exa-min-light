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


#include <mpi.h>
#include <exception>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _USE_MATH_DEFINES
#include <math.h>

#ifdef WIN32
#include <windows.h>
#endif

#include "common.h"
#include "process.h"
#include "process_new.h"
#include "process_async.h"
#include "exception.h"

#include "parameters.h"



#include "problems.h"



// ------------------------------------------------------------------------------------------------
void Unexpected()
{
  printf("\nUNEXPECTED EXCEPTION !!!");
  throw 0;
}

// ------------------------------------------------------------------------------------------------
void Terminate()
{
  printf("\nUNEXPECTED EXCEPTION !!!");
  abort();
}

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

// ------------------------------------------------------------------------------------------------

void SetDeviceIndex(TParameters& par)
{

  int ProcRank, ProcNum;

  if (MPI_Comm_size(MPI_COMM_WORLD, &ProcNum) != MPI_SUCCESS)
  {
    throw EXCEPTION("Error in MPI_Comm_size call");
  }
  if (MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank) != MPI_SUCCESS)
  {
    throw EXCEPTION("Error in MPI_Comm_rank call");
  }
  //определение устройства для процесса
  //printf("PR=%d\n", ProcRank);
  MPI_Status status;
  unsigned long size = 256;
  char* CompName = new char [size];
  for (unsigned long i = 0; i < size; i++)
    CompName[i] = 0;


#ifdef WIN32
  LPWSTR buffer = new wchar_t [size];
  GetComputerNameW( buffer, &size );
  for (unsigned long i = 0; i < size; i++)
    CompName[i] = (char)buffer[i];
#else
  char hostname[256];
  gethostname(hostname, 256);
  size = (unsigned long)strlen(hostname);
  for (unsigned long i = 0; i < size; i++)
    CompName[i] = (char)hostname[i];
#endif

  //printf( "%s\tPR=%d\n", CompName, ProcRank );
  int err = 0;
  //printf( "\n\n");
  if (ProcRank == 0)
  {
    char** allCompName = new char* [ProcNum];

    for (int i = 1; i < ProcNum; i++)
    {
      MPI_Recv(&size, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);

      allCompName[i] = new char [size];
      //printf( "%d\t%d\n", i, size );


      MPI_Recv(allCompName[i], size, MPI_CHAR, i, 0,
        MPI_COMM_WORLD, &status);

      //printf( "%d\t%s\n", i, allCompName[i] );
    }

    int* deviceIndex = new int [ProcNum];
    bool* isProcessed = new bool [ProcNum];

    for (int i = 0; i < ProcNum; i++)
    {
      deviceIndex[i] = -1;
      isProcessed[i] = false;
    }

    string curComp = "";
    int curCID = 0;

    for (int i = 1; i < ProcNum; i++)
    {
      if (isProcessed[i])
        continue;
      curComp = allCompName[i];
      curCID = 0;
      deviceIndex[i] = curCID;
      isProcessed[i] = true;
      for (int j = i + 1; j < ProcNum; j++)
      {
        if (isProcessed[j])
          continue;
        if (curComp == allCompName[j])
        {
          curCID++;
          deviceIndex[j] = curCID;
          isProcessed[j] = true;
          //err = MPI_Send(&curCID, j, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
          //printf("pr = %d, deviceIndex = %d\n", j, curCID);
        }
      }
    }

    for (int i = 1; i < ProcNum; i++)
    {
      err = MPI_Send(&deviceIndex[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    }

  }
  else
  {
    err = MPI_Send(&size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    err = MPI_Send(CompName, size, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    int deviceIndex = -1;
    MPI_Recv(&deviceIndex, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

    printf("%s\tProcRank = %d\tdeviceIndex = %d\n", CompName, ProcRank, deviceIndex);

    par.deviceIndex = deviceIndex;
  }

  ////
}

int main(int argc, char* argv[])
{
  N_func_def();
  int NumOfFunc = 1;
#ifdef SET_NUM_FUNCTION
  NumOfFunction_func_def();
  NumOfFunc = NumOfFunction;
  tFunction F[MaxNumOfFunc];
  GetFunction(F);
#else
  tFunction F[MaxNumOfFunc] = {objfn};//{function};
#endif

  TParameters parameters(argc, argv, N);

  if (!parameters.isHaveLinc && !parameters.isStartWithoutArguments)
    return 0;

  // задача
#ifdef NEED_INITIALIZE

#ifdef GKLS
  InitFunc(parameters.func_num, parameters.GKLS_global_dist, parameters.GKLS_global_radius);
  parameters.InitGKLSParam( GKLS_domain_left,
    GKLS_domain_right,
    GKLS_dim,
    GKLS_num_minima,
    GKLS_minima,
    GKLS_glob);
  parameters.GKLS_global_value = GKLS_global_value;
  parameters.GKLS_global_cor = GKLS_minima.local_min[1];
  double zzz = GKLS_norm(GKLS_domain_left, GKLS_domain_right);
#endif
#endif

  //int TaskDim = N;

  double A[MaxDim] = {-1.1, -1.1, -1.1, -1.1, -1.1, -1.1, -1.1, -1.1, -1, -1, -1, -1, -1, -1, -1, -1};
  double B[MaxDim] = {1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1, 1, 1, 1, 1, 1, 1, 1};

  bounds(A, B); // Границы поиска

  int ProcRank, ProcNum;
  int i;

  TProcess *Process;

  MPI_Init(&argc, &argv);

  if (MPI_Comm_size(MPI_COMM_WORLD, &ProcNum) != MPI_SUCCESS)
  {
    throw EXCEPTION("Error in MPI_Comm_size call");
  }
  if (MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank) != MPI_SUCCESS)
  {
    throw EXCEPTION("Error in MPI_Comm_rank call");
  }
  //определение устройства для процесса
  SetDeviceIndex(parameters);
#ifdef WIN32
  unexpected_function prev, cur;
  cur = &Unexpected;
  prev = set_unexpected(cur);
  set_terminate(Terminate);
#endif
  try
  {
    if (parameters.TypeProcess == SynchronousProcess)
      Process = new TProcess(A, B, NumOfFunc, F, parameters);
    if (parameters.TypeProcess == SynchronousProcessNew)
      Process = new TNewProcess(A, B, NumOfFunc, F, parameters);
    if (parameters.TypeProcess == AsynchronousProcess)
      Process = new TAsyncProcess(A, B, NumOfFunc, F, parameters);

    Process->Solve();
    delete Process;
  }
  catch(TException e)
  {
    printf("\nEXCEPTION in file: %s, line %d, function: %s", e.GetFile(), e.GetLine(),
      e.GetFunction());
    printf("\nDESCRIPTION: %s", e.GetDescription());

    char ExcFname[256];
    sprintf(ExcFname, "exception_%d.txt", ProcRank);
    FILE* pException = fopen(ExcFname, "w");
    if (pException != NULL)
    {
      fprintf(pException, "EXCEPTION in file: %s, line: %d, function: %s",
        e.GetFile(), e.GetLine(), e.GetFunction());
      fprintf(pException, "\nDESCRIPTION: %s\n", e.GetDescription());
      fclose(pException);
    }
    for (i = 0; i < ProcNum; i++)
      if (i != ProcRank)
        MPI_Abort(MPI_COMM_WORLD, i);
    return 1;
  }
  catch(...)
  {
    printf("\nUNKNOWN EXCEPTION !!!");
    char ExcFname[256];
    sprintf(ExcFname, "exception_%d.txt", ProcRank);
    FILE* pException = fopen(ExcFname, "w");
    if (pException != NULL)
    {
      fprintf(pException, "\nUNKNOWN EXCEPTION");
      fclose(pException);
    }
    for (i = 0; i < ProcNum; i++)
      if (i != ProcRank)
        MPI_Abort(MPI_COMM_WORLD, i);
    return 1;
  }

  MPI_Finalize();
#ifdef NEED_INITIALIZE
  FreeFunc();
#endif
  return 0;
}
// - end of file ----------------------------------------------------------------------------------
