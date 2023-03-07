# llvm-pass-debug

Get debug info

## build and run

```bash
$ cd llvm-pass-debug
$ mkdir build && cd build
$ cmake -G Ninja ..
$ ninja
```

## run

```bash
$ clang -flegacy-pass-manager -Xclang -load -Xclang debug/libDebugPass.so -g ../../something.c
```

```{out1.res}
I saw a function called 'foo', arg_size: 0
<0x56366d242e30> = distinct !DISubprogram(name: "foo", scope: <0x56366d1b8ba0>, file: <0x56366d1b8ba0>, line: 3, type: <0x56366d190b40>, scopeLine: 3, spFlags: DISPFlagDefinition, unit: <0x56366d1ba0b8>, retainedNodes: <0x56366d268ea0>)
func name: foo
src line:  3
src file:  ../../something.c
I saw a function called 'bar', arg_size: 2
<0x56366d26e8d0> = distinct !DISubprogram(name: "bar", scope: <0x56366d1b8ba0>, file: <0x56366d1b8ba0>, line: 7, type: <0x56366d1939e0>, scopeLine: 7, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: <0x56366d1ba0b8>, retainedNodes: <0x56366d268ea0>)
func name: bar
src line:  7
src file:  ../../something.c
I saw a function called 'baz', arg_size: 1
<0x56366d26ff00> = distinct !DISubprogram(name: "baz", scope: <0x56366d1b8ba0>, file: <0x56366d1b8ba0>, line: 14, type: <0x56366d26fe80>, scopeLine: 14, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: <0x56366d1ba0b8>, retainedNodes: <0x56366d268ea0>)
func name: baz
src line:  14
src file:  ../../something.c
I saw a function called 'main', arg_size: 2
<0x56366d26ff80> = distinct !DISubprogram(name: "main", scope: <0x56366d1b8ba0>, file: <0x56366d1b8ba0>, line: 18, type: <0x56366d273860>, scopeLine: 18, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: <0x56366d1ba0b8>, retainedNodes: <0x56366d268ea0>)
func name: main
src line:  18
src file:  ../../something.c
```
