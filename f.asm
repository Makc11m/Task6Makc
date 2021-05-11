section .text
global f1
global f2
global f3

f1:
    push ebp
    mov ebp, esp
    finit
    fld qword [ebp + 8]
    fld qword [ebp + 8]
    fmulp
    fld1
    faddp
    fld1
    fld1
    faddp
    fld1
    faddp
    fld1
    faddp
    fdivrp
    fld1
    faddp
    pop ebp
    ret
    
f2:
    push ebp
    mov ebp, esp
    finit
    fld qword [ebp + 8]
    fld qword [ebp + 8]
    fmulp
    fld qword [ebp + 8]
    fmulp
    pop ebp
    ret
    
    f3:
    push ebp
    mov ebp, esp
    mov ecx, 0
    finit
    fld qword [ebp + 8]
    fldz 
    fcomip
    ja .2
    .1:
        .st:
        fld1
        fcomip
        jb .incom
        jmp .skip
        .incom:
        inc ecx
        fld1
        fsubp
        jmp .st
        .skip:
        f2xm1   
        fld1
        faddp   
        fld1
        .mul:
        cmp ecx, 0
        je .finish
        dec ecx
        fld1
        fld1
        faddp
        fmulp
        jmp .mul
        .finish:
        fmulp
        fld1
        fdivrp
        jmp .end
    .2:
        fchs
        .st1:
        fld1
        fcomip
        jb .incom1
        jmp .skip1
        .incom1:
        inc ecx
        fld1
        fsubp
        jmp .st1
        .skip1:
        f2xm1   
        fld1
        faddp
        fld1
        .mul1:
        cmp ecx, 0
        je .finish1
        dec ecx
        fld1
        fld1
        faddp
        fmulp
        jmp .mul1
        .finish1:
        fmulp
    .end:
    pop ebp
    ret