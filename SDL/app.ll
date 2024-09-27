; ModuleID = 'app.c'
source_filename = "app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

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

; Function Attrs: noreturn nounwind uwtable
define dso_local void @app() local_unnamed_addr #2 {
  br label %1

1:                                                ; preds = %24, %0
  br label %2

2:                                                ; preds = %1, %24
  %3 = phi i32 [ 102, %1 ], [ %25, %24 ]
  %4 = tail call i32 (...) @simRand() #3
  %5 = sub nsw i32 0, %3
  %6 = mul nsw i32 %3, %3
  br label %7

7:                                                ; preds = %11, %2
  %8 = phi i32 [ %5, %2 ], [ %12, %11 ]
  %9 = mul nsw i32 %8, %8
  %10 = add nsw i32 %8, 256
  br label %14

11:                                               ; preds = %21
  %12 = add nsw i32 %8, 1
  %13 = icmp eq i32 %8, %3
  br i1 %13, label %24, label %7, !llvm.loop !5

14:                                               ; preds = %21, %7
  %15 = phi i32 [ %5, %7 ], [ %22, %21 ]
  %16 = mul nsw i32 %15, %15
  %17 = add nuw nsw i32 %16, %9
  %18 = icmp ugt i32 %17, %6
  br i1 %18, label %21, label %19

19:                                               ; preds = %14
  %20 = add nsw i32 %15, 128
  tail call void @simPutPixel(i32 noundef %10, i32 noundef %20, i32 noundef %4) #3
  br label %21

21:                                               ; preds = %19, %14
  %22 = add nsw i32 %15, 1
  %23 = icmp eq i32 %15, %3
  br i1 %23, label %11, label %14, !llvm.loop !7

24:                                               ; preds = %11
  tail call void (...) @simFlush() #3
  %25 = add nsw i32 %3, -5
  %26 = icmp ugt i32 %3, 5
  br i1 %26, label %2, label %1, !llvm.loop !8
}

declare i32 @simRand(...) local_unnamed_addr #1

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
!8 = distinct !{!8, !6}
