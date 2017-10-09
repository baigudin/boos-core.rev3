Built libraries
---------------

 - eoos.ti.am18x.coff.lib
    Texas Instruments AM18x ARM Microprocessors family library
    Build Options of ARM Optimizing C/C++ Compiler v4.6.6
    cl470.exe -o3 -me -mv5e --abi=ti_arm9_abi --code_state=32 --coff

 - eoos.ti.tms320c64x.coff.lib
    Texas Instruments TMS320C64x Digital Signal Processors family library
    Build Options of TMS320C6000 C/C++ Optimizing Compiler v6.0.11:
    cl6x.exe -o3 -mv6400 --mem_model:data=far
    
 - eoos.ti.tms320c64xplus.coff.lib
    Texas Instruments TMS320C64x+ Digital Signal Processors family library
    Build Options of TMS320C6000 C/C++ Optimizing Compiler v6.0.11:
    cl6x.exe -o3 -mv6400+ --mem_model:data=far
    
 - eoos.ti.tms320f2833x.coff.lib
    Texas Instruments TMS320F2833x Digital Signal Controllers family library
    Build Options of TMS320C2000 C/C++ Optimizing Compiler v5.2.1:
    cl2000.exe -o3 -d"EOOS_TYPE_WIDTH_LP32" -ml -v28 --float_support=fpu32