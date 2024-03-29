; ----------------------------------------------------------------------------
; ARM architecture constants
;
; @author    Sergey Baigudin, sergey@baigudin.software
; @copyright 2016, Embedded Team, Sergey Baigudin
; @license   http://embedded.team/license/
; ----------------------------------------------------------------------------

; Mode bits of program status registers
PSR_USR .set 00000010h
PSR_FIQ .set 00000011h     
PSR_IRQ .set 00000012h 
PSR_SVC .set 00000013h 
PSR_ABT .set 00000017h 
PSR_UND .set 0000001bh 
PSR_SYS .set 0000001fh
  
; Bit masks of program status registers
PSR_M   .set 0000001fh    
PSR_T   .set 00000020h 
PSR_F   .set 00000040h    
PSR_I   .set 00000080h 
PSR_A   .set 00000100h   
PSR_E   .set 00000200h 
PSR_GE  .set 000f0000h 
PSR_J   .set 01000000h 
PSR_Q   .set 08000000h 
PSR_V   .set 10000000h           
PSR_C   .set 20000000h 
PSR_Z   .set 40000000h 
PSR_N   .set 80000000h 
