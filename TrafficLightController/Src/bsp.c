#include "bsp.h"
#include "timer.h"

// exported global variables
volatile int Button_Status = 0;
Light_t Light = RED;

/** @brief  Initialize I/O for lamps
    @retval None
*/
void BSP_Init(void)
{
}

/** @brief  Change lamps to GREEN
    @retval None
*/
void Signal_Pass(void) //Car Pass
{
  WALK_OFF();	Delay(15);	WALK_ON();	Delay(15);
	WALK_OFF();	Delay(15);	WALK_ON();	Delay(15);
	WALK_OFF();	Delay(15);	WALK_ON();	Delay(15);
  WALK_OFF();
	DONT_WALK_ON();
	Delay(DEAD_PERIOD);
	RED_OFF();
	Delay(5);
	GREEN_ON();
	Light = GREEN;
}

/** @brief  Change lamps to RED
    @retval None
*/
void Signal_Block(void)
{
  GREEN_OFF();   //0.5s
	Delay(5);
	YELLOW_ON(); //1s
	Delay(10);
	YELLOW_OFF(); //0.5s
	Delay(5);
	RED_ON(); //DEAD_PERIOD
	Delay(DEAD_PERIOD);
	DONT_WALK_OFF();
	Delay(5);
	WALK_ON();
	Light = RED;
}

/** @brief  Flash YELLOW lamp
    @retval None
*/
void Signal_Flash(void)
{
	RED_OFF();
	GREEN_OFF();
	WALK_OFF();

	YELLOW_OFF();
	DONT_WALK_OFF();
	Delay(10);
	YELLOW_ON();
	DONT_WALK_ON();
	Delay(10); 
	
}
