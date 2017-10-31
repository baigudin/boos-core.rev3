; ----------------------------------------------------------------------------
; Interrupt low level module.
;
; @author    Sergey Baigudin, sergey@baigudin.software
; @copyright 2014-2017, Embedded Team, Sergey Baigudin
; @license   http://embedded.team/license/
; ----------------------------------------------------------------------------

    ; Set a using ABI which might be EABI if EABI is set to 1, or COFF ABI if EABI is set to 0
    ; Having version 7.0 or greater C6000 compilers might generate object files compatible with EABI 
    ; and have __TI_EABI__ predefined symbol is set to 1 if compiling for EABI and is unset to 0 otherwise. 
    .asg  0, EABI

    .ref  _c_int00
    
    .asg  b15, sp
    .asg  b14, dp
    .asg  a15, fp
    
    .asg  0001h, C_REG_GIE
    .asg  0002h, C_REG_SGIE

    ; EABI
    .if   EABI
    
    ; COFF ABI
    .else

    .def  _disableAll__Q2_6module9InterruptSFv
    .def  _enableAll__Q2_6module9InterruptSFb
    .def  _disableLow__Q2_6module19InterruptControllerSFUi
    .def  _enableLow__Q2_6module19InterruptControllerSFUib
    .def  _setLow__Q2_6module19InterruptControllerSFUi
    .def  _clearLow__Q2_6module19InterruptControllerSFUi
    .def  _jumpLow__Q2_6module19InterruptControllerSFUi
    .def  _initLow__Q2_6module19InterruptControllerSFv
   
    .ref  ___bss__
    .ref  _handler__Q2_6module19InterruptControllerSFi
    .ref  _buffer___Q3_6module19InterruptController8Contexts
    
    .asg  ___bss__,                                           m_bss
    .asg  _disableAll__Q2_6module9InterruptSFv,               m_global_disable
    .asg  _enableAll__Q2_6module9InterruptSFb,                m_global_enable
    .asg  _disableLow__Q2_6module19InterruptControllerSFUi,   m_disable
    .asg  _enableLow__Q2_6module19InterruptControllerSFUib,   m_enable
    .asg  _setLow__Q2_6module19InterruptControllerSFUi,       m_set
    .asg  _clearLow__Q2_6module19InterruptControllerSFUi,     m_clear
    .asg  _jumpLow__Q2_6module19InterruptControllerSFUi,      m_jump
    .asg  _initLow__Q2_6module19InterruptControllerSFv,       m_init
    .asg  _handler__Q2_6module19InterruptControllerSFi,       m_handler
    .asg  _buffer___Q3_6module19InterruptController8Contexts, v_context

    .endif

; ----------------------------------------------------------------------------
; Hardware interrupt handler.
;
; This is a macro command for interrupts table 
; that is used for reserved vectors.
; It has fixed size that equals eight.
; ----------------------------------------------------------------------------
reserve .macro
        .align          20h
mc_ri?  b               mc_ri?
        nop             5
        .endm

; ----------------------------------------------------------------------------
; Hardware nonmaskable interrupt handler.
;
; This is a macro command for nonmaskable interrupt table.
; It has fixed size that equals to eight.
; ----------------------------------------------------------------------------
nmi     .macro
        .align          20h
        b               nrp
        nop             5    
        .endm

; ----------------------------------------------------------------------------
; Hardware interrupt handler (the execution is 7 cycles).
;
; This is a macro command for interrupts table.
; It has fixed size that equals to eight.
; ----------------------------------------------------------------------------
handler .macro          num
        .align          20h
        stdw            b1:b0, *-sp[3]
     || mvkl            v_context, b1
        stdw            a1:a0, *-sp[2]
     || mvkh            v_context, b1
     || b               m_isr
        ldw             *++b1[ (num - 4) * 2 ], a0
        mvk             num - 4, b0
        nop             3
        .endm
        
; ----------------------------------------------------------------------------
; Hardware interrupts table.
; ----------------------------------------------------------------------------
        .sect           ".hwi"
m_reset:
        ; Reset interrupt vector
        .align          20h
        b               m_reset+24
     || dint
        mvk             0, b0
     || mvkl            _c_int00, a0        
        mvc             b0, tsr
     || mvkh            _c_int00, a0
        b               a0
        nop             5
        ; Nonmaskable interrupt vector
        nmi
        reserve
        reserve
        ; Nonreset interrupts vectors
        handler         4 
        handler         5 
        handler         6 
        handler         7 
        handler         8 
        handler         9 
        handler         10
        handler         11
        handler         12
        handler         13
        handler         14
        handler         15

; ----------------------------------------------------------------------------
; Nonreset interrupt service routine.
;
; 07 cycles is vector execution
; 22 cycles is save time of context and branch to routine.
; 28 cycles is restore time of context and return from interrupt.
; 
; 57 cycles is total service time.
; ----------------------------------------------------------------------------
        .text
