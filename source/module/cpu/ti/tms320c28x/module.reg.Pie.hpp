/**
 * TI TMS320F2833x Peripheral Interrupt Expansion registers.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_REG_PIE_HPP_
#define MODULE_REG_PIE_HPP_

#include "Types.hpp"

namespace module
{
    namespace reg
    {
        struct Pie
        {
          
        public:
          
            /**
             * Default configuration addresses.
             */
            static const uint32 ADDRESS = 0x00000CE0;
            
            /** 
             * Constructor.
             */  
            Pie()
            {
            }
            
            /** 
             * Destructor.
             */    
           ~Pie(){}    
            
            /**
             * Operator new.
             *
             * @param size unused.
             * @param ptr  address of memory.
             * @return address of memory.
             */     
            void* operator new(size_t, uint32 ptr)
            {
                return reinterpret_cast<void*>(ptr);
            }
            
            /**
             * Control Register.
             */
            union Ctrl
            {
                Ctrl(){}
                Ctrl(uint16 v){val = v;}          
               ~Ctrl(){}    
               
                uint16 val;
                struct Val
                {
                    uint16 enpie    : 1;
                    uint16 pievect  : 15;
                } bit;
            } ctrl;
          
            /**
             * Acknowledge Register.
             */
            union Ack
            {
                Ack(){}
                Ack(uint16 v){val = v;}          
               ~Ack(){}    
               
                uint16 val;
                struct Val
                {
                    uint16 pieack : 12;
                    uint16        : 4;
                } bit;
            } ack;
            
            /**
             * PIE INTx Group.
             */      
            struct Group
            {
                /**
                 * Enable Register.
                 */
                union Ier
                {
                    Ier(){}
                    Ier(uint16 v){val = v;}          
                   ~Ier(){}    
                   
                    uint16 val;
                    struct Val
                    {
                        uint16 intx1 : 1;
                        uint16 intx2 : 1;
                        uint16 intx3 : 1;
                        uint16 intx4 : 1;
                        uint16 intx5 : 1;
                        uint16 intx6 : 1;
                        uint16 intx7 : 1;
                        uint16 intx8 : 1;
                        uint16       : 8;
                    } bit;
                } ier;
                
                /**
                 * Flag Register.
                 */
                union Ifr
                {
                    Ifr(){}
                    Ifr(uint16 v){val = v;}          
                   ~Ifr(){}    
                   
                    uint16 val;
                    struct Val
                    {
                        uint16 intx1 : 1;
                        uint16 intx2 : 1;
                        uint16 intx3 : 1;
                        uint16 intx4 : 1;
                        uint16 intx5 : 1;
                        uint16 intx6 : 1;
                        uint16 intx7 : 1;
                        uint16 intx8 : 1;
                        uint16       : 8;
                    } bit;
                } ifr;
            } pie[12];
          
        };
    }
}
#endif // MODULE_REG_PIE_HPP_
