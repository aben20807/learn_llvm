# llvm-pass-pgo

PGO flow to get counter during first run

## Build

```bash
$ cd llvm-pass-pgo
$ mkdir build && cd build
$ cmake -G Ninja ..
$ ninja
```

## Run

+ 1st compilation

```bash
$ clang -flegacy-pass-manager -Xclang -load -Xclang pgo/libPGOPass.so -fprofile-instr-generate ../../something.c
```

```{out.res}
I saw a function called 'foo', arg_size: 0
I saw a block called 
Freq: 1
Freq (profile): None

I saw a function called 'bar', arg_size: 2
I saw a block called 
Freq: 1
Freq (profile): None

I saw a block called 
Freq: 0
Freq (profile): None

I saw a block called 
Freq: 0
Freq (profile): None

I saw a block called 
Freq: 1
Freq (profile): None

I saw a function called 'baz', arg_size: 1
I saw a block called 
Freq: 1
Freq (profile): None

I saw a function called 'main', arg_size: 2
I saw a block called 
Freq: 1
Freq (profile): None

I saw a block called 
Freq: 32
Freq (profile): None

I saw a block called 
Freq: 31
Freq (profile): None

I saw a block called 
Freq: 31
Freq (profile): None

I saw a block called 
Freq: 1
Freq (profile): None
```

+ 1st runtime

```bash
./a.out
```

```{out2.res}
foo
foo
foo
foo
foo
foo
foo
foo
foo
foo
foo
foo
10
3.140000
3
```

+ 2nd compilation

```bash
$ llvm-profdata merge -o default.profdata default.profraw
$ clang -flegacy-pass-manager -Xclang -load -Xclang pgo/libPGOPass.so -fprofile-instr-use=default.profdata ../../something.c
```

```{out3.res}
I saw a function called 'foo', arg_size: 0
ProfileCount: 12
I saw a block called 
Freq: 1
Freq (profile): 12

I saw a function called 'bar', arg_size: 2
ProfileCount: 1
I saw a block called 
Freq: 1
Freq (profile): 1

I saw a block called 
Freq: 0
Freq (profile): 0

I saw a block called 
Freq: 0
Freq (profile): 1

I saw a block called 
Freq: 1
Freq (profile): 1

I saw a function called 'baz', arg_size: 1
ProfileCount: 1
I saw a block called 
Freq: 1
Freq (profile): 1

I saw a function called 'main', arg_size: 2
ProfileCount: 1
I saw a block called 
Freq: 1
Freq (profile): 1

I saw a block called 
Freq: 6
Freq (profile): 6

I saw a block called 
Freq: 5
Freq (profile): 5

I saw a block called 
Freq: 5
Freq (profile): 5

I saw a block called 
Freq: 1
Freq (profile): 1

```
