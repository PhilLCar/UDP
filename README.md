# UPD utilities for C/C++ (CUT)
This repository contains a minimal implementation of a UDP server and client for C/C++.

# Usage
## C
To build the library run `make lib`. Then add:
```C
#include <udp.h>
```
to your project and compile using the flag `-ludp`. (Make sure `ld` can find `libudp.a`.)

For examples of how to use, or for testing/debugging run `make test`.

## C++
To build the library run `make lib LANG=C++`. Then add:
```C++
#include <udp.hpp>
```
to your project and compile using the flag `-ludp++`. (Make sure `ld` can find `libudp++.a`.)

For examples of how to use, or for testing/debugging run `make test LANG=C++`.