/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <semaphore.h>

uint32 time = 0;
void initHw(void);
void initLcd(void);

int main(void)
{
    uint8 i;
    /* set up PSoC registers for tracing */
    CY_SET_REG8(CYDEV_MFGCFG_MLOGIC_DEBUG, 0x8); /* swv_clk_sel = CPU_clk / 2 */
    CY_SET_REG32(CYDEV_PANTHER_TRACE_CFG, 2); /* trace mode enable, SWV mode disable */
    CyGlobalIntEnable; /* Enable global interrupts. */
    initHw();
    initStruct();
    initSemaphore();
    initLcd();
    
    for(;;)
    {
        switch(time){
            case SET:{
                for(i = 0; i < NUMBER_OF_SEMAPHORES; i++){
                    processBlinking(i);
                }
                break;
            }
            case CLEAR:{
                for(i = 0; i < NUMBER_OF_SEMAPHORES; i++){
                    processSemaphore(i);
                    processButton();
                }
                break;
            }
        }    
    }
}

void initHw(void){
    Timer_Start();
    timer_isr_Start();
    Buton_isr_Start();
    LCD_Start();
}
/* [] END OF FILE */
