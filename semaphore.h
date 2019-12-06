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
#include <display.h>

#define SET                     (0x01)
#define CLEAR                   (0x00)
#define LED_ON                  (0x01)
#define LED_OFF                 (0x00)
#define GREEN_ON                (0x01)
#define RED_ON                  (0x02)
#define RED_BLINKING            (0x03)
#define GREEN_BLINKING          (0x04)
#define NO_BLINKING             (0x00)
#define MULTIPLICATION_TIMER    (2)
#define NUMBER_OF_SEMAPHORES    (2)
#define FLASH_TIME              (5 * MULTIPLICATION_TIMER)
#define BUTTON_PRESSED_TIME     (20 * MULTIPLICATION_TIMER)
#define BUTTON_CLEARED          (0)
#define BUTTON_PRESSED          (1)
#define EVENT_CLEARED           (0)
#define EVENT_ACQUIRED          (1)
#define SWITCH_TIME_PEDESTRIANS (20 * MULTIPLICATION_TIMER)    // 20 / 2 = 10s
#define SWITCH_TIME_CARS        (50 * MULTIPLICATION_TIMER)    // 40 / 2 = 20s


extern uint32 time;
extern void processSemaphore(uint8 idSemaphore);
extern void processBlinking(uint8 idSemaphore);
extern void initSemaphore(void);
extern void initStruct(void);
extern void processButton(void);
void initLcd(void);
extern uint8 buttonPressed;
enum semaphoreType {vehicle1, ped1}; 

typedef struct {
    uint8 state;
    uint8 time;
    uint8 blinking;
    uint8(*pGetGreen)();
    uint8(*pGetRed)();
    void(*pSetGreen)(uint8);
    void(*pSetRed)(uint8);
}semaphore;
semaphore stSemaphore[NUMBER_OF_SEMAPHORES];

/* [] END OF FILE */
