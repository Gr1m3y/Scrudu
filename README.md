# Scrudu
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
-MEMCHECK - Enables malloc and free wrappers for memory analysis.
-LOG      - Enables log printing (least information)
-DEBUG    - Enables debug printing (some information)
-ERR      - Enables error printing (all information)
-VERBOSE  - Prints more detailed unit test summaries (i.e. all asserts)
