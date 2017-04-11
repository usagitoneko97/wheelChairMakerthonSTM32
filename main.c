/**
  ******************************************************************************
  * @file    main.c
  * @author  MMY Application Team
  * @version $Revision: 1633 $
  * @date    $Date: 2016-02-10 16:31:14 +0100 (Wed, 10 Feb 2016) $
  * @brief   This file describe the main program.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under ST MYLIBERTY SOFTWARE LICENSE AGREEMENT (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/myliberty
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied,
  * AND SPECIFICALLY DISCLAIMING THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l0xx_hal.h"
#include "x_nucleo_nfc02a1.h"
/** @addtogroup X_NUCLEO_NFC02A1_Applications
  * @{
  */

/** @addtogroup WriteURI_Application
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/
sURI_Info URI;
SPI_HandleTypeDef hspi1;
uint8_t data;
uint8_t password[2];
uint8_t NDEF_BUFFER1[NDEF_MAX_SIZE];
uint8_t Buffer_bin[NDEF_MAX_SIZE];
uint8_t check[NDEF_MAX_SIZE],i,n;
uint8_t test;
uint8_t ssid[12];
uint8_t wifipassword[8];
uint8_t ANDROID_CONFIRMATION[NDEF_MAX_SIZE];
/* I2C handler declaration */
I2C_HandleTypeDef hNFC02A1_i2c;

extern sCCFileInfo CCFileStruct;

/* Private function prototypes -----------------------------------------------*/
extern void SystemClock_Config( void );
	char SSID1[] ="Q9jv8Tx01mlZ";
  char SSID2[] ="1pb7YH30AcXI";
  char SSID3[] ="8uYXn27OqsG7";
  char SSID4[] ="1Wdv&yGo0LeU";
  char SSID5[] ="t8U4vnJFa50Q";
  char SSID6[] ="Ec91Q0Vb317I";
  char SSID7[] ="0UZP3eh6aY2j";
  char SSID8[] ="s82UhEN51Wha";
  char SSID9[] ="4Opa3rg45nf2";
  char SSID10[]="2i97g0HIb86v";

  char PASS1[] ="6FV0bu9V";
  char PASS2[] ="76dc09hu";
  char PASS3[] ="V68f56T0";
  char PASS4[] ="9UjoG5d2";
  char PASS5[] ="seRCrte4";
  char PASS6[] ="wTCVih0R";
  char PASS7[] ="7G7YcHYc";
  char PASS8[] ="4SWsxc9I";
  char PASS9[] ="n9kojbT5";
  char PASS10[]="FVuv86F4";

