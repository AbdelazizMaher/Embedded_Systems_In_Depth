/* LEARN-IN-DEPTH-STM32-CORTEXM3-LED-TOGGLE-STARTUP
 *  BY:ABDELAZIZ MAHER */

.section .vectors

.word 0x20001000        /*stack pointer address*/
.word _reset            /* Reset */
.word Vector_handler    /* NMI */
.word Vector_handler    /* Hard Fault */
.word Vector_handler    /* MM Fault */
.word Vector_handler    /* Bus Fault */
.word Vector_handler    /* Usage Fault */
.word Vector_handler    /* Reserved */
.word Vector_handler    /* Reserved */
.word Vector_handler    /* Reserved */
.word Vector_handler    /* Reserved */
.word Vector_handler    /* SV Call */
.word Vector_handler    /* Debug Reserved */
.word Vector_handler    /* Reserved */  
.word Vector_handler    /* PendSV */
.word Vector_handler    /* SysTick */
.word Vector_handler    /* IRQ0 */
.word Vector_handler    /* IRQ1 */
.word Vector_handler    /* IRQ2 */
.word Vector_handler    /* IRQ3 ...*/
        /* ... on to IRQ67   */
        
.section .text

_reset:
    bl main
    b .
    
.thumb_func
Vector_handler:
    b _reset