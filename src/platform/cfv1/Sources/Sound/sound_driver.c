/****************************************************************************************
* 
*   FILE        :    Driver_Sound.c
*   DATE CREATED:    
*   DESCRIPTION	:    
*
*   Author		:     
*  	Location	:    
*   Purpose		:
*   Copyright	:    
*                                                  
* UPDATED HISTORY:
*
* REV   YYYY.MM.DD  AUTHOR          	DESCRIPTION OF CHANGE
* ---   ----------  ------          	--------------------- 
* 1.0   2011.06.09  Gustavo Denardin	Initial version (sound_record.c)
* 1.1	2011.06.16  Gustavo Denardin	Add: Wave_Start_Playing()
* 1.2   2011.06.28  Diogo Vargas		Add: Sound_VolumeControl
*
****************************************************************************************/

#include "sound_driver.h"
#include "timer2.h"
#include "da.h"
#include "utils.h"
#include "debug_stack.h"

#if (SD_WAVE == 1)
BRTOS_Sem 	  *Audio;		// BRTOS Semaphore
unsigned char vol = 10;		// sound volume



/**
  Function Name	: _SoundRecorder_Start_Recording
  Engineer      : Gustavo Denardin
  Date          : 09/06/2011
  
  Parameters	: Nothing
  Returns       : Nothing
  Notes         : This function starts to record and save the ADC values to a buffer. Once the
                  buffer size is reached it exits.
*/
#if 0
INT16U ADCMicrophoneValues[16000] = {0};

void _SoundRecorder_Start_Recording(void)
{
	INT32U RecordingSampleCount = 0;
	
    //_FlexTimer_Enable(FTM0);
  
    do
    {
		OSSemPend(Audio,0);
    	//ADCMicrophoneValues[RecordingSampleCount++] = _ADC0_Read(10,CHANNEL_A);
    
    }while (RecordingSampleCount < (sizeof(ADCMicrophoneValues)/2));
		
    //_FlexTimer_Disable(FTM0);
    //_ADC0_OFF();
    DelayTask(200);    
}



/**
  Function Name	: _SoundRecorder_Start_Playing
  Engineer      : Gustavo Denardin
  Date          : 09/06/2011
  
  Parameters	: Nothing
  Returns       : Nothing
  Notes         : 
*/

void _SoundRecorder_Start_Playing(void)
{
	INT16U PlayingSampleCount = 0;

	//_DAC1_Enable();
	//Sound_AudioAmplifierTurnOn();		//Turn On the Audio Amplifier
	//_FlexTimer_Enable(FTM0);
	
	#if (_VOLUME_CONTROL == 1)
		//Sound_VolumeControl(SetVolumeLevel);
	#endif
	
    do
    {
    	OSSemPend(Audio,0);
    	//_DAC1_Write(ADCMicrophoneValues[PlayingSampleCount++]);
	  
    }while (PlayingSampleCount < (sizeof(ADCMicrophoneValues)/2));

	//_FlexTimer_Disable(FTM0);   
	//_DAC1_Disable();
	Sound_AudioAmplifierStandby();		//Standby the Audio Amplifier
	DelayTask(200);
}
#endif