void Enable_EnergyHarvesting( void );
static void MX_SPI1_Init(void);
static void MX_GPIO_Init(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @retval None
  */
int main( void )
{
  /* STM32L0xx HAL library initialization:
       - Configure the Flash prefetch, Flash preread and Buffer caches
       - Systick timer is configured by default as source of time base, but user
             can eventually implement his proper time base source (a general purpose
             timer for example or other time source), keeping in mind that Time base
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
             handled in milliseconds basis.
       - Low Level Initialization
     */

  /******************************************************************************/
  /* Initialisation of Main STM32 board and X-NUCLEO-NFC02A1 board              */
  /******************************************************************************/
  /* Reset of all peripherals, Initializes the Flash interface and the systick. */
  HAL_Init();

   MX_GPIO_Init();
  MX_SPI1_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Init of the Nucleo Board led */
//  BSP_LED_Init(LED2);

  /******************************************************************************/
  /* Configuration of X-NUCLEO-NFC02A1                                          */
  /******************************************************************************/
  /* Init of the Leds on X-NUCLEO-NFC02A1 board */
  NFC02A1_LED_Init( );
  NFC02A1_LED_ON( GREEN_LED );
  wait_ms( 500 );
  NFC02A1_LED_ON( BLUE_LED );
  wait_ms( 500 );
  NFC02A1_LED_ON( ORANGE_LED );
  wait_ms( 500 );
  NFC02A1_LED_OFF( GREEN_LED );
  wait_ms( 500 );
  NFC02A1_LED_OFF( BLUE_LED );
  wait_ms( 500 );
  NFC02A1_LED_OFF( ORANGE_LED );

  /* Init M24LR driver */
  while( BSP_NFCTAG_Init( ) != NFCTAG_OK );

  /* Enable Energy Harvesting */
  Enable_EnergyHarvesting( );

  /* Check if no NDEF detected, init mem in Tag Type 5 */
  if( NfcType5_NDEFDetection( ) != NDEF_OK )
  {
    CCFileStruct.MagicNumber = NFCT5_MAGICNUMBER_E1_CCFILE;
    CCFileStruct.Version = NFCT5_VERSION_V1_0;
    CCFileStruct.MemorySize = ( M24LR_MAX_SIZE / 8 ) & 0xFF;
    CCFileStruct.TT5Tag = 0x05;
    /* Init of the Type Tag 5 component (M24LR) */
    while( NfcType5_TT5Init( ) != NFCTAG_OK );
  }

  /* Set the LED2 on to indicate Init done */
  //NFC02A1_LED_ON( BLUE_LED );

  /* Prepare URI NDEF message content */
  strcpy( URI.protocol,URI_ID_0x01_STRING );
  strcpy( URI.URI_Message,"st.com/st25" );
  strcpy( URI.Information,"\0" );

  /* Write NDEF to EEPROM */
  //while( NDEF_WriteURI( &URI ) != NDEF_OK );

  /* Set the LED3 on to indicate Programing done */


  while(BSP_NFCTAG_WriteData((Buffer_bin), (0), 17)!=NDEF_OK);

  /*default password*/
     password[0] = 0x12;
     password[1] = 0x34;
     i=0;
     ANDROID_CONFIRMATION[0] = 0x01;
     check[8] = 0x01;
     check[9] = 0x02;
     check[10] = 0x00;
     while( 1 )
     {
    	 /*read the android flag and the password*/
    	 BSP_NFCTAG_ReadData(NDEF_BUFFER1, 0, 4);
    	 if(NDEF_BUFFER1[0] == 0x01){

   		  //read password complete, check password
   		  if((NDEF_BUFFER1[1] == password[0]) && (NDEF_BUFFER1[2] == password[1]))
   		  {
   			 /*run all these when the password is correct*/

   			  /*write password correct byte*/
   			  BSP_NFCTAG_WriteData((check+8), 3, 1);
   			/*confirmation byte to send to android on done writing ssid and pw*/
   			   	BSP_NFCTAG_WriteData((check+8), (7), 1);
   			   	BSP_NFCTAG_ReadData(NDEF_BUFFER1, 0, 10);
   			  /*receive and write the ssid and password from spi*/
   			  HAL_SPI_Receive(&hspi1,&check[0],1,5000);
   			  BSP_NFCTAG_WriteData((check), (4), 1);

   				  /*reset the android command flag*/
   			  BSP_NFCTAG_WriteData((check+10), 0, 1);



   		  }
   		  else{
   			  /*password not correct*/
   			BSP_NFCTAG_WriteData((check+9), 3, 1);
   			/*reset the android command flag*/
   			BSP_NFCTAG_WriteData((check+10), 0, 1);
   			/*confirmation byte to send to android on done writing ssid and pw*/
   			BSP_NFCTAG_WriteData((check+8), (7), 1);

   			NFC02A1_LED_ON( GREEN_LED );

   		  }
   		  HAL_Delay(100);
     }
    	 else{
    		 /*not yet receive command from android*/

    	 }
    	 HAL_Delay(100);
     }
}




/******************************************************************************/
/* PRIVATE FUNCTION                                                           */
/******************************************************************************/

/**
  * @brief  This function activate Energy Harvesting mode
  */
void Enable_EnergyHarvesting( void )
{
  /* Initialise M24LR Board */
  if( BSP_NFCTAG_GetExtended_Drv() != NULL )
  {
    /* Enable Energy Harvesting */
    BSP_NFCTAG_GetExtended_Drv()->SetEH( );

    /* Store configuration in non Volatile Memory */
    BSP_NFCTAG_GetExtended_Drv()->Enable_EH_mode();
    BSP_NFCTAG_GetExtended_Drv()->WriteEH_Cfg( M24LR_EH_Cfg_6MA );
  }
}

/*void changeToSSID_PASS(uint8_t *check, uint8_t *ssid[12], uint8_t wifipassword[8]){
	switch(check)
	  {
	    case '0':
	      strcpy(ssid,SSID1);
	      strcpy(password,PASS1);
	      break;
	    case '1':
	     strcpy(ssid,SSID2);
	      strcpy(password,PASS2);
	      break;
	    case '2':
	      strcpy(ssid,SSID3);
	      strcpy(password,PASS3);
	      break;
	    case '3':
	      strcpy(ssid,SSID4);
	      strcpy(password,PASS4);
	      break;
	    case '4':
	      strcpy(ssid,SSID5);
	      strcpy(password,PASS5);
	      break;
	    case '5':
	      strcpy(ssid,SSID6);
	      strcpy(password,PASS6);
	      break;
	    case '6':
	      strcpy(ssid,SSID7);
	      strcpy(password,PASS7);
	      break;
	    case '7':
	      strcpy(ssid,SSID8);
	      strcpy(password,PASS8);
	      break;
	    case '8':
	      strcpy(ssid,SSID9);
	      strcpy(password,PASS9);
	      break;
	    case '9':
	      strcpy(ssid,SSID10);
	      strcpy(password,PASS10);
	      break;
	  }
}*/

static void MX_SPI1_Init(void)
{

	 hspi1.Instance = SPI1;
	 hspi1.Init.Mode = SPI_MODE_SLAVE;
	  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	  hspi1.Init.NSS = SPI_NSS_SOFT;
	  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	  hspi1.Init.CRCPolynomial = 7;
	  if (HAL_SPI_Init(&hspi1) != HAL_OK)
	  {
	    Error_Handler();
	  }


}
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();


  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi){
	NFC02A1_LED_ON( ORANGE_LED );
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  */
void assert_failed( uint8_t* file, uint32_t line )
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while( 1 )
  {
  }
}
#endif

