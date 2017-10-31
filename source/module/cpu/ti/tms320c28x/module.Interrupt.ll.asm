; ----------------------------------------------------------------------------
; Interrupt low level module.
;
; @author    Sergey Baigudin, sergey@baigudin.software
; @copyright 2017, Embedded Team, Sergey Baigudin
; @license   http://embedded.team/license/
; ----------------------------------------------------------------------------
        .c28_amode
        
        .ref  _c_int00
        
        .def  _disableAll__Q2_6module9InterruptSFv
        .def  _enableAll__Q2_6module9InterruptSFb
        .def  _disableLow__Q2_6module19InterruptControllerSFUl
        .def  _enableLow__Q2_6module19InterruptControllerSFUlb
        .def  _setLow__Q2_6module19InterruptControllerSFUl
        .def  _clearLow__Q2_6module19InterruptControllerSFUl
        .def  _jumpLow__Q2_6module19InterruptControllerSFUl
        .def  _getVectorsLow__Q2_6module19InterruptControllerSFv
       
        .ref  _handler__Q2_6module19InterruptControllerSFiT1
        .ref  _contextLow___Q2_6module19InterruptController
        
        .asg  _c_int00,                                           m_bootstrap
        .asg  _disableAll__Q2_6module9InterruptSFv,               m_global_disable
        .asg  _enableAll__Q2_6module9InterruptSFb,                m_global_enable
        .asg  _disableLow__Q2_6module19InterruptControllerSFUl,   m_disable
        .asg  _enableLow__Q2_6module19InterruptControllerSFUlb,   m_enable
        .asg  _setLow__Q2_6module19InterruptControllerSFUl,       m_set
        .asg  _clearLow__Q2_6module19InterruptControllerSFUl,     m_clear
        .asg  _jumpLow__Q2_6module19InterruptControllerSFUl,      m_jump
        .asg  _getVectorsLow__Q2_6module19InterruptControllerSFv, m_get_table
        .asg  _handler__Q2_6module19InterruptControllerSFiT1,     m_handler
        .asg  _contextLow___Q2_6module19InterruptController,      v_context
    
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
        movb            al, #:n:
        movb            ah, #:g:
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
        .eval           1, n
        .loop           31
        vector          n, 12
        .eval           n+1, n
        .endloop    
        
        ; 12 PIE Groups
        .eval           0, g
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
        .eval           1, n
        .loop           31
        handler         n, 12
        .eval           n+1, n
        .endloop 
        
        ; 12 PIE Groups
        .eval           0, g
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
        ; Full context save
        asp
        push            rb
        push            ar1h:ar0h
        movl            *sp++, xar4
        movl            *sp++, xar5
        movl            *sp++, xar6
        movl            *sp++, xar7
        movl            *sp++, xt
        mov32           *sp++, stf
        mov32           *sp++, r0h
        mov32           *sp++, r1h
        mov32           *sp++, r2h
        mov32           *sp++, r3h
        setflg          rndf32=1, rndf64=1
        spm             0
        clrc            ovm, page0
        clrc            amode
        ; Call C++ routine
        lcr            m_handler
        ; Full context restore        
        mov32           r3h,   *--sp,  uncf
        mov32           r2h,   *--sp,  uncf
        mov32           r1h,   *--sp,  uncf
        mov32           r0h,   *--sp,  uncf
        mov32           stf,   *--sp
        movl            xt,    *--sp
        movl            xar7,  *--sp        
        movl            xar6,  *--sp
        movl            xar5,  *--sp
        movl            xar4,  *--sp
        pop             ar1h:ar0h
        pop             rb
        nasp
        iret

; ----------------------------------------------------------------------------
; Returns address of PIE vectors table copy.
;
; @return ACC vectors table address.
; ----------------------------------------------------------------------------       
m_get_table:
        movl            xar4, #v_ires  
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
; @param AL a register bit mask.
; @return AL an interrupt enable source bit in low bit before method was called.
; ----------------------------------------------------------------------------
        .text
m_disable:
        mov             ar0, acc
        not             acc
        mov             ar4, ier
        and             acc, ar4
        mov             ier, al 
        mov             acc, ar0
        and             acc, ar4
        cmp             al, #0
        bf              m_ret1?, eq
        mov             acc, #1
m_ret1? lretr        


; ----------------------------------------------------------------------------
; Unlocks maskable interrupt source.
;
; @param ACC a register bit mask.
; @param AR4 returned status by m_disable procedure.
; ----------------------------------------------------------------------------
        .text
m_enable:
        banz            m_set0?, ar4--
        lretr           
m_set0? mov             ar4, ier
        or              acc, ar4
        mov             ier, al        
        lretr

; ----------------------------------------------------------------------------
; Sets a maskable interrupt status.
;
; @param ACC a register bit mask.
; ----------------------------------------------------------------------------
        .text
m_set:
        push            ifr
        pop             ar4
        or              acc, ar4
        push            al
        pop             ifr
        lretr

; ----------------------------------------------------------------------------
; Clears a maskable interrupt status.
;
; @param ACC a register bit mask.
; ----------------------------------------------------------------------------
        .text
m_clear:
        not             acc
        push            ifr
        pop             ar4
        and             acc, ar4
        push            al
        pop             ifr
        lretr
          
; ----------------------------------------------------------------------------
; Jumps to interrupt HW vector.
;
; @param AR4 hardware interrupt vector number.
; ----------------------------------------------------------------------------
        .text
m_jump:
        mov             acc, #0AAAAh << #15
        lsl             acc, #1
        mov             al,  #0BBBBh
        push            acc
        mov             acc, #0CCCCh << #15
        lsl             acc, #1   
        mov             al,  #0DDDDh
m_wait_jump:
        nop
        bf              m_wait_jump, unc
        