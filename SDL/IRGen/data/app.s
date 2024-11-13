app:
    ; Generate random x
    SIM_RAND R2
    MOD R2, R2, 400
    MOV R11, 50
    ADD R2, R2, R11

    ; Generate random y
    SIM_RAND R3
    MOD R3, R3, 150
    ADD R3, R3, R11

    ; Generate random color
    SIM_RAND R4

    ; Calculate radius
    SIM_RAND R5
    
    MOD R5, R5, 45
    ADD R5, R5, R1

    ; Draw circle
    SUB R6, R0, R5
    JP .loop_w

.loop_w:
    SUB R7, R0, R5
    JP .loop_h

.loop_h:
    MUL R8, R6, R6
    MUL R9, R7, R7
    ADD R8, R8, R9
    MUL R9, R5, R5
    CMPL R8, R9
    JZ .draw_pixel, .jp_next_h

.jp_next_h:
    JP .next_h

.draw_pixel:
    ADD R10, R2, R6
    ADD R11, R3, R7
    SIM_PUT_PIXEL R10, R11, R4
    JP .next_h

.next_h:
    ADD R7, R7, R1
    CMP R7, R5
    JZ .next_w, .jp_loop_h

.jp_loop_h:
    JP .loop_h

.next_w:
    ADD R6, R6, R1
    CMP R6, R5
    JZ .flush, .jp_loop_w

.jp_loop_w:
    JP .loop_w

.flush:
    SIM_FLUSH
    JP app