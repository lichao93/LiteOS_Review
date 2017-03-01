## 1关于本文档的开源协议说明
**您可以自由地：**

**分享** 

- 在任何媒介以任何形式复制、发行本文档

**演绎** 

- 修改、转换或以本文档为基础进行创作。只要你遵守许可协议条款，许可人就无法收回你的这些权利。

**惟须遵守下列条件：**

**署名** 

- 您必须提供适当的证书，提供一个链接到许可证，并指示是否作出更改。您可以以任何合理的方式这样做，但不是以任何方式表明，许可方赞同您或您的使用。

**非商业性使用** 

- 您不得将本作品用于商业目的。

**相同方式共享** 

- 如果您的修改、转换，或以本文档为基础进行创作，仅得依本素材的
授权条款来散布您的贡献作品。

**没有附加限制** 

- 您不能增设法律条款或科技措施，来限制别人依授权条款本已许可的作为。

**声明：**

-  当您使用本素材中属于公众领域的元素，或当法律有例外或限制条款允许您的使用，
则您不需要遵守本授权条款。
未提供保证。本授权条款未必能完全提供您预期用途所需要的所有许可。例如：形象
权、隐私权、著作人格权等其他权利，可能限制您如何使用本素材。

**注意**

- 为了方便用户理解，这是协议的概述. 可以访问网址 https://creativecommons.org/licenses/by-sa/3.0/legalcode 了解完整协议内容.

## 2前言
### 目的
本文档介绍基于Huawei LiteOS如何移植到第三方开发板，并成功运行基础示例。
### 读者对象
本文档主要适用于Huawei LiteOS Kernel的开发者。
本文档主要适用于以下对象：
- 物联网端软件开发工程师
- 物联网架构设计师

### 符号约定
在本文中可能出现下列标志，它们所代表的含义如下。


![](./meta/keil/danger.png)     用于警示紧急的危险情形，若不避免，将会导致人员死亡或严重的人身伤害

![](./meta/keil/warning.png)    用于警示潜在的危险情形，若不避免，可能会导致人员死亡或严重的人身伤害

![](./meta/keil/careful.png)    用于警示潜在的危险情形，若不避免，可能会导致中度或轻微的人身伤害

![](./meta/keil/notice.png)     用于传递设备或环境安全警示信息，若不避免，可能会导致设备损坏、数据丢失、设备性能降低或其它不可预知的结果“注意”不涉及人身伤害

| 说明	|		“说明”不是安全警示信息，不涉及人身、设备及环境伤害信息	|

### 修订记录
修改记录累积了每次文档更新的说明。最新版本的文档包含以前所有文档版本的更新
内容。

<table>
	<tr>
	<td>日期</td>
	<td>修订版本</td>
	<td>描述</td>
	</tr>
	<tr>
	<td>2017年2月28日</td>
	<td>1.0</td>
	<td>完成初稿</td>
	</tr>
</table>

## 3概述

目前在github上已开源的Huawei LiteOS内核源码已适配好STM32F412、STM32F429、STM32L476、GD32F450、GD32F190芯片，本手册将以STM32F429ZI芯片为例，介绍FatFS的移植过程。

## 4环境准备
基于Huawei LiteOS Kernel开发前，我们首先需要准备好单板运行的环境，包括软件环
境和硬件环境。
硬件环境：

<table>
	<tr>
	<td>所需硬件</td>
	<td>描述</td>
	</tr>
	<tr>
	<td>STM32F4291-DISCO单板</td>
	<td>STM32开发板(芯片型号STM32F429ZIT6)</td>
	</tr>
	<tr>
	<td>PC机</td>
	<td>用于编译、加载并调试镜像</td>
	</tr>
	<tr>
	<td>电源（5v）</td>
	<td>开发板供电(使用Mini USB连接线)</td>
	</tr>
</table>


软件环境：