/**
  Function Name	: Wave_Start_Playing
  Engineer      : Gustavo Denardin
  Date          : 16/06/2011
  
  Parameters	: Nothing
  Returns       : Nothing
  Notes         : 
*/
void Wave_Start_Playing(void)
{
	WAVE_BUFFER *WaveInfo;
	INT8U		*Buff8;
	INT16S		*Buff16;
	INT16U		size = 0;
	INT8U		first = 0;
	
	//_DAC1_Enable();
	//Sound_AudioAmplifierTurnOn();	//Turn On the Audio Amplifier
	
	OSSemPost(OpenWave);	
	
	for(;;)
	{
    	(void)OSMboxPend(SendWaveBuffer,(void **)&WaveInfo,0);
  	
    	
	#if (_VOLUME_CONTROL == 1)
    	if(SetVolumeLevel == 0)	//Mute
    	{
    		//Sound_AudioAmplifierStandby();				//Standby the Audio Amplifier
    	}
    	else
    	{
    		//Sound_AudioAmplifierTurnOn();				//Turn On the Audio Amplifier
    		//Sound_VolumeControl((INT8U)SetVolumeLevel);	//Set Volume level
    	}
	#endif
    	
    	
    	if (first == 0)
    	{
    		first = 1;
    		
    		//Set sample rate: (8kHz, 11.025kHz, 44.1kHz or 48khz)
    		Wave_SetSampleRate(WaveInfo->SampleRate);

    		//Enable timer
    		Timer2Start();
    	}
    	
    	if ((WaveInfo->Size) == 0)
    	{
    		break;
    	}
    	size = WaveInfo->Size;

    	
    	if (WaveInfo->BitRate == 16)
    	{
    		Buff16 = (INT16S*)WaveInfo->Buff;
    	}
    	
    	else if (WaveInfo->BitRate == 8)
		{
			Buff8 = (INT8U*)WaveInfo->Buff;
		} 
    	   		
    	do
    	{
			OSSemPend(Audio,0);

			if (WaveInfo->BitRate == 16)
			{
				if (vol > 0)
				{
					DAConvert(((ByteSwap(*Buff16)) >> (4 + (10 - vol))) + 2048);
				}else
				{
					DAConvert(0);
				}
				Buff16++;
				if((WaveInfo->NumChannels) == 2)
				{
					Buff16++;	//Pula o  pacote do outro canal
					size--;
				}
			}
			
			else if (WaveInfo->BitRate == 8)
			{
				if (vol > 0)
				{
					DAConvert((INT16S)((ByteSwap(*Buff8)) << (4 + (10 - vol))) + 2048);
				}else
				{
					DAConvert(0);
				}
				Buff8++;
				
				if((WaveInfo->NumChannels) == 2)
				{
					Buff8++;	//Pula o  pacote do outro canal
					size--;
				}
			}    	
			size--;
    	}while(size > 0);
    	
    	OSSemPost(SyncWaveBuffer);
    }

	Timer2Stop(TRUE);   
	//_DAC1_Disable();
	Sound_AudioAmplifierStandby();		//Standby the Audio Amplifier
	DelayTask(200);
}


INT8U ChangeVol(CHAR8 *Volume, INT8U verbose)
{
	  // 100 to ...
	  if (Volume[2] != 0)
	  {
		  UserEnterCritical();
		  vol = 10;
		  UserExitCritical();
	  }else
	  {
		  // 0 to 10
		  //SetVolumeLevel = 10 + (name1[1]-48);
		  if (Volume[1] != 0)
		  {
			  UserEnterCritical();
			  vol = (10*(unsigned char)(Volume[0]-48)) + (unsigned char)(Volume[1]-48);
			  UserExitCritical();
		  }else
		  {
			  if (Volume[0] != 0)
			  {
				  UserEnterCritical();
				  vol = (unsigned char)(Volume[0]-48);
				  UserExitCritical();
			  }else
			  {
				  Print2Digits(vol, NO_ALIGN, Volume);
			  }
		  }
	  }
	  
	  //Error test (no valid Volume value)
	  if (vol <  1)
	  {
		  UserEnterCritical();
		  vol = 0;
		  UserExitCritical();
		  Volume = ("MUTE");
		  
	  }
	  else if (vol > 10)
	  {
		  vol = 10;
		  Volume[0] = '1';
		  Volume[1] = '0';
	  }
	  
      if (verbose == VERBOSE_ON)
	  {
		  //Print:	  
		  printSer(USE_USB, (CHAR8*)"\n\rVolume is: ");
		  printSer(USE_USB, (CHAR8*)Volume);
		  printSer(USE_USB, (CHAR8*)" (0 to 10)\n\r");
	  }
}

#endif

/******************************************************/





