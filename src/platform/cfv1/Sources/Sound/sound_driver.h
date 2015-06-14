/*
 * Driver_Sound.h
 *
 *  Created on: 09/06/2011
 *      Author: gustavo
 */

#ifndef DRIVER_SOUND_H_
#define DRIVER_SOUND_H_

#include "BRTOS.h"
#include "SD_API.h"

#define	STOP		0 
#define	PLAYING		1
#define PAUSE		2

#define ReadWaveFilePriority	13
#define AudioTaskPriority		14

extern BRTOS_Sem *Audio;
extern BRTOS_Sem *OpenWave;
extern unsigned char vol;

extern void _SoundRecorder_Start_Recording(void);
extern void _SoundRecorder_Start_Playing(void);

#define Sound_AudioAmplifierStandby()	//_GPIO_Clear_Pin(PORTE,28)	//Standby the Audio Amplifier
#define Sound_AudioAmplifierTurnOn()	//_GPIO_Set_Pin(PORTE,28);	//Turn On the Audio Amplifier

#if (SD_WAVE == 1)
	void Wave_Start_Playing(void);
	INT8U ChangeVol(CHAR8 *Volume, INT8U verbose);	
#endif
	
	
#define _VOLUME_CONTROL 	0

#if (_VOLUME_CONTROL == 1)
	#define Down	0
	#define Up		1 
	extern INT8U SetVolumeLevel;
	void Sound_AudioAmplifierInit(void);
	void Sound_VolumeControl(INT8U Control);
#endif

	
	
	

#endif /* DRIVER_SOUND_H_ */
