# llvm-pass-skeleton

A completely useless LLVM pass.

Build:

    $ cd llvm-pass-inject
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ cd ..

Run:

    $ clang -Xclang -load -Xclang build/inject/libInjectPass.so something.c
