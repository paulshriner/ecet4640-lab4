

# CuTest

CuTest is a lightweight C unit testing framework. It allows us to create simple unit tests for our modules, enabling Test-Driven-Development (TDD). This speeds up program iteration and validates accurate performance.

[link to CuTest repo](https://cutest.sourceforge.net/)

There are three compilation pipelines. The production pipelines compiles the code in `src` to .o files, then links them. The test file compiles all files in `src` *except* `main.c`, and also compiles all the files in `tests` and links them. This allows the `test` executable to use the modules defined in `src`. The client and server compilations exclude `/src/server/main.c` and `/src/client/main.c`, respectively.

# Notes on configuring for VS Code on windows

1. Run WSL (Windows Server Linux)
2. Run `echo | gcc -xc -E -v -` to see where your include directoreis are.
3. It will probably be `/usr/include`. Run `cp -r /usr/include linclude/` to add them to this folder, to stop the include errors VSCode gives. 
4. The file `.vscode/c_cpp_properties.json` should already be configured to look for `/linclude` as an include path. If not, add `${workspaceFolder/linclude/**}` and `${workspaceFolder/linclude/**/*}` as values to the includePath array.

# Checking shared memory

ipcs -m 

# Check if process running

ps -e | grep "server"

