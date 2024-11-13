; ModuleID = 'app.c'
source_filename = "app.c"

declare void @simPutPixel(i32, i32, i32)

declare void @simFlush()

declare i32 @simRand()

define i32 @app() {
  br label %1

1:                                                ; preds = %42, %0
  %2 = call i32 @simRand()
  %3 = srem i32 %2, 492
  %4 = add nsw i32 %3, 10
  %5 = call i32 @simRand()
  %6 = srem i32 %5, 236
  %7 = add nsw i32 %6, 10
  %8 = call i32 @simRand()
  %9 = sub nsw i32 502, %3
  %10 = icmp slt i32 %9, %4
  %11 = select i1 %10, i32 %9, i32 %4
  %12 = icmp sgt i32 %11, %7
  %13 = select i1 %12, i32 %7, i32 %11
  %14 = sub nsw i32 246, %6
  %15 = icmp slt i32 %14, %13
  %16 = select i1 %15, i32 %14, i32 %13
  %17 = call i32 @simRand()
  %18 = add nsw i32 %16, -9
  %19 = srem i32 %17, %18
  %20 = add nsw i32 %19, 2
  %21 = sub nsw i32 -2, %19
  %22 = icmp slt i32 %19, -2
  br i1 %22, label %42, label %23

23:                                               ; preds = %1
  %24 = mul nsw i32 %20, %20
  br label %25

25:                                               ; preds = %29, %23
  %26 = phi i32 [ %21, %23 ], [ %30, %29 ]
  %27 = mul nsw i32 %26, %26
  %28 = add nsw i32 %26, %4
  br label %32

29:                                               ; preds = %39
  %30 = add i32 %26, 1
  %31 = icmp eq i32 %26, %20
  br i1 %31, label %42, label %25

32:                                               ; preds = %39, %25
  %33 = phi i32 [ %21, %25 ], [ %40, %39 ]
  %34 = mul nsw i32 %33, %33
  %35 = add nsw i32 %34, %27
  %36 = icmp ugt i32 %35, %24
  br i1 %36, label %39, label %37

37:                                               ; preds = %32
  %38 = add nsw i32 %33, %7
  call void @simPutPixel(i32 %28, i32 %38, i32 %8)
  br label %39

39:                                               ; preds = %37, %32
  %40 = add i32 %33, 1
  %41 = icmp eq i32 %33, %20
  br i1 %41, label %29, label %32

42:                                               ; preds = %29, %1
  call void @simFlush()
  br label %1
}
