# VIRTEL

I've read [Crafting Interpreters]("https://craftinginterpreters.com/") book by Bob Nystrom and rewrite the Lox interpreter in C++.

## Build & Run

### Prerequisites
- CMake >= 3.16
- GCC or Clang
- Lua (for build scripts) (optional, since you can run raw cmake)

#### ***Using Lua scripts***

>NOTE: To see all available scripts, run the following command: `lua scripts/build.lua`.

#### Build
```sh
lua scripts/build.lua rebuild # to configure and build the project 
```

#### Run
```sh
lua scripts/build.lua run
```

#### Clean
```sh
lua scripts/build.lua clean
```

#### Test
```sh
lua scripts/build.lua test
```

***Raw CMake***

#### Build
```sh
cmake -S . -B build # to configure
cmake --build build # to build the project
```

#### Run
```sh
./build/src/virtel
```

#### Clean
```sh
rm -rf build # from the root directory
```

#### Test
```sh
ctest --output-on-failure --test-dir build
```
