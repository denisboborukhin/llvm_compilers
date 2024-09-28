; ModuleID = 'app.c'
source_filename = "app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@MARGIN = dso_local local_unnamed_addr constant i32 10, align 4

; Function Attrs: nounwind uwtable
define dso_local void @drawCircle(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) local_unnamed_addr #0 {
  %5 = sub i32 0, %2
  %6 = icmp slt i32 %2, 0
  br i1 %6, label %13, label %7

7:                                                ; preds = %4
  %8 = mul nsw i32 %2, %2
  br label %9

9:                                                ; preds = %14, %7
  %10 = phi i32 [ %5, %7 ], [ %15, %14 ]
  %11 = mul nsw i32 %10, %10
  %12 = add nsw i32 %10, %0
  br label %17

13:                                               ; preds = %14, %4
  ret void

14:                                               ; preds = %24
  %15 = add i32 %10, 1
  %16 = icmp eq i32 %10, %2
  br i1 %16, label %13, label %9, !llvm.loop !5

17:                                               ; preds = %9, %24
  %18 = phi i32 [ %5, %9 ], [ %25, %24 ]
  %19 = mul nsw i32 %18, %18
  %20 = add nuw nsw i32 %19, %11
  %21 = icmp ugt i32 %20, %8
  br i1 %21, label %24, label %22

22:                                               ; preds = %17
  %23 = add nsw i32 %18, %1
  tail call void @simPutPixel(i32 noundef %12, i32 noundef %23, i32 noundef %3) #3
  br label %24

24:                                               ; preds = %17, %22
  %25 = add i32 %18, 1
  %26 = icmp eq i32 %18, %2
  br i1 %26, label %14, label %17, !llvm.loop !7
}

declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #1

; Function Attrs: nounwind uwtable
define dso_local i32 @getRadius(i32 noundef %0, i32 noundef %1) local_unnamed_addr #0 {
  %3 = sub nsw i32 512, %0
  %4 = icmp slt i32 %3, %0
  %5 = select i1 %4, i32 %3, i32 %0
  %6 = icmp sgt i32 %5, %1
  %7 = select i1 %6, i32 %1, i32 %5
  %8 = sub nsw i32 256, %1
  %9 = icmp slt i32 %8, %7
  %10 = select i1 %9, i32 %8, i32 %7
  %11 = tail call i32 (...) @simRand() #3
  %12 = add nsw i32 %10, -9
  %13 = srem i32 %11, %12
  %14 = add nsw i32 %13, 2
  ret i32 %14
}

declare i32 @simRand(...) local_unnamed_addr #1

; Function Attrs: noreturn nounwind uwtable
define dso_local void @app() local_unnamed_addr #2 {
  br label %1

1:                                                ; preds = %0, %42
  %2 = tail call i32 (...) @simRand() #3
  %3 = srem i32 %2, 492
  %4 = add nsw i32 %3, 10
  %5 = tail call i32 (...) @simRand() #3
  %6 = srem i32 %5, 236
  %7 = add nsw i32 %6, 10
  %8 = tail call i32 (...) @simRand() #3
  %9 = sub nsw i32 502, %3
  %10 = icmp slt i32 %9, %4
  %11 = select i1 %10, i32 %9, i32 %4
  %12 = icmp sgt i32 %11, %7
  %13 = select i1 %12, i32 %7, i32 %11
  %14 = sub nsw i32 246, %6
  %15 = icmp slt i32 %14, %13
  %16 = select i1 %15, i32 %14, i32 %13
  %17 = tail call i32 (...) @simRand() #3
  %18 = add nsw i32 %16, -9
  %19 = srem i32 %17, %18
  %20 = add nsw i32 %19, 2
  %21 = sub nsw i32 -2, %19
  %22 = icmp slt i32 %19, -2
  br i1 %22, label %42, label %23

23:                                               ; preds = %1
  %24 = mul nuw nsw i32 %20, %20
  br label %25

25:                                               ; preds = %29, %23
  %26 = phi i32 [ %21, %23 ], [ %30, %29 ]
  %27 = mul nsw i32 %26, %26
  %28 = add nsw i32 %26, %4
  br label %32

29:                                               ; preds = %39
  %30 = add i32 %26, 1
  %31 = icmp eq i32 %26, %20
  br i1 %31, label %42, label %25, !llvm.loop !5

32:                                               ; preds = %39, %25
  %33 = phi i32 [ %21, %25 ], [ %40, %39 ]
  %34 = mul nsw i32 %33, %33
  %35 = add nuw nsw i32 %34, %27
  %36 = icmp ugt i32 %35, %24
  br i1 %36, label %39, label %37

37:                                               ; preds = %32
  %38 = add nsw i32 %33, %7
  tail call void @simPutPixel(i32 noundef %28, i32 noundef %38, i32 noundef %8) #3
  br label %39

39:                                               ; preds = %37, %32
  %40 = add i32 %33, 1
  %41 = icmp eq i32 %33, %20
  br i1 %41, label %29, label %32, !llvm.loop !7

42:                                               ; preds = %29, %1
  tail call void (...) @simFlush() #3
  br label %1
}

declare void @simFlush(...) local_unnamed_addr #1

attributes #0 = { nounwind uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { noreturn nounwind uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!5 = distinct !{!5, !6}
!6 = !{!"llvm.loop.mustprogress"}
!7 = distinct !{!7, !6}
