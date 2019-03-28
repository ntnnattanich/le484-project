#include "ctrler.h"
#include "bsp.h"
#include <stdio.h>
#include "main.h"
#include "timer.h"
Ctrler_State_t Ctrler_State = RESTART;

void Ctrler_Init()
{
}

uint32_t Ctrler_Exec(Event_t evt)
{
    uint32_t timeout_value = 0;
    switch(Ctrler_State) {
			case OUT_OF_SERVICE:
				Signal_Flash();
			break; 
				case RESTART:
					Ctrler_State = THROUGH;
					timeout_value = 20;
					Signal_Pass();
					break; 
        case THROUGH:
					if(evt == MODE_CHANGE) {
						Ctrler_State = OUT_OF_SERVICE;
						break;
					}
					if(evt == BUTTON && TimeGreen > MIN_GREEN_TIME){ 
						Ctrler_State = BLOCKED;
						timeout_value = WALK_INTERVAL;
						Signal_Block();
					}
					else if(evt == BUTTON && TimeGreen < MIN_GREEN_TIME){
						Ctrler_State = WAIT;
						timeout_value = MIN_GREEN_TIME - TimeGreen;
					}
					
            break;
				case BLOCKED:
					if(evt == MODE_CHANGE) {
						Ctrler_State = OUT_OF_SERVICE;
						break;
					}
					printf("\tWALK: %2d s\n", ((Timeout_Value-Tick))/10);
					if (evt == TIMEOUT){
						Ctrler_State = THROUGH;
						Signal_Pass();
						printf("TIME OUT\n");
					}
					break;
				case WAIT:
					
				     printf("\tDONT WALK: %2d s\n", (MIN_GREEN_TIME - TimeGreen)/10);
						
					if(evt == MODE_CHANGE) {
						Ctrler_State = OUT_OF_SERVICE;
						break;
					}
					if(evt == TIMEOUT){
						Ctrler_State = BLOCKED;
						timeout_value = WALK_INTERVAL;
						Signal_Block();
					}
					break; 
        default:
            Ctrler_State = OUT_OF_SERVICE;
    }
    return timeout_value;
}
