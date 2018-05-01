// memcheck.h
// Simple framework for debugging memory errors in C programs.
//
// @author Angus Hilts
//

#ifndef memcheck_h
#define memcheck_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"

// If memcheck is enabled, include everthing (this is a bit redundant with the
// include guards, but it means that the user does not have to remove the
// #includes from all of the files, they only need to skip defining MEMCHECK)
#ifdef MEMCHECK
// Define macros to replace malloc and free
#define malloc(X) memcheck_malloc( X, __FILE__, __LINE__, __FUNCTION__ )
#define free(X) memcheck_free( X )

#endif /* MEMCHECK */

void memcheck_printtable();     // Prints the table of allocations
void *memcheck_malloc(size_t size, const char *file, int line,
                      const char *func);  // malloc wrapper
void memcheck_free( void *ptr );   // free wrapper

typedef struct allocation_t Allocation;
typedef struct memtable_t Memtable;

struct allocation_t {
  char file[75];    // store file name
  char func[75];    // store function name
  int line;         // store line number
  size_t size;      // store size of allocation being made
  void *address;    // store address of the allocation
  Allocation *next; //  stores pointer to next item in list
};

struct memtable_t {
  Allocation *head;   // top of the allocation list
  Allocation * tail;  // tail of the alloction list
  size_t total;       // total amount of space allocated (in bytes)
  size_t leak_size;   // store memory still not freed (i.e. leaking) in bytes
  uint32_t entries;   // number of allocations made
};

Memtable memory_table;   // global memory table, to be used memcheck.c

#endif /* memcheck_h */
