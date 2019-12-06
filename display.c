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


void initLcd(void){
    LCD_Position(0,0);
    LCD_PrintString("Pedestrian: ");
    LCD_Position(3,0);
    LCD_PrintString("Cars: ");
}

void displayTimer(uint8 row, uint8 column, uint16 data){
    uint8 temp;
    if((data % 2) == 0){
        temp = (uint8)(data / 2);
        
        if(temp < 10){
            LCD_Position(row,column + 1);
            LCD_PutChar(' ');
            LCD_Position(row,column);
            LCD_PrintDecUint16(temp);
        }else{
            LCD_Position(row,column);
            LCD_PrintDecUint16(temp);
        }
        
    }else{
    //do not display anything
    }
}
/* [] END OF FILE */
