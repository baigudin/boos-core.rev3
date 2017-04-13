; ----------------------------------------------------------------------------
; Target processor registers.
;
; @author    Sergey Baigudin, sergey@baigudin.software
; @copyright 2017 Sergey Baigudin
; @license   http://baigudin.software/license/
; @link      http://baigudin.software
; ----------------------------------------------------------------------------
        .c28_amode

        .def  _allow__Q2_6driver8RegisterSFv    
        .def  _protect__Q2_6driver8RegisterSFv
        
        .asg  _allow__Q2_6driver8RegisterSFv,  m_eallow    
        .asg  _protect__Q2_6driver8RegisterSFv, m_dallow        

    
; ----------------------------------------------------------------------------
; Allows an access to protected memory mapped CPU registers.
; ----------------------------------------------------------------------------
        .text
m_eallow:
        eallow
        lretr

; ----------------------------------------------------------------------------
; Protects an access to protected memory mapped CPU registers.
; ----------------------------------------------------------------------------
        .text
m_dallow:        
        edis
        lretr

