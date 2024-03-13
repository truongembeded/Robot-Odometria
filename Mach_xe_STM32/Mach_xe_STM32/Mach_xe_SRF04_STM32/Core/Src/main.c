#include "main.h"
#include "lcd1602_4bit.h"
#include "stdio.h"

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);

#define trig GPIO_PIN_9
#define echo GPIO_PIN_8
#define max 200

//#define in1 GPIO_PIN_5
//#define in2 GPIO_PIN_4
//#define in3 GPIO_PIN_6
//#define in4 GPIO_PIN_7

#define in1 GPIO_PIN_6
#define in2 GPIO_PIN_7
#define in3 GPIO_PIN_5
#define in4 GPIO_PIN_4

int pulse,distance;
long		xung,kc,tt,tam,qd;

void delay_us(uint32_t t)
{
	TIM3->CNT=0;
	while(TIM3->CNT < t);
}
void getSRF04()
{
	HAL_GPIO_WritePin(GPIOB,trig,GPIO_PIN_RESET);
	delay_us(2);
	HAL_GPIO_WritePin(GPIOB,trig,GPIO_PIN_SET);
	delay_us(10);
	HAL_GPIO_WritePin(GPIOB,trig,GPIO_PIN_RESET);
	while(HAL_GPIO_ReadPin(GPIOB,echo) == 0);
	TIM3->CNT=0;
	while(HAL_GPIO_ReadPin(GPIOB,echo) == 1);
	pulse=TIM3->CNT;
	distance=pulse/2/29.412;
	if(distance>300)		distance=300;	
	kc=distance;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin==GPIO_PIN_10)
	{
		if(tam==0)
		{
			if(tt==0)
			{
				xung++;
				qd=xung*200/4112;				// 4780
				if(xung>2300)			//2m
				{
					tt=1;
					xung=0;
				}
			}
		}
	}
}
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
	
	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_Base_Start(&htim3);
	Lcd_Init();
	
	Lcd_gotoxy(0,0);
  Lcd_write_string("    BAT DAU     ");
	Lcd_gotoxy(0,1);
  Lcd_write_string("    CHUAN BI    ");
	HAL_GPIO_WritePin(GPIOB,in1,GPIO_PIN_RESET);				// re phai
	HAL_GPIO_WritePin(GPIOB,in2,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,in3,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,in4,GPIO_PIN_RESET);
	HAL_Delay(2000);
	
	tt=0;
	tam=0;
  while (1)
  {
		/*Lcd_gotoxy(0,0);
		Lcd_write_string("XUNG:");
		Lcd_write_char(xung/1000%10+0x30);
		Lcd_write_char(xung/100%10+0x30);
		Lcd_write_char(xung/10%10+0x30);
		Lcd_write_char(xung%10+0x30);*/
		
		Lcd_gotoxy(0,0);
		Lcd_write_string("DOAN:");
		Lcd_write_char(qd/100%10+0x30);
		Lcd_write_char(qd/10%10+0x30);
		Lcd_write_char(qd%10+0x30);
		Lcd_write_string("cm        ");
		Lcd_gotoxy(0,1);
		Lcd_write_string("KC:");
		Lcd_write_char(distance/100%10+0x30);
		Lcd_write_char(distance/10%10+0x30);
		Lcd_write_char(distance%10+0x30);
		Lcd_write_string("cm         ");
		HAL_Delay(100);
		
		if(tt==0)
		{
			getSRF04();
			if(kc<15)
			{
				tam=1;
				HAL_GPIO_WritePin(GPIOB,in1,GPIO_PIN_SET);				// re phai
				HAL_GPIO_WritePin(GPIOB,in2,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,in3,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,in4,GPIO_PIN_SET);
				HAL_Delay(500);
				HAL_GPIO_WritePin(GPIOB,in1,GPIO_PIN_SET);				// di thang
				HAL_GPIO_WritePin(GPIOB,in2,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,in3,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,in4,GPIO_PIN_RESET);
				HAL_Delay(1500);
				HAL_GPIO_WritePin(GPIOB,in1,GPIO_PIN_RESET);		// re trai
				HAL_GPIO_WritePin(GPIOB,in2,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,in3,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,in4,GPIO_PIN_RESET);
				HAL_Delay(600);
				HAL_GPIO_WritePin(GPIOB,in1,GPIO_PIN_SET);			// di thang
				HAL_GPIO_WritePin(GPIOB,in2,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,in3,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,in4,GPIO_PIN_RESET);
				HAL_Delay(2000);
				HAL_GPIO_WritePin(GPIOB,in1,GPIO_PIN_RESET);				// re trai
				HAL_GPIO_WritePin(GPIOB,in2,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,in3,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,in4,GPIO_PIN_RESET);
				HAL_Delay(600);
				HAL_GPIO_WritePin(GPIOB,in1,GPIO_PIN_SET);					// di thang
				HAL_GPIO_WritePin(GPIOB,in2,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,in3,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,in4,GPIO_PIN_RESET);
				HAL_Delay(1500);
				HAL_GPIO_WritePin(GPIOB,in1,GPIO_PIN_SET);				// re phai
				HAL_GPIO_WritePin(GPIOB,in2,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,in3,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,in4,GPIO_PIN_SET);
				HAL_Delay(400);
				tam=0;
			}
			else
			{
				HAL_GPIO_WritePin(GPIOB,in1,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,in2,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,in3,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,in4,GPIO_PIN_RESET);
			}
		}
		else if(tt==1)
		{
			tt=2;
			HAL_GPIO_WritePin(GPIOB,in1,GPIO_PIN_SET);				// re phai
			HAL_GPIO_WritePin(GPIOB,in2,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,in3,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,in4,GPIO_PIN_SET);
			HAL_Delay(500);
		}
		else if(tt==2)
		{
			HAL_GPIO_WritePin(GPIOB,in1,GPIO_PIN_RESET);				// re phai
			HAL_GPIO_WritePin(GPIOB,in2,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,in3,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,in4,GPIO_PIN_RESET);
		}
	}
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 24-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 72-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 PB14 PB3
                           PB4 PB5 PB6 PB7
                           PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA11 PA12 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
