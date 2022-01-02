# pincushion

A repository of small [spikes](https://en.wikipedia.org/wiki/Spike_(software_development)) with general applicability.

## Utilities and libraries

### csv2json

    - Read in CSV and emit JSON
    - Create utilities and types to read in CSVs
    - Emit JSON using headers
    - Handle command line options

### pincushion CSV library

Uses a simple finite state machine to parse CSV in accordance with
[RFC 4180](https://datatracker.ietf.org/doc/html/rfc4180). Note that CSV only
escapes quotes with double quotes.

## How to Build

Run CMake from build directory:

`cd build && cmake .. && make && make test`

## Build infrastructure:

- [CMake](https://cmake.org)
- [Catch2](https://github.com/catchorg/Catch2)

### CMake lab notes

In theory this should be simpler and more repeatable than writing makefiles or
something platform-specific like `automake`. In practice it's not so simple --
part of this is the fractured nature of cross-platform C\+\+, but the rest is
CMake seeming to be a solution in search of a problem.

This is why cross platform languages closely tied to build system or runtime
have been making inroads.

Some caveats:

There's no easy way to make test execution dependent on building test
harnesses:

<https://stackoverflow.com/questions/733475/cmake-ctest-make-test-doesnt-build-tests>

And then there's the whole problem of where to even run CMake to build:

<https://stackoverflow.com/questions/9680420/looking-for-a-cmake-clean-command-to-clear-up-cmake-output>

But in the end, the tests do run.

Able to successfully run tests. Note that VSCode extension will run make, and
then will run tests. Works well.

## CMake project organization

Referred to Boost's program_options library for example of standards:
<https://github.com/boostorg/program_options/blob/develop/CMakeLists.txt>
