; ----------------------------------------------------------------------------
; Boot routine.
;
; The module performs the tasks to initialize C/C++ run-time environment.
; 
; @author    Sergey Baigudin, sergey@baigudin.software
; @copyright 2016-2017, Embedded Team, Sergey Baigudin
; @license   http://embedded.team/license/
; ----------------------------------------------------------------------------

    ; Set a using ABI which might be EABI if EABI is set to 1, or COFF ABI if EABI is set to 0
    ; Having version 7.0 or greater C6000 compilers might generate object files compatible with EABI 
    ; and have __TI_EABI__ predefined symbol is set to 1 if compiling for EABI and is unset to 0 otherwise. 
    .asg  0, EABI

    .def  _c_int00
    
    ; EABI 
    .if   EABI

    ; COFF ABI
    .else
    
    .def  _getCRecord__Q2_6module4BootSFv
    .def  _getPRecord__Q2_6module4BootSFv

    .ref  _initialize__Q2_6module4BootSFv
    .ref  _main__Q2_6kernel4MainSFv    
    .ref  ___cinit__
    .ref  ___pinit__
    .ref  ___bss__

    .asg  _main__Q2_6kernel4MainSFv,       m_main    
    .asg  _getCRecord__Q2_6module4BootSFv, m_get_cinit
    .asg  _getPRecord__Q2_6module4BootSFv, m_get_pinit
    .asg  _initialize__Q2_6module4BootSFv, m_boot_init    
    .asg  _c_int00,                        m_bootstrap
    .asg  ___cinit__,                      v_cinit
    .asg  ___pinit__,                      v_pinit
    .asg  ___bss__,                        v_bss
    
    .endif ; EABI
    
    .asg  b15, sp
    .asg  b14, dp
    .asg  a15, fp
    ; The operating system stack definition
    .asg  2000h, STACK_SIZE
    .bss  v_stack, STACK_SIZE, 8
    

; ----------------------------------------------------------------------------
; The bootstrap routine.
; ----------------------------------------------------------------------------
        .text
m_bootstrap:
        ; Set CPU register
        mvk             0, a0
        mvc             a0, istp
        mvc             a0, amr
        mvc             a0, irp
        mvc             a0, nrp
        mvk             -1, a0
        mvc             a0, icr
        mvk             3,  a0
        mvc             a0, ier ; set NMIE to enable
        nop
        ; Set CPU registers to zero
        .eval           0, i
        .loop           32
        mvk             0, a:i:
     || mvk             0, b:i:
        .eval           i+1, i
        .endloop
        ; Initialize the ABI pointers
        mvkl            v_stack + STACK_SIZE - 8, sp
        mvkh            v_stack + STACK_SIZE - 8, sp
        mvkl            v_bss, dp
     || mvkl            0, fp
        mvkh            v_bss, dp
     || mvkl            0, fp
        ; Call the boot initialization
        b               m_boot_init
mr_0?   addkpc          mr_0?+4, b3, 4      
        ; Call the system main method
        mvkl            m_termination, b3
     || mvkl            m_main, a3
        mvkh            m_termination, b3
     || mvkh            m_main, a3
        b               a3
        nop             5

; ----------------------------------------------------------------------------
; The termination routine.
; ----------------------------------------------------------------------------
        .text
m_termination:
        idle
        b               m_termination

; ----------------------------------------------------------------------------
; Returns the first record adderess.
;
; @return A4 memory address of .cinit section or NULL.
; ----------------------------------------------------------------------------
        .text
m_get_cinit:
        .if             EABI
        b               b3
        mvk             0, a4
        nop             4        
        .else
        b               b3
        mvkl            v_cinit, a4
     || mvkl            0ffffffffh, b0
        mvkh            v_cinit, a4
     || mvkh            0ffffffffh, b0
        xor             a4, b0, b0
  [!b0] mvk             0, a4
        nop             1
        .endif
        
; ----------------------------------------------------------------------------
; Returns the first record adderess.
;
; @return A4 memory address of .pinit section or NULL.
; ----------------------------------------------------------------------------
        .text
m_get_pinit:
        .if             EABI
        b               b3
        mvk             0, a4
        nop             4        
        .else
        b               b3
        mvkl            v_pinit, a4
     || mvkl            0ffffffffh, b0
        mvkh            v_pinit, a4
     || mvkh            0ffffffffh, b0
        xor             a4, b0, b0
  [!b0] mvk             0, a4
        nop             1
        .endif
            