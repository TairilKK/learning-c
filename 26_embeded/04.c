#include "main.h"

void SystemClock_Config(void);

typedef struct GPIO{
	volatile uint32_t GPIO_MODER;
	volatile uint32_t GPIO_OTYPER;
	volatile uint32_t GPIO_OSPEEDR;
	volatile uint32_t GPIO_PUPDR;
	volatile uint32_t GPIO_IDR;
	volatile uint32_t GPIO_ODR;
	volatile uint32_t GPIO_BSRR;
	volatile uint32_t GPIO_LCKR;
	volatile uint32_t GPIO_AFRL;
	volatile uint32_t GPIO_AFRH;
	volatile uint32_t GPIO_BRR;
	volatile uint32_t GPIO_ASCR;
 }GPIOS, *GPIOSP;


 typedef struct TIM{
	 volatile uint32_t TIMx_CR1;
	 volatile uint32_t TIMx_CR2;
	 uint16_t : 16;
	 volatile uint16_t TIMx_DIER;
	 volatile uint16_t TIMx_SR;
	 volatile uint16_t TIMx_EGR;
	 uint16_t : 32;
	 volatile uint32_t TIMx_CNT;
	 volatile uint16_t TIMx_PSC;
	 volatile uint16_t TIMx_ARR;

 }TIMx, *TIMxP;

#define TIM6_PTR ((TIMxP)0x40001000)
#define TIM7_PTR ((TIMxP)0x40001400)

#define GPIOB_PTR ((GPIOSP) 0x48000400)
#define GPIOG_PTR ((GPIOSP) 0x48001800)

#define RCC_AHB2 (volatile uint32_t *) 0x4002104C
#define RCC_APB1 (volatile uint32_t *) 0x40021058
#define PWR_CR2 (volatile uint32_t *) 0x40007004

#define TIME_DELEY 1000


void delay (unsigned ms){

	TIM6_PTR->TIMx_PSC = 0;
	TIM6_PTR->TIMx_ARR = (uint16_t)ms;

	TIM6_PTR->TIMxCR1 |= 1;
	while ((TIM6_PTR->TIM_SR) == 0);
	TIM6_PTR->TIM_SR &= ~(1);
}


 void displayDigit(uint8_t digit){
  	switch(digit){
		case 0:
			GPIOG_PTR->GPIO_ODR = 63UL;
			break;
		case 1:
			GPIOG_PTR->GPIO_ODR = 6UL;
			break;
		case 2:
			GPIOG_PTR->GPIO_ODR = 91UL;
			break;
		case 3:
			GPIOG_PTR->GPIO_ODR = 79UL;
			break;
		case 4:
			GPIOG_PTR->GPIO_ODR = 102UL;
			break;
		case 5:
			GPIOG_PTR->GPIO_ODR = 109UL;
			break;
		case 6:
			GPIOG_PTR->GPIO_ODR = 125UL;
			break;
		case 7:
			GPIOG_PTR->GPIO_ODR = 7UL;
			break;
		case 8:
			GPIOG_PTR->GPIO_ODR = 127UL;
			break;
		case 9:
			GPIOG_PTR->GPIO_ODR = 111UL;
			break;
		default:
			GPIOG_PTR->GPIO_ODR = 0UL;
		break;
  	}
}

 void GPIO_init(void){

	 /* Zegar dla GPIOB i GPIOG */
	*RCC_AHB2 |= (1 << 1) | (1 << 6);
	/* Reset PWR */
	*RCC_APB1 |= (1 << 28);
	/* Zasilanie wyświetlacza 7segm*/
	*PWR_CR2 |= (1 << 9);

	/* Ustawianie Output */

	/* GPIOB */

	/* PIN2 */
 	GPIOB_PTR->GPIO_MODER &= ~(1 << 5);
 	GPIOB_PTR->GPIO_MODER |= (1 << 4);

 	/* PIN3 */
 	GPIOB_PTR->GPIO_MODER &= ~(1 << 7);
 	GPIOB_PTR->GPIO_MODER |= (1 << 6);
 	/* PIN4 */
 	GPIOB_PTR->GPIO_MODER &= ~(1 << 9);
 	GPIOB_PTR->GPIO_MODER |= (1 << 8);
 	/* PIN5 */
 	GPIOB_PTR->GPIO_MODER &= ~(1 << 11);
 	GPIOB_PTR->GPIO_MODER |= (1 << 10);

 	/* GPIOG */

 	/* PIN0 */
 	GPIOG_PTR->GPIO_MODER &= ~(1 << 1);
 	GPIOG_PTR->GPIO_MODER |= (1 << 0);

 	/* PIN1 */
 	GPIOG_PTR->GPIO_MODER &= ~(1 << 3);
 	GPIOG_PTR->GPIO_MODER |= (1 << 2);

 	/* PIN2 */
 	GPIOG_PTR->GPIO_MODER &= ~(1 << 5);
 	GPIOG_PTR->GPIO_MODER |= (1 << 4);

 	/* PIN3 */
 	GPIOG_PTR->GPIO_MODER &= ~(1 << 7);
 	GPIOG_PTR->GPIO_MODER |= (1 << 6);

 	/* PIN4 */
 	GPIOG_PTR->GPIO_MODER &= ~(1 << 9);
 	GPIOG_PTR->GPIO_MODER |= (1 << 8);

 	/* PIN5 */
 	GPIOG_PTR->GPIO_MODER &= ~(1 << 11);
 	GPIOG_PTR->GPIO_MODER |= (1 << 10);

 	/* PIN6 */
 	GPIOG_PTR->GPIO_MODER &= ~(1 << 13);
 	GPIOG_PTR->GPIO_MODER |= (1 << 12);


 	/* TIM6 */
 	TIM6_PTR->TIMxCR1 = 0x0000;
 	TIM6_PTR->TIMx_CR1 |= (1<<11);
 	TIM6_PTR->TIMx_CR1 |= (1<<7);
 	TIM6_PTR->TIMx_CR1 |= (1<<3);
 	TIM6_PTR->TIMx_CR1 |= (1<<2);



 }

int main(void){

	HAL_Init();
    SystemClock_Config();
    GPIO_init();

    int digits[] = {0,0,0,0};

    while (1){
	  for(int j=0;j<TIME_DELEY/4;j++){
		 for( int i=0; i<4; ++i){
			 displayDigit(digits[i]);
			 GPIOB_PTR->GPIO_ODR = 4<<i;
			 HAL_Delay(1);
		 }
	  }
	 ++digits[3];
	 if(digits[3]>9){
		 digits[3]=0;
		 ++digits[2];
	 }
	 if(digits[2]>9){
		 digits[2]=0;
		 ++digits[1];
	 }
	 if(digits[1]>9){
		 digits[1]=0;
		 ++digits[0];
	 }
	 if(digits[0]>9)
		 digits[0]=0;
	}

}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};


  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}


void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif


