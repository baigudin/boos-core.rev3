; ----------------------------------------------------------------------------
; Boot routine.
;
; The module performs the tasks to initialize C/C++ run-time environment.
; 
; @author    Sergey Baigudin, sergey@baigudin.software
; @copyright 2016-2017, Embedded Team, Sergey Baigudin
; @license   http://embedded.team/license/
; ----------------------------------------------------------------------------
    .state32
    .copy    "module.registers.inc"
    .include "module.constants.inc"    

    .def  _c_int00

    ; EABI 
    .if   __TI_EABI_ASSEMBLER

    ; COFF ABI
    .else
    
    .def  _getCRecord__Q2_6module4BootSFv
    .def  _getPRecord__Q2_6module4BootSFv
    
    .ref  _initialize__Q2_6module4BootSFv
    .ref  _main__Q2_6kernel4MainSFv    
    .ref  ___cinit__
    .ref  ___pinit__
    
    .asg  _main__Q2_6kernel4MainSFv,       m_main    
    .asg  _getCRecord__Q2_6module4BootSFv, m_get_cinit
    .asg  _getPRecord__Q2_6module4BootSFv, m_get_pinit
    .asg  _initialize__Q2_6module4BootSFv, m_boot_init
    .asg  _c_int00,                        m_bootstrap
    .asg  ___cinit__,                      v_cinit
    .asg  ___pinit__,                      v_pinit
    .asg  ___bss__,                        v_bss    
    
    .endif  
    
    ; The operating system stack definition
    .asg  0008h,  STACK_SIZE_UND
    .asg  0020h,  STACK_SIZE_SVC
    .asg  0008h,  STACK_SIZE_ABT            
    .asg  0020h,  STACK_SIZE_IRQ
    .asg  0008h,  STACK_SIZE_FIQ    
    .asg  0400h,  STACK_SIZE_SYS

    .bss  v_stack_und, STACK_SIZE_UND, 8
    .bss  v_stack_svc, STACK_SIZE_SVC, 8
    .bss  v_stack_abt, STACK_SIZE_ABT, 8            
    .bss  v_stack_irq, STACK_SIZE_IRQ, 8    
    .bss  v_stack_fiq, STACK_SIZE_FIQ, 8
    .bss  v_stack_sys, STACK_SIZE_SYS, 8
   
; ----------------------------------------------------------------------------
; The bootstrap routine.        
; ----------------------------------------------------------------------------
    .text
m_bootstrap:
    ; Set FIQ mode registers
    mov     r0,  #PSR_I|PSR_F|PSR_FIQ
    msr     cpsr_cxsf, r0
    mov     r7,  #0
    mov     r8,  #0
    mov     r9,  #0
    mov     r10, #0
    mov     r11, #0
    mov     r12, #0
    ldr     sp,  a_v_stack_fiq    
    mov     lr,  #0
    ; Set Supervisor mode registers
    mov     r0,  #PSR_I|PSR_F|PSR_SVC
    msr     cpsr_cxsf, r0
    ldr     sp,  a_v_stack_svc    
    mov     lr,  #0
    ; Set Abort mode registers
    mov     r0,  #PSR_I|PSR_F|PSR_ABT
    msr     cpsr_cxsf, r0
    ldr     sp,  a_v_stack_abt    
    mov     lr,  #0
    ; Set IRQ mode registers
    mov     r0,  #PSR_I|PSR_F|PSR_IRQ
    msr     cpsr_cxsf, r0
    ldr     sp,  a_v_stack_irq    
    mov     lr,  #0
    ; Set Undefined mode registers
    mov     r0,  #PSR_I|PSR_F|PSR_UND
    msr     cpsr_cxsf, r0
    ldr     sp,  a_v_stack_und    
    mov     lr,  #0
    ; Set System and User mode registers
    mov     r0,  #PSR_I|PSR_F|PSR_SYS    
    msr     cpsr_cxsf, r0
    mov     r0,  #0
    mov     r1,  #0
    mov     r2,  #0
    mov     r3,  #0
    mov     r4,  #0
    mov     r5,  #0
    mov     r6,  #0
    mov     r7,  #0
    mov     r8,  #0
    mov     r9,  #0
    mov     r10, #0
    mov     r11, #0
    mov     r12, #0
    ldr     sp,  a_v_stack_sys        
    mov     lr,  #0
    ; Call the boot initialization    
    bl      m_boot_init
    ; Call the system main method
    ldr     lr,  a_m_termination
    b       m_main

a_m_termination .word m_termination
a_v_stack_und   .word v_stack_und + STACK_SIZE_UND
a_v_stack_svc   .word v_stack_svc + STACK_SIZE_SVC
a_v_stack_abt   .word v_stack_abt + STACK_SIZE_ABT
a_v_stack_irq   .word v_stack_irq + STACK_SIZE_IRQ
a_v_stack_fiq   .word v_stack_fiq + STACK_SIZE_FIQ
a_v_stack_sys   .word v_stack_sys + STACK_SIZE_SYS

; ----------------------------------------------------------------------------
; The termination routine.
; ----------------------------------------------------------------------------
    .text
m_termination:
    b       m_termination    

; ----------------------------------------------------------------------------
; Returns the first record adderess.
;
; @return R0 memory address of .cinit section or NULL.
; ----------------------------------------------------------------------------
    .text
m_get_cinit:
    ldr     r0, a_v_cinit
    ldr     r1, a_v_cinit_err
    cmp     r0, r1
    moveq   r0, #0
    bx      lr

a_v_cinit     .word v_cinit
a_v_cinit_err .word 0ffffffffh

; ----------------------------------------------------------------------------
; Returns the first record adderess.
;
; @return R0 memory address of .pinit section or NULL.
; ----------------------------------------------------------------------------
    .text
m_get_pinit:
    ldr     r0, a_v_pinit
    ldr     r1, a_v_pinit_err
    cmp     r0, r1
    moveq   r0, #0
    bx      lr

a_v_pinit     .word v_pinit
a_v_pinit_err .word 0ffffffffh
