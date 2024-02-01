/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ssd1306.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void tetrisInit();
void tetrisBordureDecor(SSD1306_COLOR);
void tetrisStartMenu(SSD1306_COLOR);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  tetrisInit();
  drawL(10, 50);
  drawL(20, 30);
  drawL(50, 10);
  ssd1306_UpdateScreen();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void tetrisInit(){
  ssd1306_Init();
  ssd1306_DrawRectangle(0, 0, 127, 63, White);  //ext border
  ssd1306_DrawRectangle(1, 1, 126, 62, White);  //interior
  ssd1306_UpdateScreen();   //!! Could Blink ?

  //FACULTATIF DECORS
  tetrisStartMenu(White);
  
  //ecrire le nom du jeu en GROS
  //initialiser le reste
}

void tetrisBordureDecor(SSD1306_COLOR color)
{
  //BORD DROIT HAUT
  ssd1306_DrawPixel(2, 3, color);
  ssd1306_DrawPixel(3, 2, color);
  ssd1306_DrawPixel(4, 3, color);
  ssd1306_DrawPixel(3, 4, color);
  ssd1306_DrawPixel(5, 5, color);

  ssd1306_DrawPixel(5, 2, color);
  ssd1306_DrawPixel(6, 2, color);
  ssd1306_DrawPixel(7, 2, color);

  ssd1306_DrawPixel(2, 5, color);
  ssd1306_DrawPixel(2, 6, color);
  ssd1306_DrawPixel(2, 7, color);

  //BORD GAUCHE HAUT
  ssd1306_DrawPixel(2, 60, color);
  ssd1306_DrawPixel(3, 61, color);
  ssd1306_DrawPixel(2, 59, color);
  ssd1306_DrawPixel(4, 60, color);
  ssd1306_DrawPixel(5, 58, color);

  ssd1306_DrawPixel(2, 56, color);
  ssd1306_DrawPixel(2, 57, color);
  ssd1306_DrawPixel(2, 58, color);

  ssd1306_DrawPixel(5, 61, color);
  ssd1306_DrawPixel(6, 61, color);
  ssd1306_DrawPixel(7, 61, color);

  //BORD DROIT BAS
  ssd1306_DrawPixel(124, 3, color);
  ssd1306_DrawPixel(126, 3, color);
  ssd1306_DrawPixel(125, 3, color);
  ssd1306_DrawPixel(125, 4, color);
  ssd1306_DrawPixel(123, 5, color);

  ssd1306_DrawPixel(121, 2, color);
  ssd1306_DrawPixel(122, 2, color);
  ssd1306_DrawPixel(123, 2, color);

  ssd1306_DrawPixel(126, 5, color);
  ssd1306_DrawPixel(126, 6, color);
  ssd1306_DrawPixel(126, 7, color);

  //BORD GAUCHE BAS		//A REFAIRE RIEN n'est BON
  ssd1306_DrawPixel(126, 62, color);
  ssd1306_DrawPixel(125, 61, color);
  ssd1306_DrawPixel(124, 61, color);
  ssd1306_DrawPixel(123, 60, color);
  ssd1306_DrawPixel(122, 59, color);

  ssd1306_DrawPixel(121, 57, color);
  ssd1306_DrawPixel(122, 58, color);
  ssd1306_DrawPixel(123, 59, color);

  ssd1306_DrawPixel(126, 62, color);
  ssd1306_DrawPixel(126, 62, color);
  ssd1306_DrawPixel(126, 62, color);
  HAL_Delay(100);
}

void tetrisStartMenu(SSD1306_COLOR color){
//  tetrisBordureDecor(color);
//  ssd1306_UpdateScreen();
  //afficher "Tetris The GAME"
  //afficher flèche click
  //afficher "Click to Start"
  //afficher les tetriminos
}

//functions to draw pieces
void drawL(uint8_t x, uint8_t y) { 
	// ssd1306_FillRectangle(x, y, x+17, y+5, White); 
	// ssd1306_FillRectangle(x+12, y+6, x+17, y+11, White); //left L but work
  ssd1306_FillRectangle(x, y+6, x+17, y+11, White); 
	ssd1306_FillRectangle(x+12, y+11, x+17, y+17, White); 
} 

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
