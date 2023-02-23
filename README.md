# Learn LLVM

## Legacy pass manager

```bash
$ cd llvm-pass-skeleton
$ mkdir build && cd build
$ cmake -G Ninja ..
$ ninja
$ cd ../..
$ clang -flegacy-pass-manager -Xclang -load -Xclang llvm-pass-skeleton/build/skeleton/libSkeletonPass.* something.c
```

<details>
<summary>Output</summary>

```
I saw a function called 'foo', arg_size: 0
I saw a block called 
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i64 0, i64 0))
  ret void
I saw a function called 'bar', arg_size: 2
I saw a block called 
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  %5 = load i32, i32* %3, align 4
  %6 = load i32, i32* %4, align 4
  %7 = mul nsw i32 %5, %6
  %8 = load i32, i32* %4, align 4
  %9 = add nsw i32 %7, %8
  ret i32 %9
I saw a function called 'baz', arg_size: 1
I saw a block called 
  %2 = alloca float, align 4
  store float %0, float* %2, align 4
  %3 = load float, float* %2, align 4
  %4 = fptosi float %3 to i32
  ret i32 %4
I saw a function called 'main', arg_size: 2
I saw a block called 
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  store i8** %1, i8*** %5, align 8
  call void @foo()
  %8 = call i32 @bar(i32 3, i32 5)
  store i32 %8, i32* %6, align 4
  %9 = load i32, i32* %6, align 4
  %10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i64 0, i64 0), i32 %9)
  %11 = call i32 @baz(float 0x40091EB860000000)
  store i32 %11, i32* %7, align 4
  %12 = load i32, i32* %7, align 4
  %13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i64 0, i64 0), i32 %12)
  ret i32 0
```

</details>
