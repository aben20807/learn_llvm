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

```{out1.res}
I saw a function called 'foo', arg_size: 0
I saw a CallInst called 'printf' (skip)
I saw a function called 'bar', arg_size: 2
I saw a function called 'baz', arg_size: 1
I saw a function called 'main', arg_size: 2
I saw a CallInst called 'foo', Num of arguments: 0, format specifier of printf: "\n"
I saw a CallInst called 'foo', Num of arguments: 0, format specifier of printf: "\n"
I saw a CallInst called 'foo', Num of arguments: 0, format specifier of printf: "\n"
I saw a CallInst called 'bar', Num of arguments: 2, format specifier of printf: "; args: %d, %d\n"
I saw a CallInst called 'printf' (skip)
I saw a CallInst called 'baz', Num of arguments: 1, format specifier of printf: "; args: %f\n"
Add fpext for printing float vaule
I saw a CallInst called 'printf' (skip)
I saw a CallInst called 'printf' (skip)
```

## Output

```bash
$ ./a.out 
```

+ stdout:

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

+ stderr:

```{out3.res}
inject fprintf for call 'foo'
inject fprintf for call 'foo'
inject fprintf for call 'foo'
inject fprintf for call 'foo'
inject fprintf for call 'foo'
inject fprintf for call 'foo'
inject fprintf for call 'foo'
inject fprintf for call 'foo'
inject fprintf for call 'foo'
inject fprintf for call 'foo'
inject fprintf for call 'foo'
inject fprintf for call 'foo'
inject fprintf for call 'bar'; args: 3, 5
inject fprintf for call 'baz'; args: 3.140000
```
