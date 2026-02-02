# VIRTEL

I've read ["Crafting Interpreters"]("https://craftinginterpreters.com/") book by Bob Nystrom and rewrite the Lox interpreter in C++.

## Build

>NOTE: I've used Lua for scripting, so you need the Lua interpreter or you can use cmake directly.

```sh
# build the binary
lua scripts/build.lua configure
lua scripts/build.lua build 
```

```sh
# run virtel interpreter (repl)
lua scripts/build.lua run
```

```sh
# remove build dir, (clean)
lua scripts/build.lua clean
```
