; ----------------------------------------------------------------------------
; Boot routine.
;
; The module performs the tasks to initialize C/C++ run-time environment.
; 
; @author    Sergey Baigudin, baigudin@mail.ru
; @copyright 2017 Sergey Baigudin
; @license   http://baigudin.software/license/
; @link      http://baigudin.software
; ----------------------------------------------------------------------------
    .c28_amode
    .def  _c_int00

    .def  _getCRecord__Q2_6driver4BootSFv
    .def  _getPRecord__Q2_6driver4BootSFv

    .ref  _init__Q2_6driver4BootSFv    
    .ref  _main__Q2_6system4MainSFv
    .ref  cinit
    .ref  pinit
    .ref  bss    
    
    .asg  _main__Q2_6system4MainSFv,       m_main
    .asg  _getCRecord__Q2_6driver4BootSFv, m_get_cinit
    .asg  _getPRecord__Q2_6driver4BootSFv, m_get_pinit    
    .asg  _init__Q2_6driver4BootSFv,       m_boot_init    
    .asg  _c_int00,                        m_bootstrap        
    .asg  cinit,                           v_cinit
    .asg  pinit,                           v_pinit 
    .asg  bss,                             v_bss

    ; Mode stacks sizes
    .asg  3c0h, STACK_SIZE_CORE
    ; Mode stacks
    .bss  v_stack_core, STACK_SIZE_CORE, 8
      

; ----------------------------------------------------------------------------
; The bootstrap routine.        
; ----------------------------------------------------------------------------
        .text
m_bootstrap:
        dint
        c28obj                             ; Enable C28x Object Mode
        c28addr                            ; Enable C28x Address Mode
        c28map                             ; Enable C28x Mapping Of M0 and M1 blocks
        mov             sp, #v_stack_core  ; Set kernel stack pointer
        clrc            c, tc, ovm, sxm    ; Clear Status Register 0
        spm             0                  ; Set product shift mode
        clrc            vmap, page0        ; Clear Status Register 1
        setc            dbgm, intm         ; Set Status Register 1
        movw            dp, #0             ; Initialize DP
        nop             *, arp0            ; Set ARP pointer to XAR0        
        asp                                ; Ensure SP is aligned
        mov             acc, #0            ; Set CPU registers to zero
        mov             pl, #0
        mov             ph, #0        
        movl            xt, p        
        and             ier, #0
        and             ifr, #0        
        movb            xar0, #0
        movb            xar1, #0        
        movb            xar2, #0                
        movb            xar3, #0                        
        movb            xar4, #0        
        movb            xar5, #0        
        movb            xar6, #0                
        movb            xar7, #0
        .if             .TMS320C2800_FPU32        
        setflg          rndf32=1           ; Enable rounding in FPU32 mode.
        .endif
        lcr             m_main             ; Call target kernel
        
; ----------------------------------------------------------------------------
; The termination routine.
; ----------------------------------------------------------------------------
        .text
m_termination:
        b               m_termination, unc
        
; ----------------------------------------------------------------------------
; Returns the first record adderess.
;
; @return AR4 memory address of .cinit section or NULL.
; ----------------------------------------------------------------------------
        .text
m_get_cinit:
        mov            al, #v_cinit
        mov            ah, #hi16(v_cinit)
        addb           acc, #1
        b              m_c0?, eq 
        movl           xar4, #v_cinit
        lretr
m_c0?   movl           xar4, #0        
        lretr
        
; ----------------------------------------------------------------------------
; Returns the first record adderess.
;
; @return AR4 memory address of .pinit section or NULL.
; ----------------------------------------------------------------------------
        .text
m_get_pinit:
        mov            al, #v_pinit
        mov            ah, #hi16(v_pinit)
        addb           acc, #1
        b              m_p0?, eq 
        movl           xar4, #v_pinit
        lretr
m_p0?   movl           xar4, #0        
        lretr

            