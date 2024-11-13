app:                                    # @app
        push    rbp
        push    r15
        push    r14
        push    r13
        push    r12
        push    rbx
        sub     rsp, 40
        jmp     .LBB0_1
.LBB0_8:                                #   in Loop: Header=BB0_1 Depth=1
        call    simFlush@PLT
.LBB0_1:                                # =>This Loop Header: Depth=1
        call    simRand@PLT
        cdqe
        imul    rcx, rax, 558694933
        mov     rdx, rcx
        shr     rdx, 63
        sar     rcx, 38
        add     ecx, edx
        imul    ecx, ecx, 492
        mov     edx, eax
        sub     edx, ecx
        mov     ebp, 502
        sub     ebp, edx
        neg     ecx
        lea     r14d, [rax + rcx + 10]
        call    simRand@PLT
        cdqe
        imul    rcx, rax, 582368447
        mov     rdx, rcx
        shr     rdx, 63
        sar     rcx, 37
        add     ecx, edx
        imul    ecx, ecx, 236
        mov     r15d, eax
        sub     r15d, ecx
        neg     ecx
        lea     ebx, [rax + rcx + 10]
        call    simRand@PLT
        mov     dword ptr [rsp + 20], eax       # 4-byte Spill
        cmp     ebp, r14d
        mov     qword ptr [rsp + 24], r14       # 8-byte Spill
        cmovge  ebp, r14d
        cmp     ebp, ebx
        cmovg   ebp, ebx
        mov     ebx, 246
        mov     r14d, r15d
        sub     ebx, r15d
        cmp     ebx, ebp
        cmovge  ebx, ebp
        call    simRand@PLT
        add     ebx, -9
        cdq
        idiv    ebx
        mov     eax, edx
        sub     eax, -2
        jl      .LBB0_8
        lea     r15d, [rdx + 2]
        neg     eax
        mov     dword ptr [rsp + 8], r15d       # 4-byte Spill
        imul    r15d, r15d
        lea     ecx, [rdx + rdx + 5]
        mov     dword ptr [rsp + 4], ecx        # 4-byte Spill
        sub     r14d, edx
        add     r14d, 8
        mov     dword ptr [rsp + 16], r14d      # 4-byte Spill
        mov     dword ptr [rsp + 12], eax       # 4-byte Spill
        mov     ecx, eax
        jmp     .LBB0_3
.LBB0_7:                                #   in Loop: Header=BB0_3 Depth=2
        mov     rax, qword ptr [rsp + 32]       # 8-byte Reload
        cmp     eax, dword ptr [rsp + 8]        # 4-byte Folded Reload
        lea     ecx, [rax + 1]
        je      .LBB0_8
.LBB0_3:                                #   Parent Loop BB0_1 Depth=1
        mov     r13d, ecx
        imul    r13d, ecx
        mov     rax, qword ptr [rsp + 24]       # 8-byte Reload
        mov     qword ptr [rsp + 32], rcx       # 8-byte Spill
        lea     ebp, [rcx + rax]
        mov     r14d, dword ptr [rsp + 16]      # 4-byte Reload
        mov     r12d, dword ptr [rsp + 4]       # 4-byte Reload
        mov     ebx, dword ptr [rsp + 12]       # 4-byte Reload
        jmp     .LBB0_4
.LBB0_6:                                #   in Loop: Header=BB0_4 Depth=3
        inc     ebx
        inc     r14d
        dec     r12d
        je      .LBB0_7
.LBB0_4:                                #   Parent Loop BB0_1 Depth=1
        mov     eax, ebx
        imul    eax, ebx
        add     eax, r13d
        cmp     eax, r15d
        ja      .LBB0_6
        mov     edi, ebp
        mov     esi, r14d
        mov     edx, dword ptr [rsp + 20]       # 4-byte Reload
        call    simPutPixel@PLT
        jmp     .LBB0_6