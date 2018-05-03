//
//  debug.h
//  BNA Fasta parser
//
//  Created by Angus Hilts on 2017-07-10.
//  Copyright © 2017 Angus Hilts. All rights reserved.
//
// This module contains different macros for printing debugging infomration
// based on defined preprocessor variables. Each variable represents a different
// level of debugging. The levels are given below, where 1 yields the least
// information and 3 yields the most information.
//  1 (LOG)   - prints logging informatin. LOG_PRINT should be used if the
//              information will be relevant for the end user.
//  2 (DEBUG) - prints debugging informatin. DBG_PRINT should be used if the
//              inforation is relevant for debugging the program.
//  3 (ERR)   - prints information on errors. ERR_PRINT should be used when
//              some error in program use has occurred, such as failed
//              allocations, incorrect parameters, etc.
// Note: The above levels may change, since they are somewhat of misnomers. The
// ERR flag in particular seems to evoke a feeling of problems that COULD be
// relevant to the end user (i.e. to let them know that things did not work).
// DEBUG makes sense where it is at, but the levels should perhaps be something
// to the effect of LOG, ERR, DEBUG, DEBUG_VERBOSE. This may come in a future
// update.

#include <stdio.h>
#include <stdlib.h>

#ifndef debug_h
#define debug_h

/* logging */
#if defined LOG || defined DEBUG || defined ERR
#define LOG_PRINT(message, ...)                                         \
    do {                                                                \
        fprintf(stdout, "\(LOG)\t");                                    \
        fprintf(stdout, message, ##__VA_ARGS__);                        \
    } while (0)
#else
#define LOG_PRINT(message, ...)
#endif	/* logging */

/* debugging */
#if defined DEBUG || defined ERR
#define DBG_PRINT(fmt, args...)                                         \
    do {                                                                \
        fprintf(stderr, "%s:%d:%s(): " fmt,                             \
                __FILE__, __LINE__, __func__, ##args);                  \
    } while (0)
#else
#define DBG_PRINT(fmt, args...)
#endif /* debugging */

/* error */
#ifdef ERR
#define ERR_PRINT(fmt, args...)										\
	do {																            \
		fprintf(stderr, "\(ERR)\t");								  \
		fprintf(stderr, "%s:%d:%s(): " fmt,						\
				__FILE__, __LINE__, __func__, ##args);		\
	} while (0)
#else
#define ERR_PRINT(fmt, args...)
#endif /* error */

#ifdef VERMEM
#define MEM_PRINT(fmt, args...)       \
  do {                                \
    printf(fmt, ##args);             \
  } while (0)
#else
#define MEM_PRINT(fmt, args...)
#endif
#endif /* debug_h */
