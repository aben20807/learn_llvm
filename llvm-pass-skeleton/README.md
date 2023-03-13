# llvm-pass-skeleton

A completely useless LLVM pass for the legacy pass manager.

+ reference: [sampsyo/llvm-pass-skeleton](https://github.com/sampsyo/llvm-pass-skeleton)

## build and run

```bash
$ cd llvm-pass-skeleton
$ mkdir build && cd build
$ cmake -G Ninja ..
$ ninja
```

## run

```bash
$ clang -flegacy-pass-manager -Xclang -load -Xclang skeleton/libSkeletonPass.so ../../something.c
```

## Output

```{out1.res}
I saw a function called 'foo', arg_size: 0
I saw a block called 
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i64 0, i64 0))
  ret void
I saw a function called 'bar', arg_size: 2
I saw a block called 
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i32 %0, i32* %4, align 4
  store i32 %1, i32* %5, align 4
  %6 = load i32, i32* %4, align 4
  %7 = load i32, i32* %5, align 4
  %8 = icmp sgt i32 %6, %7
  br i1 %8, label %9, label %15
I saw a block called 
  %10 = load i32, i32* %4, align 4
  %11 = load i32, i32* %5, align 4
  %12 = mul nsw i32 %10, %11
  %13 = load i32, i32* %5, align 4
  %14 = add nsw i32 %12, %13
  store i32 %14, i32* %3, align 4
  br label %21
I saw a block called 
  %16 = load i32, i32* %4, align 4
  %17 = load i32, i32* %5, align 4
  %18 = mul nsw i32 %16, %17
  %19 = load i32, i32* %5, align 4
  %20 = sub nsw i32 %18, %19
  store i32 %20, i32* %3, align 4
  br label %21
I saw a block called 
  %22 = load i32, i32* %3, align 4
  ret i32 %22
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
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca float, align 4
  %11 = alloca i32, align 4
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  store i8** %1, i8*** %5, align 8
  store i32 0, i32* %6, align 4
  br label %12
I saw a block called 
  %13 = load i32, i32* %6, align 4
  %14 = icmp slt i32 %13, 10
  br i1 %14, label %15, label %19
I saw a block called 
  call void @foo()
  br label %16
I saw a block called 
  %17 = load i32, i32* %6, align 4
  %18 = add nsw i32 %17, 1
  store i32 %18, i32* %6, align 4
  br label %12, !llvm.loop !2
I saw a block called 
  call void @foo()
  call void @foo()
  store i32 3, i32* %7, align 4
  store i32 5, i32* %8, align 4
  %20 = load i32, i32* %7, align 4
  %21 = load i32, i32* %8, align 4
  %22 = call i32 @bar(i32 %20, i32 %21)
  store i32 %22, i32* %9, align 4
  %23 = load i32, i32* %9, align 4
  %24 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i64 0, i64 0), i32 %23)
  store float 0x40091EB860000000, float* %10, align 4
  %25 = load float, float* %10, align 4
  %26 = call i32 @baz(float %25)
  store i32 %26, i32* %11, align 4
  %27 = load float, float* %10, align 4
  %28 = fpext float %27 to double
  %29 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i64 0, i64 0), double %28)
  %30 = load i32, i32* %11, align 4
  %31 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i64 0, i64 0), i32 %30)
  ret i32 0
```
