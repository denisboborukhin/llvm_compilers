; ModuleID = 'top'
source_filename = "top"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@regFile = external global [16 x i32]

define void @main() {
  store i32 0, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 0), align 4
  store i32 1, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 1), align 4
  br label %app

app:                                              ; preds = %.flush, %0
  %1 = call i32 @simRand()
  store i32 %1, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 2), align 4
  %2 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 2), align 4
  %3 = srem i32 %2, 400
  store i32 %3, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 2), align 4
  store i32 50, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 11), align 4
  %4 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 2), align 4
  %5 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 11), align 4
  %6 = add nsw i32 %4, %5
  store i32 %6, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 2), align 4
  %7 = call i32 @simRand()
  store i32 %7, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 3), align 4
  %8 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 3), align 4
  %9 = srem i32 %8, 150
  store i32 %9, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 3), align 4
  %10 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 3), align 4
  %11 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 11), align 4
  %12 = add nsw i32 %10, %11
  store i32 %12, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 3), align 4
  %13 = call i32 @simRand()
  store i32 %13, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 4), align 4
  %14 = call i32 @simRand()
  store i32 %14, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 5), align 4
  %15 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 5), align 4
  %16 = srem i32 %15, 45
  store i32 %16, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 5), align 4
  %17 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 5), align 4
  %18 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 1), align 4
  %19 = add nsw i32 %17, %18
  store i32 %19, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 5), align 4
  %20 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 0), align 4
  %21 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 5), align 4
  %22 = sub nsw i32 %20, %21
  store i32 %22, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 6), align 4
  br label %.loop_w

.loop_w:                                          ; preds = %.jp_loop_w, %app
  %23 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 0), align 4
  %24 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 5), align 4
  %25 = sub nsw i32 %23, %24
  store i32 %25, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 7), align 4
  br label %.loop_h

.loop_h:                                          ; preds = %.jp_loop_h, %.loop_w
  %26 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 6), align 4
  %27 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 6), align 4
  %28 = mul nsw i32 %26, %27
  store i32 %28, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 8), align 4
  %29 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 7), align 4
  %30 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 7), align 4
  %31 = mul nsw i32 %29, %30
  store i32 %31, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 9), align 4
  %32 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 8), align 4
  %33 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 9), align 4
  %34 = add nsw i32 %32, %33
  store i32 %34, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 8), align 4
  %35 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 5), align 4
  %36 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 5), align 4
  %37 = mul nsw i32 %35, %36
  store i32 %37, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 9), align 4
  %38 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 8), align 4
  %39 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 9), align 4
  %40 = icmp slt i32 %38, %39
  %41 = zext i1 %40 to i32
  store i32 %41, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 15), align 4
  %42 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 15), align 4
  %43 = trunc i32 %42 to i1
  br i1 %43, label %.draw_pixel, label %.jp_next_h

.jp_next_h:                                       ; preds = %.loop_h
  br label %.next_h

.draw_pixel:                                      ; preds = %.loop_h
  %44 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 2), align 4
  %45 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 6), align 4
  %46 = add nsw i32 %44, %45
  store i32 %46, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 10), align 4
  %47 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 3), align 4
  %48 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 7), align 4
  %49 = add nsw i32 %47, %48
  store i32 %49, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 11), align 4
  %50 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 10), align 4
  %51 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 11), align 4
  %52 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 4), align 4
  call void @simPutPixel(i32 %50, i32 %51, i32 %52)
  br label %.next_h

.next_h:                                          ; preds = %.draw_pixel, %.jp_next_h
  %53 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 7), align 4
  %54 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 1), align 4
  %55 = add nsw i32 %53, %54
  store i32 %55, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 7), align 4
  %56 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 7), align 4
  %57 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 5), align 4
  %58 = icmp eq i32 %56, %57
  %59 = zext i1 %58 to i32
  store i32 %59, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 15), align 4
  %60 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 15), align 4
  %61 = trunc i32 %60 to i1
  br i1 %61, label %.next_w, label %.jp_loop_h

.jp_loop_h:                                       ; preds = %.next_h
  br label %.loop_h

.next_w:                                          ; preds = %.next_h
  %62 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 6), align 4
  %63 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 1), align 4
  %64 = add nsw i32 %62, %63
  store i32 %64, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 6), align 4
  %65 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 6), align 4
  %66 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 5), align 4
  %67 = icmp eq i32 %65, %66
  %68 = zext i1 %67 to i32
  store i32 %68, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 15), align 4
  %69 = load i32, i32* getelementptr inbounds ([16 x i32], [16 x i32]* @regFile, i32 0, i32 15), align 4
  %70 = trunc i32 %69 to i1
  br i1 %70, label %.flush, label %.jp_loop_w

.jp_loop_w:                                       ; preds = %.next_w
  br label %.loop_w

.flush:                                           ; preds = %.next_w
  call void @simFlush()
  br label %app
}

declare void @simPutPixel(i32, i32, i32)

declare void @simFlush()

declare i32 @simRand()
