# Scrúdú
A testing framework for C development.

## Introduction
This is a framework with different macros that can be used for testing and building
C projects. This includes a simple unit testing framework (unittest.h) and a memory
management testing framework (memcheck.h). To use the different frameworks, simply
include Scrudu.h in any file you wish to test, then define the appropriate flags,
either in your source code (less good way) or in our compiler command (better way).

## Unittest.h
Used for unit testing code snippets. To use this module, either include the header
in your main code file and define appropriate variables (harder way), or use the
provided unittest.c file and define your tests where noted. Be sure that your
compiler points to this file for the entry point for your test binaries!

## Memcheck.h
This framework includes macros that override the default malloc and free functions.
The provided functions will keep track of any allocations and store them in a table.
This table can then be printed to view any allocations that were not subsequently
freed.

## Flags
The interface uses several flags that must be defined for certain functionality
to work. These are listed below.
* MEMCHECK - Enables malloc and free wrappers for memory analysis.
* LOG      - Enables log printing (least information)
* DEBUG    - Enables debug printing (some information)
* ERR      - Enables error printing (all information)
* VERBOSE  - Prints more detailed unit test summaries (i.e. all asserts)

## Example of Usage
Unit testing is relatively simple here. Simply add the code to your project,
then use the scrudu.c file to write tests. There are two macros defined in
unittest.h that should be used: `ut_assert` and `ut_run`. The first macro works
like a normal assert and compares two values. For example, consider the function
give below:
```C
int square(int x) {
  return x*x;
}
```
To test this, write a test function which makes the necessary asserts, as shown
below:
```C
int test_square() {
  ut_assert( square(3) == 9 );  // this test should pass
  ut_assert( square(4) == 2 );  // this assert should fail
  return 0;
}
```
Finally, call the function with ut_run. This should be called in `main`, located
in scrudu.c.
```C
int main() {
  ut_run( test_square );    // fails if any asserts within the function fail
  return 0;
}
```

## The Road Ahead

I have many plans for this suite, and in all likelihood will add them as they
become relevant, especially over the course of my current projects. I would like
to implement wrappers for some of the other methods of allocating memory
(realloc, etc.) This is the big change that will likely happen in the near
future. Other changes I will add to this part of the readme as I think of them,
or as they become something that I need. In addition to this, I would like to,
for the sake of being in good habit, update the documentation on usage to be
thorough and approachable, especially for people who do not have much of a
background with computer science or programming. This will include in-line
documentation, as well as this readme, and a log file.

I hope that anyone who uses this finds it helpful, and hopefully it can teach
something as well!
