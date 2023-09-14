

# CuTest

CuTest is a lightweight C unit testing framework. It allows us to create simple unit tests for our modules, enabling Test-Driven-Development (TDD). This speeds up program iteration and validates accurate performance.

[link to CuTest repo](https://cutest.sourceforge.net/)

There are two compilation pipelines. The production pipelines compiles the code in `src` to .o files, then links them. The test file compiles all files in `src` *except* `main.c`, and also compiles all the files in `tests` and links them. This allows the `test` executable to use the modules defined in `src`.

cp -r /usr/include/x86_64-linux-gnu/ linclude

cp -r /usr/include/ linclude/