<table>
	<tr>
	<td>软件</td>
	<td>描述</td>
	</tr>
	<tr>
	<td>Window 7 操作系统</td>
	<td>安装Keil和st-link的操作系统</td>
	</tr>
	<tr>
	<td>Keil(5.21以上版本)</td>
	<td>用于编译、链接、调试程序代码
	uVision V5.21.1.0 MDK-Lite uVersion:5.21a</td>
	</tr>
	<tr>
	<td>st-link_v2_usbdriver</td>
	<td>开发板与pc连接的驱动程序，用户加载及调试程序代码</td>
	</tr>
</table>

**说明**

Keil工具需要开发者自行购买，ST-Link的驱动程序可以从st link的相关网站获取，采用J-Link还
是ST-Link需要根据具体使用的开发板来确定。这里以STM32F429为例，使用ST-Link。


## 5获取Huawei LiteOS 及 FatFs 源码

###step1:获取Huawei LiteOS源码，方法如下：

- 仓库地址是https://github.com/LITEOS/LiteOS_Kernel.git 
![](./meta/keil/git_down.png)

- 点击”clone or download”按钮,下载源代码


- 目录结构如下：
![](./meta/keil/catal.png)

###step2:下载FatFs源码：
网址：http://elm-chan.org/fsw/ff/00index_e.html

![](./meta/keil/stm32f429/FatFs/download_src.png)

目录结构如下：

![](./meta/keil/stm32f429/FatFs/fatfs_contents.png)

###step3:下载stm32cubef4开发包：
网址：http://www.st.com/content/st_com/en/products/embedded-software/mcus-embedded-software/stm32-embedded-software/stm32cube-embedded-software/stm32cubef4.html

点击“Get Software”按钮下载：

![](./meta/keil/stm32f429/FatFs/get_soft.png)

解压后目录结构如下：

![](./meta/keil/stm32f429/FatFs/stm32_contents.png)

获取相关源代码之后，我们可以开始移植工作了，由于STM32F4291-DISCO单板没有外挂的flash设备，我们将使用MCU内部flash进行文件系统操作，使用其他外部falsh操作时与此类似。

## 6如移植FatFS
本章节描述的内容以stm32cubef4开发包中的flash驱动代码为基础，移植FatFs到LiteOS的STM32F429I_DISCO_KEIL工程中，演示基于使用MCU内部flash进行fatfs移植的过程。

### 添加需要的代码到LiteOS工程中

- STM32F429的源代码工程包含Drivers、应用适配程序以及startup_stm32f429xx.s汇编启动文件。

![](./meta/keil/stm32f429/FatFs/src1.png)

![](./meta/keil/stm32f429/FatFs/src2.png)

![](./meta/keil/stm32f429/FatFs/src3.png)


- 在LiteOS顶级目录下创建STM32FXX目录，然后将Drivers目录拷贝到下面

![](./meta/keil/stm32f429/FatFs/src4.png)

- 创建STM32FXX\stm32f429目录，将inc和src拷贝到下面，并且将startup_stm32f429xx.s也拷贝到stm32f429目录中。

![](./meta/keil/stm32f429/FatFs/src5.png)

- 创建/thirdparty/FatFs目录拷贝FatFs源码到该目录下

![](./meta/keil/stm32f429/FatFs/src6.png)

-在\platform\STM32F429I_DISCO目录下新建los_bsp_flash.c和los_bsp_flash.h文件

![](./meta/keil/stm32f429/FatFs/src7.png)

- 在LiteOS工程中新建stm32f4xx及fatfs目录，并添如下代码