m_isr:
        ; Store the context 
        stdw            b1:b0, *-sp[1]
     || add             a0, 8, b0
     || mv              sp, a1
     || mv              sp, b1
        stdw            a3:a2, *+a0[2]
     || stdw            b3:b2, *+b0[2]
        lddw            *-a1[2], a3:a2
     || lddw            *-b1[3], b3:b2
        stdw            a5:a4, *++a0[4]
     || stdw            b5:b4, *++b0[4]
        ; Load the vector number to A4 argument register and
        ; a memory address of the vector low context to A5
        lddw            *-sp[1], a5:a4        
        stdw            a7:a6, *++a0[2]
     || stdw            b7:b6, *++b0[2]
        stdw            a9:a8, *++a0[2]
     || stdw            b9:b8, *++b0[2]
     || mvc             ilc, b6    
        stdw            a3:a2, *-a0[8]
     || stdw            b3:b2, *-b0[8]
     || mv              b6, a6
     || mvc             rilc, b7
        stdw            a11:a10, *++a0[2]
     || stdw            b11:b10, *++b0[2]
     || mv              b7, a7     
    ;|| mvc             ilc, b6 ; FOR BACKLOG STORING A REGISTER
        stdw            a13:a12, *++a0[2]
     || stdw            b13:b12, *++b0[2]
    ;|| mvc             rilc, b7 ; FOR BACKLOG STORING A REGISTER     
        stdw            a15:a14, *++a0[2]
     || stdw            b15:b14, *++b0[2]
        ; Load an interrupt TOS address to B15 (SP) register and
        ; Remove an address of  the vector low context to A14
        lddw            *a5, b15:b14
     || mv              a5, a14
     || mvc             amr, b2
     || zero            b4
        stdw            a17:a16, *++a0[2]
     || stdw            b17:b16, *++b0[2]
     || mvc             irp, b3
        stdw            a19:a18, *++a0[2]
     || stdw            b19:b18, *++b0[2]
     || mv              b2, a2
     || mvc             csr, b2
        stdw            a21:a20, *++a0[2]
     || stdw            b21:b20, *++b0[2]
     || mv              b3, a3
     || mvc             itsr, b3
        stdw            a23:a22, *++a0[2]
     || stdw            b23:b22, *++b0[2]
        stdw            a25:a24, *++a0[2]
     || stdw            b25:b24, *++b0[2]
     || mvkl            m_bss, dp    
        ; Call an interrupt handler
     || b               m_handler     
        stdw            a27:a26, *++a0[2]
     || stdw            b27:b26, *++b0[2]
     || mvkh            m_bss, dp
        stdw            a29:a28, *++a0[2]
     || stdw            b29:b28, *++b0[2]
     || mvc             b4, amr
        stdw            a31:a30, *++a0[2]
     || stdw            b31:b30, *++b0[2]
     || mvc             a1, irp
        ; Store A2-AMR, A3-IRP, B2-CSR, and B3-ITSR
        stdw            a3:a2, *+a0[2]
     || stdw            b3:b2, *+b0[2]
        ; Store A6-ILC, A7-RILC, B7-TMP1, and B7-TMP2
        stdw            a7:a6, *+a0[4]
     || stdw            b7:b6, *+b0[4]                  
     || zero            fp
     || addkpc          m_restore?, b3, 0
m_restore?
        ; Restore a context 
        ldw             *a14, a31
        mvk             20h, a28
     || mvk             20h, b28
        mvk             22h, a26
     || mvk             22h, b26
        nop             2
        add             a31, 8, b31
        ; Store A26-ILC, A27-RILC, B26-TMP1, and B27-TMP2
        lddw            *+a31[a26], a27:a26
     || lddw            *+b31[b26], b27:b26
        ; Load A28-AMR, A29-IRP, B28-CSR, and B29-backlog to registers     
        lddw            *+a31[a28], a29:a28
     || lddw            *+b31[b28], b29:b28
        lddw            *a31++[2], a1:a0
     || lddw            *b31++[2], b1:b0
        lddw            *a31++[2], a3:a2
     || lddw            *b31++[2], b3:b2
        lddw            *a31++[2], a5:a4
     || lddw            *b31++[2], b5:b4
        lddw            *a31++[2], a7:a6
     || lddw            *b31++[2], b7:b6
     || mvc             a26, ilc
        lddw            *a31++[2], a9:a8
     || lddw            *b31++[2], b9:b8
     || mvc             a27, rilc     
        lddw            *a31++[2], a11:a10
     || lddw            *b31++[2], b11:b10
    ;|| mvc             b26, tmp1 ; FOR BACKLOG RESTORING A REGISTER     
        lddw            *a31++[2], a13:a12
     || lddw            *b31++[2], b13:b12
    ;|| mvc             b27, tmp2 ; FOR BACKLOG RESTORING A REGISTER          
        lddw            *a31++[2], a15:a14
     || lddw            *b31++[2], b15:b14
     || mvc             a29, irp     
        lddw            *a31++[2], a17:a16
     || lddw            *b31++[2], b17:b16
     || mvc             a28, amr          
        lddw            *a31++[2], a19:a18
     || lddw            *b31++[2], b19:b18
     || mvc             b29, itsr         
        lddw            *a31++[2], a21:a20
     || lddw            *b31++[2], b21:b20
     || mvc             b28, csr          
        lddw            *a31++[2], a23:a22
     || lddw            *b31++[2], b23:b22
        lddw            *a31++[2], a25:a24
     || lddw            *b31++[2], b25:b24
        lddw            *a31++[2], a27:a26
     || lddw            *b31++[2], b27:b26
        lddw            *a31++[2], a29:a28
     || lddw            *b31++[2], b29:b28
     || b               irp
        lddw            *a31++[2], a31:a30
     || lddw            *b31++[2], b31:b30
        nop             4

