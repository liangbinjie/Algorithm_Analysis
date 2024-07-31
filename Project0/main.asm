global standardMulASM, nullMulASM, russianMulASM
; Compile with:
; nasm -f elf64 main.asm 
; gcc -Wall main.c main.o 

section .text

; In NASM x86_64 rdi is the first argument and rsi is the second argument

standardMulASM:
    mov rax, rdi
    imul rsi      
    ret

nullMulASM:
    mov rax, 0
    ret

russianMulASM:
    mov rdx, 0        ; initialize result to 0
    
russianMulASM_while:
    cmp rsi, 0        ; check if b (rsi) is 0
    je russianMulASM_end

    test rsi, 1       ; check if b is odd
    jz russianMulASM_even

    add rdx, rdi      ; if b is odd, add a (rdi) to result

russianMulASM_even:
    shr rsi, 1        ; divide b by 2
    shl rdi, 1        ; multiply a by 2
    jmp russianMulASM_while

russianMulASM_end:
    mov rax, rdx      ; move result to rax
    ret

    
