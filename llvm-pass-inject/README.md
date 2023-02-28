# llvm-pass-inject

Inject printf function to the call instrument

## Build

```bash
$ cd llvm-pass-inject
$ mkdir build && cd build
$ cmake -G Ninja ..
$ ninja
```

## Run

```bash
$ clang -flegacy-pass-manager -Xclang -load -Xclang inject/libInjectPass.so ../../something.c
```

## Output

```bash
$ ./a.out 
inject printf for call 'foo'
inject printf for call 'printf'
foo
inject printf for call 'foo'
inject printf for call 'printf'
foo
inject printf for call 'foo'
inject printf for call 'printf'
foo
inject printf for call 'foo'
inject printf for call 'printf'
foo
inject printf for call 'foo'
inject printf for call 'printf'
foo
inject printf for call 'foo'
inject printf for call 'printf'
foo
inject printf for call 'foo'
inject printf for call 'printf'
foo
inject printf for call 'foo'
inject printf for call 'printf'
foo
inject printf for call 'foo'
inject printf for call 'printf'
foo
inject printf for call 'foo'
inject printf for call 'printf'
foo
inject printf for call 'foo'
inject printf for call 'printf'
foo
inject printf for call 'foo'
inject printf for call 'printf'
foo
inject printf for call 'bar'
inject printf for call 'printf'
10
inject printf for call 'baz'
inject printf for call 'printf'
3
```

