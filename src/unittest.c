// unittest.c
// Based on MinUnit
// http://www.jera.com/techinfo/jtns/jtn002.html
//
// @author Angus Hilts
//
// Simple unit test framework for C

#include <stdio.h>
#include <string.h>
#include "unittest.h"
#include "memcheck.h"

// Unit Testing summary data
int tests_run = 0;
int tests_passed = 0;
int tests_failed = 0;
int asserts_passed = 0;
int asserts_failed = 0;

// Sample functions
int square(int x) {
	return x*x;
}

// WRITE TESTS HERE
/*******************************************************************/

// Example
int square_test() {
	ut_assert( square(3) == 9 );
	return 0;
}

/*******************************************************************/

int main(int argc, char **argv) {

	printf("Starting test driver...\n\n");

	/*******************************************************************/
	// RUN TESTS HERE

	ut_run( square_test );
	void *test = malloc(sizeof(int));
	free(test);

	/*******************************************************************/
	printf("\n**********RESULTS**********\n");

	if ( tests_run ) {
		printf("Tests run: %16d\n", tests_run);
		printf("Tests passed: %13d\n", tests_passed);
		printf("Tests failed: %13d\n", tests_failed);
		printf("%3.1f%% of tests passed.\n\n", 100*(double)tests_passed/tests_run);
	} else {
		printf("No tests were run.\n\n");
	}

	memcheck_printtable();

	return tests_failed;
}

/************************************************************************
 * Testing Functions, do not modify code below this line.
 ************************************************************************/

void *debug_malloc( size_t size, const char *file, int line, const char *func ) {
	void *p = malloc(size);		// allocate object with a normal call to malloc
	DBG_PRINT( "Allocated = %s, %i, %s, %p[%li]\n", file, line, func, p, size );
	return p;
}
