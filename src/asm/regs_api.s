.text
.globl _delta_cp_regs
.globl _delta_cp_real
_delta_cp_regs:
    pushq %r15
    leaq 8(%rdi),%r15
    movq (%r15),%rax
    movq 8(%r15),%rdi
    movq 16(%r15),%rsi
    movq 24(%r15), %rdx
    movq 32(%r15), %rcx
    movq 40(%r15), %r8
    movq 48(%r15), %r9
    movq 56(%r15), %r10
    movq 64(%r15), %r11
    leaq 128(%r15), %r15
    movsd (%r15),%xmm0
    movsd 8(%r15),%xmm1
    movsd 16(%r15),%xmm2
    movsd 24(%r15),%xmm3
    movsd 32(%r15),%xmm4
    movsd 40(%r15),%xmm5
    movsd 48(%r15),%xmm6
    movsd 56(%r15),%xmm7
    movsd 64(%r15),%xmm8
    movsd 72(%r15),%xmm9
    movsd 80(%r15),%xmm10
    movsd 88(%r15),%xmm11
    movsd 96(%r15),%xmm12
    movsd 104(%r15),%xmm13
    movsd 112(%r15),%xmm14
    movsd 120(%r15),%xmm15 
    popq %r15
    ret

_delta_cp_real:
    pushq %r14
    movq %rdi,%r14
    leaq 8(%rdi),%rdi
    movq %rax,(%rdi)
    movq %r14,8(%rdi)
    movq %rsi,16(%rdi)
    movq %rdx,24(%rdi)
    movq %rcx,32(%rdi)
    movq %r8,40(%rdi)
    movq %r9,48(%rdi)
    movq %r10,56(%rdi)
    movq %r11,64(%rdi)
    movq %r12,72(%rdi)
    movq %r13,80(%rdi)
    popq %r14
    movq %r14,88(%rdi)
    movq %r15,96(%rdi)
    leaq 128(%rdi), %rdi
    movsd %xmm0,(%rdi)
    movsd %xmm1,8(%rdi)
    movsd %xmm2,16(%rdi)
    movsd %xmm3,24(%rdi)
    movsd %xmm4,32(%rdi)
    movsd %xmm5,40(%rdi)
    movsd %xmm6,48(%rdi)
    movsd %xmm7,56(%rdi)
    movsd %xmm8,64(%rdi)
    movsd %xmm9,72(%rdi)
    movsd %xmm10,80(%rdi)
    movsd %xmm11,88(%rdi)
    movsd %xmm12,96(%rdi)
    movsd %xmm13,104(%rdi)
    movsd %xmm14,112(%rdi)
    movsd %xmm15,120(%rdi)
    ret