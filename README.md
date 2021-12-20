# pincushion

A repository of small [spikes](https://en.wikipedia.org/wiki/Spike_(software_development)) with general applicability.

## Utilities and libraries

csv2json:
    - Read in CSV and emit JSON
    - Create utilities and types to read in CSVs
    - Emit JSON using headers
    - Handle command line options

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

There's no easy way to make test execution dependento on building test
harnesses:

<https://stackoverflow.com/questions/733475/cmake-ctest-make-test-doesnt-build-tests>

And then there's the whole problem of where to even run CMake to build:

<https://stackoverflow.com/questions/9680420/looking-for-a-cmake-clean-command-to-clear-up-cmake-output>

But in the end, the tests do run.
