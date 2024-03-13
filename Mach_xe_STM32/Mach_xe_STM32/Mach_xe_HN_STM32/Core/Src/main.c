#include "main.h"
#include "lcd1602_4bit.h"
#include "stdio.h"

TIM_HandleTypeDef htim1;


void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);

#define in1 GPIO_PIN_7
#define in2 GPIO_PIN_6
#define in3 GPIO_PIN_4
#define in4 GPIO_PIN_5

#define hn	GPIO_PIN_8

long		xungp,tt,tam,qdp;
long		xungt,tamt,qdt;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin==GPIO_PIN_10)
	{
		if(tam==0)
		{
			if(tt==0)
			{
				xungt++;
				qdt=xungt*200/4112;				// 4780
			}
		}
	}
	
	if(GPIO_Pin==GPIO_PIN_11)
	{
		if(tam==0)
		{
			if(tt==0)
			{
				xungp++;
				qdp=xungp*200/4112;				// 4780
			}
		}
	}
}

int main(void)
{
  
  HAL_Init();

  
  SystemClock_Config();

  
  MX_GPIO_Init();
  MX_TIM1_Init();
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	
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
		if((xungt>2300)||(xungp>2300))			//2m
		{
			tt=1;
			xungt=0;
			xungp=0;
		}
		
		Lcd_gotoxy(0,0);
		Lcd_write_string("TRAI:");
		Lcd_write_char(xungt/1000%10+0x30);
		Lcd_write_char(xungt/100%10+0x30);
		Lcd_write_char(xungt/10%10+0x30);
		Lcd_write_char(xungt%10+0x30);
		Lcd_write_string("xung     ");
		
		Lcd_gotoxy(0,1);
		Lcd_write_string("PHAI:");
		Lcd_write_char(xungp/1000%10+0x30);
		Lcd_write_char(xungp/100%10+0x30);
		Lcd_write_char(xungp/10%10+0x30);
		Lcd_write_char(xungp%10+0x30);
		Lcd_write_string("xung     ");
		
		if(tt==0)
		{
			if(HAL_GPIO_ReadPin(GPIOB,hn)==0)
			{
				tam=1;
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, 99);
				HAL_Delay(300);
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, 80);
				HAL_Delay(300);
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, 60);
				HAL_Delay(300);
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, 40);
				HAL_Delay(300);
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, 30);
				HAL_Delay(300);
				//__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, 90);
				HAL_GPIO_WritePin(GPIOB,in1,GPIO_PIN_SET);				// re phai
				HAL_GPIO_WritePin(GPIOB,in2,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,in3,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,in4,GPIO_PIN_SET);
				HAL_Delay(1000);
				HAL_GPIO_WritePin(GPIOB,in1,GPIO_PIN_SET);				// di thang
				HAL_GPIO_WritePin(GPIOB,in2,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,in3,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,in4,GPIO_PIN_RESET);
				HAL_Delay(4000);
				HAL_GPIO_WritePin(GPIOB,in1,GPIO_PIN_RESET);		// re trai
				HAL_GPIO_WritePin(GPIOB,in2,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,in3,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,in4,GPIO_PIN_RESET);
				HAL_Delay(1000);
				HAL_GPIO_WritePin(GPIOB,in1,GPIO_PIN_SET);			// di thang
				HAL_GPIO_WritePin(GPIOB,in2,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,in3,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,in4,GPIO_PIN_RESET);
				HAL_Delay(4000);
				HAL_GPIO_WritePin(GPIOB,in1,GPIO_PIN_RESET);				// re trai
				HAL_GPIO_WritePin(GPIOB,in2,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,in3,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,in4,GPIO_PIN_RESET);
				HAL_Delay(1000);
				HAL_GPIO_WritePin(GPIOB,in1,GPIO_PIN_SET);					// di thang
				HAL_GPIO_WritePin(GPIOB,in2,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,in3,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,in4,GPIO_PIN_RESET);
				HAL_Delay(1500);
				HAL_GPIO_WritePin(GPIOB,in1,GPIO_PIN_SET);				// re phai
				HAL_GPIO_WritePin(GPIOB,in2,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,in3,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,in4,GPIO_PIN_SET);
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, 99);
				HAL_Delay(400);
				tam=0;
			}
			else
			{
				HAL_GPIO_WritePin(GPIOB,in1,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,in2,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,in3,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,in4,GPIO_PIN_RESET);
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, 99);
			}
		}
		else if(tt==1)
		{
			tt=2;
			HAL_GPIO_WritePin(GPIOB,in1,GPIO_PIN_SET);				// re phai
			HAL_GPIO_WritePin(GPIOB,in2,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,in3,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,in4,GPIO_PIN_SET);
			__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, 99);
			HAL_Delay(500);
		}
		else if(tt==2)
		{
			HAL_GPIO_WritePin(GPIOB,in1,GPIO_PIN_RESET);				// re phai
			HAL_GPIO_WritePin(GPIOB,in2,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,in3,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,in4,GPIO_PIN_RESET);
			__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, 99);
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 800;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 99;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 25;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

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
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB10 PB11 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 PB14 PB15
                           PB3 PB4 PB5 PB6
                           PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7;
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

  /*Configure GPIO pins : PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
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
