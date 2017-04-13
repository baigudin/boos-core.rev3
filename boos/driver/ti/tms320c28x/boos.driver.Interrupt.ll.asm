; ----------------------------------------------------------------------------
; Interrupt low level module
;
; @author    Sergey Baigudin, sergey@baigudin.software
; @copyright 2017 Sergey Baigudin
; @license   http://baigudin.software/license/
; @link      http://baigudin.software
; ----------------------------------------------------------------------------
        .c28_amode
        
        .ref  _c_int00

        .def  _globalDisable__Q2_6driver9InterruptSFv
        .def  _globalEnable__Q2_6driver9InterruptSFb
        .def  _disableLow__Q2_6driver19InterruptControllerSFUi
        .def  _enableLow__Q2_6driver19InterruptControllerSFUib
        .def  _setLow__Q2_6driver19InterruptControllerSFUi
        .def  _clearLow__Q2_6driver19InterruptControllerSFUi
        .def  _jumpLow__Q2_6driver19InterruptControllerSFUi
        .def  _getPieVectors__Q2_6driver19InterruptControllerSFv
       
        .ref  _handler__Q2_6driver19InterruptControllerSFi
        .ref  _contextLow___Q2_6driver19InterruptController

        .asg  _c_int00,                                           m_bootstrap
        .asg  _globalDisable__Q2_6driver9InterruptSFv,            m_global_disable
        .asg  _globalEnable__Q2_6driver9InterruptSFb,             m_global_enable
        .asg  _disableLow__Q2_6driver19InterruptControllerSFUi,   m_disable
        .asg  _enableLow__Q2_6driver19InterruptControllerSFUib,   m_enable
        .asg  _setLow__Q2_6driver19InterruptControllerSFUi,       m_set
        .asg  _clearLow__Q2_6driver19InterruptControllerSFUi,     m_clear
        .asg  _jumpLow__Q2_6driver19InterruptControllerSFUi,      m_jump
        .asg  _getPieVectors__Q2_6driver19InterruptControllerSFv, m_get_table
        .asg  _handler__Q2_6driver19InterruptControllerSFi,       m_handler
        .asg  _contextLow___Q2_6driver19InterruptController,      v_context
    
; ----------------------------------------------------------------------------
; Hardware interrupt vectors
; ----------------------------------------------------------------------------

reset   .macro 
        .ulong          m_bootstrap
        .endm    

vector  .macro          n, g
v_ih_n:n:_g:g:
        .ulong          m_ih_n:n:_g:g:
        .endm    

; ----------------------------------------------------------------------------
; Hardware interrupt handler.
; ----------------------------------------------------------------------------
handler .macro          n, g
m_ih_n:n:_g:g:
        movb            xar0, #:g:
        movb            xar1, #:n:
        bf              m_isr, unc
        .endm
        
; ----------------------------------------------------------------------------
; Interrupt vector table section of PIE.
;
; This section is being loaded and will be alloced by linker.
; It is used for user's code initialization of
; PIE Vectors memory.
; ----------------------------------------------------------------------------
        .data
v_ires:
        reset           
        ; 31 CPU Vectors
        .eval           0, i
        .loop           31
        vector          i, 0
        .eval           i+1, i
        .endloop    
        
        ; 12 PIE Groups
        .eval           1, g
        .loop           12

        ; 8 PIE Group Vectors
        .eval           0, n
        .loop           8
        vector          n, g
        .eval           n+1, n
        .endloop    
        
        .eval           g+1, g
        .endloop
        
; ----------------------------------------------------------------------------
; Interrupt handlers.
; ----------------------------------------------------------------------------
        .text
        
        ; 31 CPU Vector
        .eval           0, i
        .loop           31
        handler         i, 0
        .eval           i+1, i
        .endloop 
        
        ; 12 PIE Groups
        .eval           1, g
        .loop           12

        ; 8 PIE Group Vectors
        .eval           0, n
        .loop           8
        handler         n, g
        .eval           n+1, n
        .endloop    
        
        .eval           g+1, g
        .endloop                    
                
; ----------------------------------------------------------------------------
; Nonreset interrupt service routine.
; ----------------------------------------------------------------------------
        .text
m_isr:
        nop
        bf              m_isr, unc

; ----------------------------------------------------------------------------
; Returns address of PIE vectors table copy.
;
; @return ACC vectors table address.
; ----------------------------------------------------------------------------       
m_get_table:
       movl           xar4, #v_ires  
       lretr

; ----------------------------------------------------------------------------
; Disables all maskable interrupts.
;
; @return AL global interrupt enable bit value before method was called.
; ----------------------------------------------------------------------------
        .text
m_global_disable:
        push            st1
        dint        
        pop             al
        and             al, #1
        xor             al, #1
        lretr

; ----------------------------------------------------------------------------
; Enables all maskable interrupts.
;
; @param AL the returned status by disable method.
; ----------------------------------------------------------------------------
        .text
m_global_enable:
        cmp             al, #0
        bf              m_ret0?, eq
        eint
m_ret0? lretr

; ----------------------------------------------------------------------------
; Locks maskable interrupt source.
;
; @param AR4 hardware interrupt vector number.
; @return AL an interrupt enable source bit in low bit before method was called.
; ----------------------------------------------------------------------------
        .text
m_disable:
        nop
        bf              m_disable, unc

; ----------------------------------------------------------------------------
; Unlocks maskable interrupt source.
;
; @param AR4 hardware interrupt vector number.
; @param AR5 returned status by m_disable procedure.
; ----------------------------------------------------------------------------
        .text
m_enable:
        nop
        bf              m_enable, unc
   
; ----------------------------------------------------------------------------
; Sets a maskable interrupt status.
;
; @param AR4 hardware interrupt vector number.
; ----------------------------------------------------------------------------
        .text
m_set:
        nop
        bf              m_set, unc

; ----------------------------------------------------------------------------
; Clears a maskable interrupt status.
;
; @param AR4 hardware interrupt vector number.
; ----------------------------------------------------------------------------
        .text
m_clear:
        nop
        bf              m_clear, unc
          
; ----------------------------------------------------------------------------
; Jumps to interrupt HW vector.
;
; @param AR4 hardware interrupt vector number.
; ----------------------------------------------------------------------------
        .text
m_jump:
        nop
        bf              m_jump, unc
        