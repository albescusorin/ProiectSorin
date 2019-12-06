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

uint8 blinkingState, buttonPressed, eventCleared;
void displayTimer(uint8 column, uint8 row, uint16 data);

void initStruct(void){
    stSemaphore[vehicle1].state = GREEN_ON;
    stSemaphore[vehicle1].time = SWITCH_TIME_PEDESTRIANS;
    stSemaphore[vehicle1].blinking = GREEN_BLINKING,
    stSemaphore[vehicle1].pGetGreen = VM_Read;
    stSemaphore[vehicle1].pGetRed = RM_Read;
    stSemaphore[vehicle1].pSetGreen = VM_Write;
    stSemaphore[vehicle1].pSetRed = RM_Write;
    
    stSemaphore[ped1].state = RED_ON;
    stSemaphore[ped1].time = SWITCH_TIME_PEDESTRIANS;
    stSemaphore[ped1].blinking = GREEN_BLINKING,
    stSemaphore[ped1].pGetGreen = VP_Read;
    stSemaphore[ped1].pGetRed = RP_Read;
    stSemaphore[ped1].pSetGreen = VP_Write;
    stSemaphore[ped1].pSetRed = RP_Write; 
    
    buttonPressed = 0;
    eventCleared = 0;
}
void initSemaphore(void){
    uint8 i;
    for(i = 0; i < NUMBER_OF_SEMAPHORES; i++){
        if(stSemaphore[i].state == RED_ON){
            stSemaphore[i].pSetRed(LED_OFF);
            stSemaphore[i].pSetGreen(LED_ON);
            stSemaphore[i].state = GREEN_ON;
        }else if(stSemaphore[i].state == GREEN_ON){
            stSemaphore[i].pSetRed(LED_ON);
            stSemaphore[i].pSetGreen(LED_OFF);
            stSemaphore[i].state = RED_ON;
        }
    }
}
void processSemaphore(uint8 idSemaphore){
    if(stSemaphore[idSemaphore].time == CLEAR){
        if(stSemaphore[idSemaphore].state == RED_ON){
            stSemaphore[idSemaphore].pSetRed(LED_OFF);
            stSemaphore[idSemaphore].pSetGreen(LED_ON);
            stSemaphore[idSemaphore].state = GREEN_ON;    
        }else if(stSemaphore[idSemaphore].state == GREEN_ON){
            stSemaphore[idSemaphore].pSetRed(LED_ON);
            stSemaphore[idSemaphore].pSetGreen(LED_OFF);
            stSemaphore[idSemaphore].state = RED_ON;
        }
        if(stSemaphore[vehicle1].state == GREEN_ON){
            stSemaphore[idSemaphore].time = SWITCH_TIME_CARS;
        }else{
            stSemaphore[idSemaphore].time = SWITCH_TIME_PEDESTRIANS;
        }
        eventCleared = EVENT_CLEARED;
        buttonPressed = BUTTON_CLEARED;
    }
} 
void processBlinking(uint8 idSemaphore){
    stSemaphore[idSemaphore].time = stSemaphore[idSemaphore].time - 1;
    if(stSemaphore[idSemaphore].time <= FLASH_TIME){
        if((stSemaphore[idSemaphore].blinking == GREEN_BLINKING) && (stSemaphore[idSemaphore].state == GREEN_ON)){
            blinkingState =~ stSemaphore[idSemaphore].pGetGreen();
            stSemaphore[idSemaphore].pSetGreen(blinkingState);
        }    
    }
    displayTimer(PEDESTRIAN_LCD_ROW, PEDESTRIAN_LCD_COLUMN, stSemaphore[ped1].time);
    displayTimer(CARS_LCD_ROW, CARS_LCD_COLUMN, stSemaphore[vehicle1].time);
    time = CLEAR;
}
void processButton(void){
    uint8 i;
    if((buttonPressed == BUTTON_PRESSED) && (eventCleared == EVENT_CLEARED) && (stSemaphore[vehicle1].state == GREEN_ON)){
        eventCleared = EVENT_ACQUIRED;
        for(i = 0; i < NUMBER_OF_SEMAPHORES; i++){
            if(stSemaphore[vehicle1].time >= BUTTON_PRESSED_TIME){
                stSemaphore[i].time = BUTTON_PRESSED_TIME;
            }else{
                //do nothing
            }
        }
    }
}
/* [] END OF FILE */
