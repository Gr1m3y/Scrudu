//
//  debug.h
//  BNA Fasta parser
//
//  Created by Angus Hilts on 2017-07-10.
//  Copyright © 2017 Angus Hilts. All rights reserved.
//

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

#ifdef MEMCHECK
#define MEM_PRINT(fmt, args...)       \
  do {                                \
    fprintf(fmt, ##args);             \
  } while (0)
#else
#define MEM_PRINT(fmt, args...)
#endif
#endif /* debug_h */
