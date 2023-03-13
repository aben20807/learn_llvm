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
v1:
<addr> = distinct !DISubprogram(name: "foo", scope: <addr>, file: <addr>, line: 3, type: <addr>, scopeLine: 3, spFlags: DISPFlagDefinition, unit: <addr>, retainedNodes: <addr>)
func name: foo
src line:  3
src file:  ../../something.c
v1:
<addr> = distinct !DISubprogram(name: "foo", scope: <addr>, file: <addr>, line: 3, type: <addr>, scopeLine: 3, spFlags: DISPFlagDefinition, unit: <addr>, retainedNodes: <addr>)
v2:
<addr> = distinct !DISubprogram(name: "foo", scope: <addr>, file: <addr>, line: 3, type: <addr>, scopeLine: 3, spFlags: DISPFlagDefinition, unit: <addr>, retainedNodes: <addr>)
func name: foo
src line:  3
src file:  ../../something.c

I saw a function called 'bar', arg_size: 2
v1:
<addr> = distinct !DISubprogram(name: "bar", scope: <addr>, file: <addr>, line: 7, type: <addr>, scopeLine: 7, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: <addr>, retainedNodes: <addr>)
func name: bar
src line:  7
src file:  ../../something.c
v1:
<addr> = distinct !DISubprogram(name: "bar", scope: <addr>, file: <addr>, line: 7, type: <addr>, scopeLine: 7, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: <addr>, retainedNodes: <addr>)
v2:
<addr> = distinct !DISubprogram(name: "bar", scope: <addr>, file: <addr>, line: 7, type: <addr>, scopeLine: 7, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: <addr>, retainedNodes: <addr>)
func name: bar
src line:  7
src file:  ../../something.c

I saw a function called 'baz', arg_size: 1
v1:
<addr> = distinct !DISubprogram(name: "baz", scope: <addr>, file: <addr>, line: 14, type: <addr>, scopeLine: 14, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: <addr>, retainedNodes: <addr>)
func name: baz
src line:  14
src file:  ../../something.c
v1:
<addr> = distinct !DISubprogram(name: "baz", scope: <addr>, file: <addr>, line: 14, type: <addr>, scopeLine: 14, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: <addr>, retainedNodes: <addr>)
v2:
<addr> = distinct !DISubprogram(name: "baz", scope: <addr>, file: <addr>, line: 14, type: <addr>, scopeLine: 14, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: <addr>, retainedNodes: <addr>)
func name: baz
src line:  14
src file:  ../../something.c

I saw a function called 'main', arg_size: 2
v1:
<addr> = distinct !DISubprogram(name: "main", scope: <addr>, file: <addr>, line: 18, type: <addr>, scopeLine: 18, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: <addr>, retainedNodes: <addr>)
func name: main
src line:  18
src file:  ../../something.c
v1:
<addr> = distinct !DISubprogram(name: "main", scope: <addr>, file: <addr>, line: 18, type: <addr>, scopeLine: 18, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: <addr>, retainedNodes: <addr>)
v2:
<addr> = distinct !DISubprogram(name: "main", scope: <addr>, file: <addr>, line: 18, type: <addr>, scopeLine: 18, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: <addr>, retainedNodes: <addr>)
func name: main
src line:  18
src file:  ../../something.c

```
