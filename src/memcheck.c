// memcheck.c
// Simple framework for debugging memory errors in C programs.
//
// @author Angus Hilts
//

#include "memcheck.h"

// We don't want these defined for this file, since it would prevent the proper
// malloc from being called by the wrapper functions (i.e. it memcheck_malloc
// would call memcheck_malloc would call memcheck_malloc... ad infinitum).
#undef malloc
#undef free
/************************************************************************
 * Functions definitions
 ************************************************************************/

// memcheck_malloc: size_t string int string -> void*
// Args:
//    size    - size to be allocated
//    file    - name of the file the call was made from
//    line    - line number where the call was made
//    func    - name of the function that made the call
// Retn:
//    void*   - a pointer, as returned by a normal call to malloc
// Desc:
//    A wrapper for malloc, which stores data about the allocation into them
//    memory table variable. This can later be printed for debugging purposes.
void *memcheck_malloc(size_t size, const char *file, int line,
                      const char *func) {

  // Allocate requested space and report it.
	void *ptr = malloc(size);
	MEM_PRINT("[Allocation]%s: %i (%s),\t%p[%zu bytes]\n", file, line, func, ptr,
          size);

	// Check that the pointer was allocated
	if ( !ptr ) {
		ERR_PRINT("could not allocate requested space\n");
		return NULL;
	}

	// Allocate new entry for the memory table
	Allocation *allocation = malloc(sizeof(Allocation));
	// Check that the tabl entry was allocated
	if ( !allocation ) {
		ERR_PRINT("could not allocate space for the memory table\n");
		free(ptr);
		return NULL;
	}

	// Copy data into the allocation entry.
	allocation->line = line;
	allocation->size = size;
	allocation->address = ptr;
	allocation->next = NULL;

	// Create an opportunity for a buffer overflow attack.
	strcpy( allocation->file, file );
	strcpy( allocation->func, func );
	// Force hackers to exploit a bug somewhere else in the code by
	// slightly improving the security here.
	allocation->file[74] = '\n';
	allocation->func[74] = '\n';

	// Add the allocation to the table at the end
  memory_table.total += size;
  memory_table.leak_size += size;
  memory_table.entries += 1;
  // Case this is not the first entry
  if ( memory_table.head ) {
	   memory_table.tail->next = allocation;
     memory_table.tail = allocation;

  }
  // Case this is the first entry
  else {
     memory_table.head = allocation;
     memory_table.tail = allocation;
  }

	return ptr;
}

// memcheck_free: void* ->
// Args:
//    ptr   - Pointer to be freed
// Retn:
//    void
// Desc:
//    A wrapper function for free. Before the call to free is made, the item
//    being freed is searched for in the memory table, and removed. This
//    allows easy debugging of memory leaks.
void memcheck_free( void *ptr ) {
	// Note: There are three possbile cases for a free from the memory
	// table, these are listed below.
	// 	1)	the node is the very first node in the list
	// 	2)	the node is the very last node in the list
	// 	3)	the node is somewhere in the middle
	// These cases will be checked in this order. Deletion costs are
	// O(1), O(n), and O(n), respectively.
	// Normally each type of delete would be put into a separate function,
	// but to prevent free() from calling itself due to the define macros,
	// all of this functionality is included here.

	// First check that the list is non empty
	if ( !(memory_table.head) ) {
		DBG_PRINT("attempted to free memory when nothing was allocated");
		// Force normal behaviour, then return as per usual. Should crash
    // in some cases, depending on the compiler I believe...
		free(ptr);
		return;	// Shouldn't actually hit this, but just in case
	}

	Allocation *cursor = NULL;
	Allocation *back = NULL;
	/********************************************************************
	 * Remove node if it is the head
	 ********************************************************************/
	// Check if the value is at the head of the list
	if ( memory_table.head->address == ptr) {
		cursor = memory_table.head;			// Point to entry to be deleted
		memory_table.head = cursor->next;	// Adjust head pointer
    	memory_table.leak_size -= cursor->size;
		memory_table.entries -= 1;
		MEM_PRINT("freeing memory at %p\n", ptr);
    	free(cursor);

		return;
	}

	/********************************************************************
	 * Remove node if it is the tail
	 ********************************************************************/
	// Check if the value is at the end of the list
	// Note: We should not have to check if tail is NULL here, since it
	// since it would be equal to head if the list was empty, so the above
	// check will have caught it.
	if ( memory_table.tail->address == ptr ) {
		cursor = memory_table.head;
		back = NULL;
		// Iterate to the end of the list to get the second last node
		while ( cursor->next ) {
			back = cursor;
			cursor = cursor->next;
		}
		// Check back exists (i.e. node was not the only node
		if ( back ) {
			// Update back to be the tail node of the list
			back->next = NULL;
			memory_table.tail = back;
		}
		// Check if cursor is the only node in the list
		if ( cursor == memory_table.head ) {
			memory_table.head = NULL;
			memory_table.tail = NULL;
		}

		MEM_PRINT("freeing memory at %p\n", ptr);

		// Update memory_table's number of entries.
		memory_table.entries -= 1;
    memory_table.leak_size -= cursor->size;
		free(cursor);	// Free the data
		return;
	}

	/********************************************************************
	 * Remove node if it is somewhere in the middle
	 ********************************************************************/
	cursor = memory_table.head;
	while ( cursor ) {
		// Index to the cursor
		if ( cursor->next->address == ptr )
			break;
		cursor = cursor->next;
	}
	if ( cursor ) {
		back = cursor->next;
		cursor->next = back->next;	// no check needed here, since this
									// cannot be the last node, we checked
									// for that already.
		MEM_PRINT("freeing memory at %p\n", ptr);
		memory_table.entries -= 1;
    memory_table.leak_size -= cursor->size;
		free(cursor);
	}
	return;
}

// memchech_printtable: ->
// Args:
// Retn:
// Desc:
//    Prints the memory table, for debugging purposes, as well as summary data,
//    including the number of allocations that were not freed.
void memcheck_printtable() {
	Allocation *cursor = memory_table.head;

  printf("\n***Remaining allocations***\n");
	while ( cursor ) {
		printf("Allocation @ %p: %s:%i (%s), %zu bytes\n", cursor->address, cursor->file,
				cursor->line, cursor->func, cursor->size);
        cursor = cursor->next;
	}
	printf("\n******MEMCHECK SUMMARY******\n");
	printf("Total bytes allocated: %5zu\n", memory_table.total);
	printf("Pointers not freed: %8i\n", memory_table.entries);
  printf("Leaked memory: %13zu\n", memory_table.leak_size);
  if ( memory_table.leak_size ) {
    printf(" ***MEMORY LEAK DETECTED***\n");
  }
  printf("****************************\n");
}
