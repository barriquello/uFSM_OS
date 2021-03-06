#include "BRTOS.h"
#include "drivers.h"
#include "tasks.h"
#include "AppConfig.h"

#ifdef __cplusplus
extern "C"
#endif

/******************************************************************************
 * @file main.c
 * @author Carlos H. Barriquello
 * @version
 * @date
 * @brief   This software is the GPRS_TRAFO project for Coldfire V1 JE256
 *****************************************************************************/

#if ((defined _MCF51MM256_H) || (defined _MCF51JE256_H) || (defined _MCF51JE128_H))
/* checksum bypass */
//const unsigned long checksum_bypass @0x00000408U = 0xFFFF00FF;
/* unsecure flash */
//const INT32U sec@0x040C = 0xFFFFFF00;  
//const byte CHKSBYP1_INIT @0x0000040A = 0x00;
//const unsigned char boot:0x040A = 0x00;   //zero out checksum to bypass boot loader


#endif /* (defined _MCF51MM256_H) || (defined _MCF51JE256_H) */

/******************************************************************************
 * @name        main
 * @brief       This function initializes the system, enables the interrupts and calls the application
 * @param       None
 * @return      None
 *****************************************************************************/
void main_old(void)
{
	
#if 1
	//SIGNATURE = 0x00;
	
	/* initial the system */
	Init_Sys();

	// Initialize BRTOS
	BRTOS_Init();

	if (InstallTask(&System_Time, "System Time", 256, 31, NULL) != OK)
	{
		while (1){};
	};

#if 1
	if (InstallTask(&Tarefa_termometro, "Tarefa de Termometro", 256, 19, NULL) != OK)
	{
		while (1){};
	};
#endif
	
#if 1
	if (InstallTask(&Tarefa_GPRS, "Tarefa do modem GPRS", 256, 28, NULL) != OK)
	{
		while (1){};
	};
#endif
	
#if TESTE_RS485
	if (InstallTask(&Tarefa_RS485, "Tarefa de teste RS485", 256, 5, NULL) != OK)
	{
		while (1){};
	};
#endif

#if 0
	if (InstallTask(&Tarefa_datalogger, "Datalogger", (384 + 256), 20, NULL) != OK)
	{
		while (1){};
	};
#endif	
	
#if TESTE_MODBUS

	if (InstallTask(&Task_modbus_slave, "MB slave", 256, 23, NULL) != OK)
	{
		while (1){}
	}
	

	if (InstallTask(&Task_modbus_slave_test, "MB slave test", 256, 22, NULL) != OK)
	{
		while (1){}
	}
	
#if TESTE_MODBUS_SLAVE
#if (defined TESTE_MODBUS_MASTER && TESTE_MODBUS_MASTER == 1)	
	
	if (InstallTask(&Task_modbus_master_test, "MB master test", (384+64), 21, NULL) != OK)
	{
		while (1){}
	}
#endif
#endif	
	
#endif	
	
#if USB_DEVICE_ENABLED
#if (USB_CLASS_TYPE == BRTOS_USB_MSD)
	if(InstallTask(&Mass_Storage_Device_Task,"Mass Storage Device Task",512,15,NULL) != OK)
	{
		while(1)
		{};
	};
#endif


#if (USB_CLASS_TYPE == BRTOS_USB_CDC)
	if (InstallTask(&Terminal_Task, "USB Terminal Task", 672, 15, NULL) != OK)
	{
		while (1){};
	};
#endif
#endif


#if 0
	if(InstallTask(&HMI,"Human-Machine Interface task",416,10,NULL) != OK)
	{
		while(1)
		{};
	};

	if(InstallTask(&Keyboard_Handler,"Keyboard handler task",416,12,NULL) != OK)
	{
		while(1)
		{};
	};
#endif

	// Start Task Scheduler
	if (BRTOSStart() != OK)
	{
		while (1){};
	};
#endif	

	for (;;)
	{
		__RESET_WATCHDOG();
		/* __RESET_WATCHDOG(); by default, COP is disabled with device init. When enabling, also reset the watchdog. */
	} /* loop forever */
	/* please make sure that you never leave main */
}

