#include <string.h>
#include "los_sys.h"
#include "los_tick.h"
#include "los_task.ph"
#include "los_config.h"

#include "los_bsp_led.h"
#include "los_bsp_key.h"
#include "los_bsp_uart.h"
#include "los_bsp_adapter.h"
#include "los_bsp_flash.h" 
#include "los_demo_entry.h"

#include "ff.h"


/* Private value-----------------------------------------------*/
FIL fnew;													/* file objects */
FATFS fs;													/* Work area (file system object) for logical drives */
FRESULT res_flash; 
UINT br, bw;            					/* File R/W count */
BYTE buffer[1024]={0};       		  /* file copy buffer */
BYTE textFileBuffer[] = "LiteOS FatFS文件系统测试";

static UINT32 g_uwboadTaskID;

/* Private function prototypes -----------------------------------------------*/
//static void SystemClock_Config(void);
static void Delay(uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}


LITE_OS_SEC_TEXT VOID LOS_BoadExampleTskfunc(VOID)
{
	/*************************   flash 文件系统   *********************************************/
	//挂载文件系统
	res_flash = f_mount(&fs,"1:",1);
	LOS_EvbUartPrintf("\r\n f_mount res_flash = [%d] \r\n",res_flash);
	
	//如果没有文件系统就格式化创建创建文件系统
	if(res_flash == FR_NO_FILESYSTEM)
	{
		res_flash=f_mkfs("1:",0,0);							    //格式化
		LOS_EvbUartPrintf("\r\n f_mkfs res_flash=%d",res_flash);
		res_flash = f_mount(&fs,"1:",0);						//格式化后，先取消挂载
		res_flash = f_mount(&fs,"1:",1);						//重新挂载
		LOS_EvbUartPrintf("\r\n remount res_flash = [%d] \r\n",res_flash);
	}
	
	//文件系统测试，写测试,打开文件，如果文件不存在则创建它
	res_flash = f_open(&fnew, "1:LiteOS.txt", FA_CREATE_ALWAYS | FA_WRITE );
	if ( res_flash == FR_OK )
	{
		LOS_EvbUartPrintf("\r\nWrite = [%s] ", textFileBuffer);
		res_flash = f_write(&fnew, textFileBuffer, sizeof(textFileBuffer), &bw);
		if(FR_OK != res_flash)
		{
			LOS_EvbUartPrintf("\r\f_write failed.");
			LOS_EvbLedControl(LOS_LED2, LED_ON);
		}	
		LOS_EvbUartPrintf("\r\nbw = [%d] ", bw);
		f_close(&fnew);      
	}
	else
	{
		LOS_EvbUartPrintf("\r\ncreate file failed.");
		LOS_EvbLedControl(LOS_LED2, LED_ON);
	}

	//读测试
	res_flash = f_open(&fnew, "1:LiteOS.txt", FA_OPEN_EXISTING | FA_READ); 
  if(FR_OK != res_flash)
	{
	  LOS_EvbUartPrintf("\r\f_open failed.");
		LOS_EvbLedControl(LOS_LED2, LED_ON);
	}	
	
	res_flash = f_read(&fnew, buffer, sizeof(buffer), &br); 
	if(FR_OK != res_flash)
	{
	  LOS_EvbUartPrintf("\r\f_read failed.");
		LOS_EvbLedControl(LOS_LED2, LED_ON);
	}	
	else
	{
		LOS_EvbLedControl(LOS_LED1, LED_ON);
		LOS_EvbUartPrintf("\r\nRead sucess buffer = [%s] ", buffer);
		LOS_EvbUartPrintf("\r\nbr = [%d] ", br);
	}
	
	/* Close open files */
	res_flash = f_close(&fnew);	
	
	//不再使用文件系统，取消挂载文件系统
	res_flash = f_mount(&fs,"1:",0);
	while(1)
	{
		LOS_EvbLedControl(LOS_LED3, LED_ON);
		Delay(0xffffff);
		LOS_EvbLedControl(LOS_LED3, LED_OFF);
		Delay(0xffffff);
	}
}


void LOS_BoadExampleEntry(void)
{
    UINT32 uwRet;
    TSK_INIT_PARAM_S stTaskInitParam;

    (VOID)memset((void *)(&stTaskInitParam), 0, sizeof(TSK_INIT_PARAM_S));
    stTaskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)LOS_BoadExampleTskfunc;
    stTaskInitParam.uwStackSize = LOSCFG_BASE_CORE_TSK_IDLE_STACK_SIZE;//4096
    stTaskInitParam.pcName = "BoardDemo";
    stTaskInitParam.usTaskPrio = 30;
    uwRet = LOS_TaskCreate(&g_uwboadTaskID, &stTaskInitParam);

    if (uwRet != LOS_OK)
    {
        return ;
    }
    return ;
}

/*****************************************************************************
 Function    : main
 Description : Main function entry
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT
int main(void)
{
    UINT32 uwRet;
    /*
			add you hardware init code here
			for example flash, i2c , system clock ....
    */
	  //HAL_Init();
	  //SystemClock_Config();

		/*Init LiteOS kernel */
    uwRet = LOS_KernelInit();
    if (uwRet != LOS_OK) {
        return LOS_NOK;
    }
		/* Enable LiteOS system tick interrupt */
    LOS_EnableTick();
		
		
    /* 
        Notice: add your code here
        here you can create task for your function 
        do some hw init that need after systemtick init
    */
    LOS_EvbSetup();
		
		//LOS_Demo_Entry();
    
		LOS_BoadExampleEntry();
		
    /* Kernel start to run */
    LOS_Start();
    for (;;);
    /* Replace the dots (...) with your own code.  */
}


/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
#if 0
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Activate the Over-Drive mode */
  HAL_PWREx_EnableOverDrive();
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}
#endif