![](./meta/keil/stm32f429//FatFs/src8.png)

- 替换startup目录下的启动文件，在platform/stm32f429i目录下添加los_bsp_flsh.c文件

![](./meta/keil/stm32f429//FatFs/src9.png)

**注意**
LiteOS的默认startup汇编文件中只实现了使LiteOS内核正常运行的最小功能。

### 在los_bsp_flash.c文件中适配FatFs接口

为了时文件系统能正常工作，我们要适配FatFs文件系统的相关接口，可参考http://elm-chan.org/fsw/ff/00index_e.html网页上的相关说明进行适配.

![](./meta/keil/stm32f429//FatFs/FatFs_adapter.png)

- 适配disk_initialize接口，初始化设备
   
		 DRESULT disk_ioctl (
			BYTE pdrv,		/* Physical drive nmuber (0..) */
			BYTE cmd,		/* Control code */
			void *buff		/* Buffer to send/receive control data */
		 )
		{
			DRESULT status = RES_PARERR;
			switch (pdrv) {
				case SPI_FLASH:
							#if	FATFS_FLASH_SPI ==1
							status = TM_FATFS_FLASH_disk_ioctl(cmd, buff);
							#endif
				break;
				default:
					status = RES_PARERR;
			}
			return status;
		}

		DSTATUS TM_FATFS_FLASH_disk_initialize(void)
		{
			return RES_OK;//由于是芯片内部flash，直接返回OK，如果是其他外设可进行相应初始化	
		}

- 适配DSTATUS disk_status接口，获取设备状态

	    DSTATUS disk_status (
			BYTE pdrv		/* Physical drive nmuber (0..) */
			)
			{
			DSTATUS status = STA_NOINIT;
			
			switch (pdrv) {
				case SPI_FLASH:
					#if	FATFS_FLASH_SPI ==1
					status = TM_FATFS_FLASH_disk_status();
					#endif
					break;
		
				default:
					status = STA_NOINIT;
			}
			
			return status;
		}

      	DSTATUS TM_FATFS_FLASH_disk_status(void)
		{
			return RES_OK;//芯片内部flash，直接返回OK，其他外设可以通过获取设备ID来验证	
		}

- 适配disk_read接口，读取扇区数据

		DRESULT disk_read (
			BYTE pdrv,		/* Physical drive nmuber (0..) */
			BYTE *buff,		/* Data buffer to store read data */
			DWORD sector,	/* Sector address (LBA) */
			UINT count		/* Number of sectors to read (1..128) */
		)
		{
			DRESULT status = RES_PARERR;
			switch (pdrv) {
				case SPI_FLASH:
							#if	FATFS_FLASH_SPI ==1
							status = TM_FATFS_FLASH_disk_read(buff, sector, count);	
							#endif
				break;
				default:
					status = RES_PARERR;
			}
			
			return status;
		}

		/*******************************************************************************
		* Function Name  : TM_FATFS_FLASH_disk_read
		* Description    : Read sector(s)
		* Input          : DWORD sector
		                   UINT count
		* Output         : BYTE *buff
		* Return         : RES_OK/RES_ERROR
		*******************************************************************************/
		DRESULT TM_FATFS_FLASH_disk_read(BYTE *buff, DWORD sector, UINT count)
		{
			u32 result;
		  
		  if (!count)return RES_PARERR;
		  
		  result = Flash_ReadPage(buff, sector, count);
		
		  if(result == STM_FLASH_SUCCESS)
				return RES_OK;
		  else 
				return RES_ERROR;
		}
        
		/******************************************************************************
		* Function Name  : Flash_ReadPage
		* Description    : This routine is for sequential read from one or several
		* Input          : - PageNum£ºform which Page to read
		                   - NumPageToRead£ºread Page num 
		* Output         : - pBuffer: pointer on the Buffer to fill
		* Return         : New status of the NAND operation. This parameter can be:
		*******************************************************************************/
		u32 Flash_ReadPage(u8 *pBuffer, u32 PageNum, u32 NumPageToRead)
		{
		  u32 STMFlashStatus = STM_FLASH_SUCCESS;
		  u32 Address;
		  u32 index, data;
			u8 tmpdata = 0x00;
		  
		  /* Unlock the Flash Program Erase controller */
		  HAL_FLASH_Unlock();
		  /* Clear All pending flags */
		  FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
		  
		  while( (NumPageToRead != 0x00) && (STMFlashStatus != STM_FLASH_INVALID_ADDRESS) )
		  {
		    Address = FLASH_USER_START_ADDR + PageNum*STM_FLASH_SECTOR_SIZE;
		    
		    for(index=0; index < STM_FLASH_SECTOR_SIZE; index++)
		    {
		      switch(index%4)
		      {
						case 0:
							data = *(u32*)Address;
							Address += 4;
						  
							tmpdata = DATA_1st(data);
						  *pBuffer = tmpdata;
						  pBuffer++;
							break;
						case 1:
							tmpdata = DATA_2nd(data);
						  *pBuffer = tmpdata;
						  pBuffer++;
							break;
						case 2:
							tmpdata = DATA_3rd(data);
						  *pBuffer = tmpdata;
						  pBuffer++;
							break;
						case 3:
							tmpdata = DATA_4th(data);
						  *pBuffer = tmpdata;
						  pBuffer++;
							break;
						default:
							break;
					}
		    }
				
		    NumPageToRead--;
		    if(NumPageToRead != 0)
		    {
		      PageNum++;
		      
		      /* Calculate Next page Address */
		      if(PageNum >= STM_FLASH_SECTOR_TOTAL)
					STMFlashStatus = STM_FLASH_INVALID_ADDRESS;
		    }
		  }
		  
		  HAL_FLASH_Lock();
		  
		  return STMFlashStatus;
		}

- 适配disk_write接口，写扇区数据
       
	       #if _USE_WRITE
			DRESULT disk_write (
				BYTE pdrv,			/* Physical drive nmuber (0..) */
				const BYTE *buff,	/* Data to be written */
				DWORD sector,		/* Sector address (LBA) */
				UINT count			/* Number of sectors to write (1..128) */
			)
			{
				DRESULT status = RES_PARERR;
				if (!count) {
					return RES_PARERR;		/* Check parameter */
				}
			
				switch (pdrv) {
					case SPI_FLASH:
						#if	FATFS_FLASH_SPI ==1
						status = TM_FATFS_FLASH_disk_write((BYTE *)buff, sector, count);	
						#endif
						break;
					default:
						status = RES_PARERR;
				}
			
				return status;
		  }
		  #endif	  

		/*******************************************************************************
		* Function Name  : TM_FATFS_FLASH_disk_write
		* Description    : Write sector(s)
		* Input          : DWORD sector
		                   UINT count
		                   BYTE *buff
		* Output         : None
		* Return         : RES_OK/RES_ERROR
		*******************************************************************************/
		DRESULT TM_FATFS_FLASH_disk_write(BYTE *buff, DWORD sector, UINT count)
		{
		  u32 WriteBlockNum,ulRet = STM_FLASH_SUCCESS;
		  u16 IndexTmp, OffsetPage;
		  
		  if(!count)return RES_PARERR;
		  
		  //data in witch Block
		  WriteBlockNum = sector/STM_FLASH_SECTOR_COUNT;
		  //data Offset Page of current Block
		  OffsetPage = sector%STM_FLASH_SECTOR_COUNT;
		  //Copy data to backup
		  ulRet = Flash_ReadPage((u8*)(&BackUpData[0][0]), WriteBlockNum*STM_FLASH_SECTOR_COUNT, STM_FLASH_SECTOR_COUNT);
		  if(STM_FLASH_SUCCESS != ulRet)
			{
					return RES_ERROR;
			}
		  //Erase block data
		  ulRet = Flash_EraseBlock(WriteBlockNum);
		  if(STM_FLASH_SUCCESS != ulRet)
			{
					return RES_ERROR;
			}
		  // write data
		  for (IndexTmp = 0; IndexTmp < STM_FLASH_SECTOR_COUNT; IndexTmp++ )
		  {
		    if((IndexTmp>=OffsetPage)&&(IndexTmp < (OffsetPage+count)))
		    {
		      ulRet = Flash_WritePage((u8 *)buff, WriteBlockNum*STM_FLASH_SECTOR_COUNT+IndexTmp, 1);
					if(STM_FLASH_SUCCESS != ulRet)
					{
							return RES_ERROR;
					}
		      buff = (u8 *)buff + STM_FLASH_SECTOR_SIZE;
		    }
		    else
		    {
		      //write backup data to flash
		      ulRet = Flash_WritePage((u8 *)(&BackUpData[IndexTmp][0]), WriteBlockNum*STM_FLASH_SECTOR_COUNT+IndexTmp, 1);
					if(STM_FLASH_SUCCESS != ulRet)
					{
							return RES_ERROR;
					}
				}
		  }
		  return RES_OK;	
		}
				
		/******************************************************************************
		* Function Name  : Flash_WritePage
		* Description    : This routine is for writing one or several 512 Bytes Page size.
		* Input          : pBuffer£ºpointer on the Buffer to read
		                   PageNum 
		                   NumPageToWrite
		* Output         : None
		* Return         : STM_FLASH_SUCCESS¡¢STM_FLASH_ERROR
		*******************************************************************************/
		u32 Flash_WritePage(u8 *pBuffer, u32 PageNum, u32 NumPageToWrite)
		{
		  HAL_StatusTypeDef status = HAL_OK;
		  u32 STMFlashStatus = STM_FLASH_SUCCESS;
		  u32 Address;
		  u32 index, data, data32;
		  
		  /* Unlock the Flash Program Erase controller */
		  HAL_FLASH_Unlock();
		  /* Clear All pending flags */
		  FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
		  
		  while( (NumPageToWrite != 0x00) && (STMFlashStatus != STM_FLASH_INVALID_ADDRESS) )
		  {
		    Address = FLASH_USER_START_ADDR + PageNum*STM_FLASH_SECTOR_SIZE;
		    
		    for(index=0; index < STM_FLASH_SECTOR_SIZE; index++)
		    {
		      data32 = *pBuffer++;
		      
		      switch(index%4)
		      {
		      case 0:
						data  = ( data32 << 0 ) & 0x000000FF;
						break;
		      case 1:
						data += ( data32 << 8 ) & 0x0000FF00;
						break;
		      case 2:
						data += ( data32 << 16) & 0x00FF0000;
						break;
		      case 3:
						data += ( data32 << 24) & 0xFF000000;
						if(data != 0)
						{
							data = data;
						}
						status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,Address, data);
						Address += 4;
			
						if(status != HAL_OK)
						{
							HAL_FLASH_Lock();
							return STM_FLASH_ERROR;
						}
			
						break;
		      default:
						break;
		      }
		    }  
		    NumPageToWrite--;
		    if(NumPageToWrite != 0)
		    {
		      PageNum++;
		      
		      /* Calculate Next page Address */
		      if(PageNum >= STM_FLASH_SECTOR_TOTAL)
					STMFlashStatus = STM_FLASH_INVALID_ADDRESS;
		    }
		  }
		  
		  HAL_FLASH_Lock();
		  
		  return STMFlashStatus;
		}
		      
		/******************************************************************************
		* Function Name  : Flash_EraseBlock
		* Description    : Erase Block before write
		* Input          : - BlockNum£ºform which Page to read
		* Output         : None
		* Return         : STM_FLASH_ERROR/STM_FLASH_SUCCESS
		*******************************************************************************/
		u32 Flash_EraseBlock(u32 BlockNum)
		{
				/* Unlock the Flash to enable the flash control register access *************/ 
				HAL_FLASH_Unlock();
		
				/* Erase the user Flash area
					(area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/
		
				/* Get the 1st sector to erase */
				FirstSector = GetSector(FLASH_USER_START_ADDR);
		
				/* Get the number of sector to erase from 1st sector*/
				NbOfSectors = 1;
		
				/* Fill EraseInit structure*/
				EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
				EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
				EraseInitStruct.Sector = FirstSector + BlockNum;
				EraseInitStruct.NbSectors = NbOfSectors;
				if(HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError) != HAL_OK)
				{ 
					/* 
						Error occurred while sector erase. 
						User can add here some code to deal with this error. 
						SectorError will contain the faulty sector and then to know the code error on this sector,
						user can call function 'HAL_FLASH_GetError()'
					*/
					/*
						FLASH_ErrorTypeDef errorcode = HAL_FLASH_GetError();
					*/
					Error_Handler();
					return STM_FLASH_ERROR;
				}
		
				/* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
					 you have to make sure that these data are rewritten before they are accessed during code
					 execution. If this cannot be done safely, it is recommended to flush the caches by setting the
					 DCRST and ICRST bits in the FLASH_CR register. */
				__HAL_FLASH_DATA_CACHE_DISABLE();
				__HAL_FLASH_INSTRUCTION_CACHE_DISABLE();
		
				__HAL_FLASH_DATA_CACHE_RESET();
				__HAL_FLASH_INSTRUCTION_CACHE_RESET();
		
				__HAL_FLASH_INSTRUCTION_CACHE_ENABLE();
				__HAL_FLASH_DATA_CACHE_ENABLE();
				
		   return STM_FLASH_SUCCESS;
		}

- 适配disk_ioctl接口，控制设备依赖函数
     
		#if _USE_IOCTL
		DRESULT disk_ioctl (
			BYTE pdrv,		/* Physical drive nmuber (0..) */
			BYTE cmd,		/* Control code */
			void *buff		/* Buffer to send/receive control data */
		)
		{
			DRESULT status = RES_PARERR;
			switch (pdrv) {
				case SPI_FLASH:
							#if	FATFS_FLASH_SPI ==1
							status = TM_FATFS_FLASH_disk_ioctl(cmd, buff);	
							#endif
				break;
				default:
					status = RES_PARERR;
			}
			return status;
		}
		#endif
		     
		/*******************************************************************************
		* Function Name  : TM_FATFS_FLASH_disk_ioctl
		* Description    : detail disk iocotl cmd
		* Input          : cmd
		* Output         : buff
		* Return         : RES_OK/RES_ERROR
		*******************************************************************************/
		DRESULT TM_FATFS_FLASH_disk_ioctl(BYTE cmd, char *buff)
		{
			switch (cmd) 
			{
				case GET_SECTOR_SIZE :                      // Get R/W sector size (WORD)
					*(WORD * )buff = STM_FLASH_SECTOR_SIZE; // flash read/write unit
					break;
				case GET_SECTOR_COUNT:
					*(DWORD * )buff = STM_FLASH_SECTOR_TOTAL; //Get sector num
					break;
				case GET_BLOCK_SIZE :  // Get erase block size in unit of sector (DWORD)
					*(DWORD * )buff = STM_FLASH_SECTOR_COUNT;
					break;
				case CTRL_SYNC :
					break;
				default:
				 return RES_ERROR;
			}
		
			return RES_OK;
		}

- 适配get_fattime接口，获取当前时间

		   __weak DWORD get_fattime(void) {
			/* Returns current time packed into a DWORD variable */
			return	  ((DWORD)(2017 - 1980) << 25)	/* Year 2013 */
					| ((DWORD)2 << 21)				/* Month 7 */
					| ((DWORD)28 << 16)				/* Mday 28 */
					| ((DWORD)12 << 11)				/* Hour 12 */
					| ((DWORD)59 << 5)				/* Min 59 */
					| ((DWORD)59 >> 1);				/* Sec 59 */
		    }

**注意**

示例中的时间为固定值，用户可设置为RTC时钟的时间


### 在los_bsp_flash.h文件中进行相关配置
 
		#define FLASH_USER_START_ADDR   ADDR_FLASH_SECTOR_5   /* Start @ of user Flash area */
		#define FLASH_USER_END_ADDR     (ADDR_FLASH_SECTOR_11  +  GetSectorSize(ADDR_FLASH_SECTOR_11) -1) /* End @ of user Flash area : sector start address + sector size -1 */
		
		/* Flash memory address of physics */
		#define STM32_FLASH_ADDR		((u32)0x08000000)
		#define STM32_BLOCK_SIZE		((u32)0x20000)//扇区大小设置为128K
		
		/* Flash  memory parameters */
		#define STM_FLASH_SECTOR_SIZE		((u16)0x1000)	/* 4096 bytes per page w/o Spare Area */
		#define STM_FLASH_SECTOR_COUNT    ((u16)0x0020)		/* 128k = 32*4096 bytes sectors per block */
		#define STM_FLASH_SECTOR_TOTAL		((u16)((FLASH_USER_END_ADDR - FLASH_USER_START_ADDR +1)/STM_FLASH_SECTOR_SIZE))	/* (128/4)*7= 224*/

### 修改ffconf.h文件，进行文件系统配置
       
	#define _VOLUMES	2  /* Number of volumes (logical drives) to be used. */
        
	#define _CODE_PAGE	936 //支持简体中文
	
	#define	_MIN_SS		512
	#define	_MAX_SS		4096 //设置setcor大小
	   
	#define	_USE_LFN	2    //使用长文件名
	#define	_MAX_LFN	255

**注意**

   详细说明请参考ffconf.h文件中的注释

### 修改los_bsp_adapter.c文件

- 代码添加完毕之后，需要修改los_bsp_adapter.c中的system tick时钟const unsigned int sys_clk_freq = 16000000;修改为const unsigned int sys_clk_freq = 180000000; 代码给出的时默认system clock值。

		const unsigned int sys_clk_freq = 180000000;

- 增加system tick中断的处理内容适配stm32工程的运行。
![](./meta/keil/stm32f429/bsp_src7_2.png)

### 修改main.c文件

- 在main.c中添加平台初始化以及系统时钟配置的调用

![](./meta/keil/stm32f429/bsp_src7.png)

- 修改LOS_BoadExampleTskfunc函数
	
		LITE_OS_SEC_TEXT VOID LOS_BoadExampleTskfunc(VOID)
		{
			/*************************   flash文件系统  *********************************************/
			//挂载文件系统
			res_flash = f_mount(&fs,"1:",1);
			LOS_EvbUartPrintf("\r\nf_mount res_flash = [%d] \r\n",res_flash);
			
			//如果没有文件系统则创建文件系统
			if(res_flash == FR_NO_FILESYSTEM)
			{
				res_flash=f_mkfs("1:",0,0);							    //格式化
				LOS_EvbUartPrintf("\r\n f_mkfs res_flash=%d",res_flash);
				res_flash = f_mount(&fs,"1:",0);						//格式化后取消挂载
				res_flash = f_mount(&fs,"1:",1);						//重新挂载
                LOS_EvbUartPrintf("\r\n remount res_flash = [%d] \r\n",res_flash);
			}
					
			//文件系统测试，写测试，打开文件，没有则创建
			res_flash = f_open(&fnew, "1:n.txt", FA_CREATE_ALWAYS | FA_WRITE );
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
		
			//读文件测试
			res_flash = f_open(&fnew, "1:n.txt", FA_OPEN_EXISTING | FA_READ); 
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
			
			//取消挂载
			res_flash = f_mount(&fs,"1:",0);
			while(1)
			{
				LOS_EvbLedControl(LOS_LED3, LED_ON);
				Delay(0xffffff);
				LOS_EvbLedControl(LOS_LED3, LED_OFF);
				Delay(0xffffff);
			}
		}

### 修改stm32f4xx_it.c文件

- 将stm32f4xx_it.c中的SysTick_Handler、PendSV_Handler的实现删除或者if 0掉。

![](./meta/keil/stm32f429/bsp_src8.png)

### 修改stm32f4xx_hal_msp.c文件
- 将stm32f4xx_hal_msp.c中的main.h替换成los_bsp_uart.h。

		//#include "main.h"
		#include "los_bsp_uart.h"

### 添加头文件路径包含以及宏定义

- 参考STM32的原始工程，将其中的头文件搜索路径以及宏定义拷贝到LiteOS工程的设置中，并且定义宏LOS_STM32F429ZI

![](./meta/keil/stm32f429/FatFs/src10.png)

![](./meta/keil/stm32f429/bsp_src10.png)

### 编译运行

- 以上步骤完成之后，编译代码，连接串口进行调试，可以相关打印信息，如果成功,LD3绿灯点亮，否则LD4红灯点亮。

## 7 其他说明

### 内部Flash以Sector为单位时，关于扇区大小设置设置说明

  设置扇区大小时，首先要阅读芯片手册中有关falsh的说明，例如STM32F429ZI芯片内部falsh分为两个bank，每个bank分不同大小的扇区，最大的扇区为128k，最小的为16k，没有细分为page，那么数据擦除的最小单位为Sector，而FatFS中只有block和sector的概念，为了匹配，我们可以把一个sector当成一个block，把它再看做由4k大小的virtualsector组成，但是要记住，进行数据写操作时需要同时擦除的sector个数为 = (Sector size)/(virtual sector size),有了这个概念就可以与FatFS进行匹配了，示例代码中使用的是SECTOR_5到SECTOR_11。

		 /* Base address of the Flash sectors Bank 1 */
		#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
		#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
		#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
		#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
		#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
		#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
		#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
		#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
		#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
		#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
		#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
		#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */
		
		/* Base address of the Flash sectors Bank 2 */
		#define ADDR_FLASH_SECTOR_12     ((uint32_t)0x08100000) /* Base @ of Sector 0, 16 Kbytes */
		#define ADDR_FLASH_SECTOR_13     ((uint32_t)0x08104000) /* Base @ of Sector 1, 16 Kbytes */
		#define ADDR_FLASH_SECTOR_14     ((uint32_t)0x08108000) /* Base @ of Sector 2, 16 Kbytes */
		#define ADDR_FLASH_SECTOR_15     ((uint32_t)0x0810C000) /* Base @ of Sector 3, 16 Kbytes */
		#define ADDR_FLASH_SECTOR_16     ((uint32_t)0x08110000) /* Base @ of Sector 4, 64 Kbytes */
		#define ADDR_FLASH_SECTOR_17     ((uint32_t)0x08120000) /* Base @ of Sector 5, 128 Kbytes */
		#define ADDR_FLASH_SECTOR_18     ((uint32_t)0x08140000) /* Base @ of Sector 6, 128 Kbytes */
		#define ADDR_FLASH_SECTOR_19     ((uint32_t)0x08160000) /* Base @ of Sector 7, 128 Kbytes */
		#define ADDR_FLASH_SECTOR_20     ((uint32_t)0x08180000) /* Base @ of Sector 8, 128 Kbytes  */
		#define ADDR_FLASH_SECTOR_21     ((uint32_t)0x081A0000) /* Base @ of Sector 9, 128 Kbytes  */
		#define ADDR_FLASH_SECTOR_22     ((uint32_t)0x081C0000) /* Base @ of Sector 10, 128 Kbytes */
		#define ADDR_FLASH_SECTOR_23     ((uint32_t)0x081E0000) /* Base @ of Sector 11, 128 Kbytes */

### 内部Flash以page为单位时，关于扇区大小设置设置说明

  我们使用的某些芯片内部flash以page为单位，比如STM32F103ZE芯片，每个page的大小为2K，共256个，那么我们可以将每个page看做一个block，每个block看做4个sector，那么每次擦除的最小单位为4个sector，即进行一次page擦除操作；当然我们也可以设置sector大小为4k，这样每次擦除的最小单位为1个sector，即进行两次page擦除操作。

### 使用MCU 内部flash 时要在注意的问题
   
  使用MCU内部flash时，要注意不能擦除存放code的扇区，尽量使用地址靠后的扇区。

### 使用芯片外部存储设备存储
  
  使用芯片外部存储设备进行存储时，需要适配的接口与使用芯片内部flash相同，需要注意的是存储设备进行擦除操作的单位大小与sector大小设置之间的关系，当擦除操作的单位为sector大小的整数倍时，需要在擦除数据前先将这些数据进行保存，以便修改其中一个sector的数据后将其他sector的数据写回flash中。

**注意**

不管使用哪种flash，当擦除操作的单位为sector大小的整数倍时，需要在擦除数据前先将这些数据进行保存，以便修改其中一个sector的数据后将其他sector的数据写回flash中。

### FatFs API接口使用
   
  关于FatFs的API接口参数使用，可以参考：http://elm-chan.org/fsw/ff/00index_e.html。


	










