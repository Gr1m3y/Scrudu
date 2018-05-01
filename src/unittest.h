// unittest.h
// Based on MinUnit
// http://www.jera.com/techinfo/jtns/jtn002.html
//
// @author Angus Hilts
//
// Simple unit test framework for C

#include <stdlib.h>
#include "debug.h"

#ifndef unittest_h
#define unitttest_h

// Colours
#define RED "\x1B[31m"		// Red
#define GRN "\x1B[32m"		// Green
#define RST "\x1B[0m"		// Reset colours

/************************************************************************
 * Unit Testing Framework
 ************************************************************************/

// Success message
#define SUCCESS() do { printf("[ " GRN "OK" RST " ]\n"); \
	tests_passed++; } while (0)
// Fail message
#define FAIL() do { printf("[" RED "FAIL" RST "]\n"); \
	tests_failed++; } while (0)

// This version of the code will only present the overall result of
// each test (i.e. the test function will pass only if every call to
// ut_assert succeeded).
#ifndef VERBOSE		// Only presents information for each test
// assert function for test
#define assert_SUCCESS() do { \
	asserts_passed++; } while(0)
#define assert_FAIL() do {	\
	asserts_failed++; } while(0)

#define ut_assert(test) do {\
	if (!(test)) { assert_FAIL() ; } 						\
	else { assert_SUCCESS() ; } } while (0)

#define ut_run(test) do { printf( "%-30s",#test "..." );	\
	int current = asserts_failed;					\
	test(); tests_run++;							\
	if( asserts_failed-current ) { FAIL(); }		\
	else { SUCCESS(); } } while(0)


#else	/* verbose */

// This version of the code will present the result of every call to
// ut_assert, as well as the overall result of each test.
#define assert_SUCCESS() do { printf("[ " GRN "OK" RST " ]\n"); \
	asserts_passed++; } while(0)
#define assert_FAIL() do { printf("[" RED "FAIL" RST "]\n"); 	\
	asserts_failed++; } while(0)


#define ut_assert(test) do { printf("\tLine: %-15d", __LINE__); 	\
	if (!(test)) { assert_FAIL() ; } 						\
	else { assert_SUCCESS() ; } } while (0)

#define ut_run(test) do { printf( #test "...\n" );	\
	int current = asserts_failed;					\
	test(); tests_run++;							\
	printf("%-35s", "Result:");						\
	if( asserts_failed-current ) { FAIL(); }		\
	else { SUCCESS(); } } while(0)

#endif /* verbose */

// Summary data
extern int tests_run;
extern int tests_passed;
extern int tests_failed;
extern int asserts_failed;
extern int asserts_passed;

#endif /* unittest_h */
