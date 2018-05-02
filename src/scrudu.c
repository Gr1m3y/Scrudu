// scrudu.c
// Based on MinUnit
// http://www.jera.com/techinfo/jtns/jtn002.html
//
// @author Angus Hilts
//
// Simple unit test framework for C

#include <stdio.h>
#include <string.h>
#include "scrudu.h"

// Unit Testing summary data [DO NOT CHANGE]
int tests_run = 0;
int tests_passed = 0;
int tests_failed = 0;
int asserts_passed = 0;
int asserts_failed = 0;

// Sample function [this can be removed]
int square(int x) {
	return x*x;
}

/***********************************************************************
 * WRITE TESTS HERE [MODIFY THIS SECTIONS]
 ***********************************************************************/

// Example
int square_test() {
	ut_assert( square(3) == 9 );
	return 0;
}

/*******************************************************************/

int main(int argc, char **argv) {

	printf("Starting test driver...\n\n");

	/**********************************************************************
	 * RUN TESTS HERE [MODIFY THIS SECTION]
	 **********************************************************************/

	// Unit test example
	ut_run( square_test );
	// Examples of memcheck
	// Note that if MEMCHECK is defined, allocations and frees will be reported.
	void *int_1 = malloc(sizeof(int));
	int *int_2 = malloc(sizeof(uint64_t));
	int *int_3 = malloc(sizeof(char));
	free(int_1);
	free(int_3);
	free(int_2);
	free(NULL);

	/**********************************************************************
	* Print out a summary of the results [DO NOT MODIFY BELOW HERE]
	***********************************************************************/
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
