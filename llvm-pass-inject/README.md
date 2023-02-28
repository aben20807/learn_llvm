# llvm-pass-inject

Inject printf function to the call instrument

## Build

```bash
$ cd llvm-pass-inject
$ mkdir build && cd build
$ cmake -G Ninja ..
$ ninja
$ cd ../..
```

## Run

```bash
$ clang -flegacy-pass-manager -Xclang -load -Xclang llvm-pass-inject/build/inject/libInjectPass.so something.c
```

## Output

```bash
$ ./a.out 
call foo
call printf
foo
call bar
call printf
20
call baz
call printf
3
```