/*UNUSED CODE*/
/*switch(check[0])
    		 	  	  {
   				  	case 0x30:
    		 	      strcpy(ssid,SSID1);
    		 	      strcpy(wifipassword,PASS1);
    		 	      break;
    		 	    case 0x31:
    		 	     strcpy(ssid,SSID2);
    		 	      strcpy(wifipassword,PASS2);
    		 	      break;
    		 	    case 0x32:
    		 	      strcpy(ssid,SSID3);
    		 	      strcpy(wifipassword,PASS3);
    		 	      break;
    		 	    case 0x33:
    		 	      strcpy(ssid,SSID4);
    		 	      strcpy(wifipassword,PASS4);
    		 	      break;
    		 	    case 0x34:
    		 	      strcpy(ssid,SSID5);
    		 	      strcpy(wifipassword,PASS5);
    		 	      break;
    		 	    case 0x35:
    		 	      strcpy(ssid,SSID6);
    		 	      strcpy(wifipassword,PASS6);
    		 	      break;
    		 	    case 0x36:
    		 	      strcpy(ssid,SSID7);
    		 	      strcpy(wifipassword,PASS7);
    		 	      break;
    		 	    case 0x37:
    		 	      strcpy(ssid,SSID8);
    		 	      strcpy(wifipassword,PASS8);
    		 	      break;
    		 	    case 0x38:
    		 	      strcpy(ssid,SSID9);
    		 	      strcpy(wifipassword,PASS9);
    		 	      break;
    		 	    case 0x39:
    		 	      strcpy(ssid,SSID10);
    		 	      strcpy(wifipassword,PASS10);
    		 	      break;
    		 	  }*/
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