; ----------------------------------------------------------------------------
; Disables all maskable interrupts.
;
; @return A4 global interrupt enable bit value before method was called.
; ----------------------------------------------------------------------------
        .text
m_global_disable:
        b               b3
        dint
        mvc             tsr, b0        
        and             C_REG_SGIE, b0, a4
        shr             a4, 1, a4 
        nop             1

; ----------------------------------------------------------------------------
; Enables all maskable interrupts.
;
; @param A4 the returned status by disable method.
; ----------------------------------------------------------------------------
        .text
m_global_enable:
        b               b3
        and             1, a4, a1
     || mvc             tsr, b0
   [a1] or              C_REG_SGIE, b0, b0
  [!a1] and            ~C_REG_SGIE, b0, b0   
        mvc             b0, tsr
        rint
        
; ----------------------------------------------------------------------------
; Locks maskable interrupt source.
;
; @param A4 hardware interrupt vector number.
; @return A4 an interrupt enable source bit before method was called.
; ----------------------------------------------------------------------------
        .text
m_disable:
        b               b3
     || mvk             1, a1
        dint
     || shl             a1, a4, a1
        mvc             ier, b0
     || not             a1, a1
        shr             b0, a4, a4
     || and             b0, a1, a1
        and             a4, 1, a4
     || mvc             a1, ier            
        rint

; ----------------------------------------------------------------------------
; Unlocks maskable interrupt source.
;
; @param A4 hardware interrupt vector number.
; @param B4 returned status by m_disable procedure.
; ----------------------------------------------------------------------------
        .text
m_enable:
        b               b3
     || and             1, b4, a1
        dint
     || shl             a1, a4, a1         
     || mvc             ier, b0
        or              b0, a1, b0 
        mvc             b0, ier    
        rint
        nop             1        
   
; ----------------------------------------------------------------------------
; Sets a maskable interrupt status.
;
; @param A4 hardware interrupt vector number.
; ----------------------------------------------------------------------------
        .text
m_set:
        b               b3        
        mvk             1, a1     
        shl             a1, a4, a0
        mvc             a0, isr   
        mvk             0, a4         
        nop             1         

; ----------------------------------------------------------------------------
; Clears a maskable interrupt status.
;
; @param A4 hardware interrupt vector number.
; ----------------------------------------------------------------------------
        .text
m_clear:
        b               b3        
        mvk             1, a1     
        shl             a1, a4, a0
        mvc             a0, icr   
        mvk             0, a4         
        nop             1 
          
; ----------------------------------------------------------------------------
; Jumps to interrupt HW vector.
;
; The method must be executed in Supervisor Mode, as it works 
; with ITSR register. Also, the OS basically is being executed 
; in the mode and does not switch any tasks to User Mode. So, 
; the algorithm will be changed when a circumstance is changed.
;
; @param A4 hardware interrupt vector number.
; ----------------------------------------------------------------------------
        .text
m_jump:
        ; Save TSR to ITSR, disable global interrupts,
        ; and calculate interrupt vector address
        b               m_jmp?
     || mvc             tsr, b0
        dint
     || mvc             b0, itsr        
     || shl             a4, 5, a4             
        mvkl            m_reset, a0
        mvkh            m_reset, a0     
        add             a0, a4, a4     
        nop 
        ; Jump to the vector
m_jmp?  b               a4
        mvkl            m_ret?, b0
        mvkh            m_ret?, b0
        mvc             b0, irp
        nop             2
        ; Return point
m_ret?  b               b3
        nop             5
        
; ----------------------------------------------------------------------------
; Initializes the interrupt controller.
; ----------------------------------------------------------------------------
m_init:
        mvk             0, a0
        mvc             a0, irp
        mvc             a0, nrp
        mvk             -1, a0
        mvc             a0, icr
        mvk             3,  a0
        mvc             a0, ier ; enable NMI
        b               b3        
        mvkl            m_reset, a0
        mvkh            m_reset, a0        
        mvc             a0, istp        
        nop             2
        
