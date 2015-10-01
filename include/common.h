/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2015 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      common.h                                                    //
//                                                                         //
//  Purpose:   Common Header file                                          //
//                                                                         //
//  Author(s): Sysoyev A., Barkalov K.                                     //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#ifndef __COMMON_H__
#define __COMMON_H__

/* ============================================================================================= *\
**  Constants                                                                                    **
\* ============================================================================================= */

//const int MaxPathLength = 512
const int MaxNumOfTaskLevels = 5;
const int MaxNumOfFunc = 20;
const int MaxDim = 50;
const int MaxM = 15;
const int MaxL = 10;

const double MaxDouble = 1.7e308;

const int DefaultQueueSize = 16777215;//8388607;//1048573;//8388607;//524287; //262143; // должно быть равно 2^k - 1
const int DefaultSearchDataSize = 100000;

const int TagChildStartSolve = 101;
const int TagChildSolved  = 102;
const int ChildStopMsg = -101;

/* ============================================================================================= *\
**  Types                                                                                        **
\* ============================================================================================= */
//typedef double (*TFuncPointer)(const double*, int);

class TProcess;
#ifdef WIN32
typedef void (__cdecl *tIterationHandler)(TProcess *pProcess);
typedef double (__cdecl *tFunction)(const double*);
#else
typedef void ( *tIterationHandler)(TProcess *pProcess);
typedef double ( *tFunction)(const double*);
#endif



#endif
// - end of file ----------------------------------------------------------------------------------
