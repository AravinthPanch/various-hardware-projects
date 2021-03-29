/************************************************************************/
/*																		*/
/*	IA_DATA.cpp  --	Library for Impedance Analyzer   	            		*/
/*																		*/
/************************************************************************/
/*	Author: 	Jessie W. Njuguna								    	*/
/*	Copyright 2014, Digilent Inc.										*/
/************************************************************************/
/*
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
/************************************************************************/
/*  Module Description: 												*/
/*																		*/
/*	This module contains the implementation of the object class that	*/
/*	forms a chipKIT interface to the Impedance Analyzer functions of    */
/*  the Digilent PmodIA_DATA.						  					*/
/*																		*/
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	06/22/2014(JessieN): Created										*/
/*	11/06/2015(JColvin): Fixed getGF() variable assignment				*/
/*  																	*/
/*	Notes (11/6/2015):													*/
/*		Need to update library to do the following:						*/
/*		-User selection of PGA setting									*/
/*		-User setting of calibration impedance used						*/
/*		-User selection of feedback resistor							*/
/*		-User selection of p2p voltage range							*/
/*		-Library auto-selection of PGA, and p2p voltage during 			*/
/*			calibration sequence										*/
/*  																	*/
/************************************************************************/

#include "WireIA.h"

/****************************** FUNCTION DEFINITIONS *****************************/
IA::IA()
{
	IA_init();
	
	//initialize register buffers
	ControlData 		= {0};
	StartFreqData	= {0};
	FrequencyIncData	= {0};
	NumIncData		= {0};
	SettlingTimeData = {0};
	realData 		= {0};
	imagData 		= {0};
	
	SParam.calibration_Flag = false;
	SParam.start_Freq = 0;
	SParam.freq_Step = 0;
	SParam.sweep_Samples = 0;
	SParam.repeat_Flag = 0;
	
	IA_DATA.gf_addr = 0;
	IA_DATA.gf_value_20 = 0.0;
	IA_DATA.gf_value_100K = 0.0;
	IA_DATA.rVAL = 0;
	IA_DATA.iVAL = 0;
	IA_DATA.range = 7;
	IA_DATA.pga_gain = 1;
	IA_DATA.SYSPhase = 0.0;
	IA_DATA.imp = 0.0;
	IA_DATA.ph_angle = 0.0;
	
}

 /***************************************************
* @function: 	IA_init
* @description: Initialize the IA I2C Communication
* @param:
* @return: 
****************************************************/
void IA::IA_init()
{
	Wire.begin();
}

void IA::IA_test()
{
	uint8_t Data[3] = {0};

	StartFreqData[0] = 96;
	StartFreqData[1] = 128;
	StartFreqData[2] = 45;
	Serial.println("IN test");
	Serial.println(StartFreqData[1]);
	
	
	setRegisterPointer(0x82);
	blockWrite(3, StartFreqData);
	
	
	//setRegisterPointer(0x82);
	blockRead(3, Data, 0x82);
	Serial.println("**********");
	
	Serial.println(Data[0]);
	Serial.println(Data[1]);
	Serial.println(Data[2]);
	
	Serial.println("**********");
	Data[1] = readRegisterValue(0x83);
	Serial.println(Data[1]);
	
	setStartFrequency(18000);
	blockRead(3, Data, 0x82);
	Serial.println("**********");
	
	Serial.println(Data[0]);
	Serial.println(Data[1]);
	Serial.println(Data[2]);
	
	Serial.println("**********");
}


/***********************************************************
* @function: 	setRegisterPointer
* @description: Set Register Pointer to a register address
* @param RegAddress: Register address to be set
* 
* @return: 		None	
************************************************************/

/*****************************************************************************************************/
//					  READ AND WRITE DATA TO EEPROM USING MPIDE EEPROM LIBRARY                       //
void IA::EEPROMReadGF()
{
	char *rptr;
	int i = 0, addr = IA_DATA.gf_addr;
	
	if(addr == 20)
	{
		rptr = (char *)&IA_DATA.gf_value_20;
		for(i = 0; i < sizeof(IA_DATA.gf_value_20); i++ )
		{			
		rptr[addr] = EEPROM.read(addr);
		addr++;
		}
	}
	else if(addr == 100)
	{
		rptr = (char *)&IA_DATA.gf_value_100K;
		for(i = 0; i < sizeof(IA_DATA.gf_value_100K); i++ )
		{			
		rptr[addr] = EEPROM.read(addr);
		addr++;
		}
	}
	else{
		Serial.println("Address Error");
		return;
	}
	
	
}

void IA::EEPROMWriteGF()
{
	int i = 0, addr = IA_DATA.gf_addr;
	char *ptr;
		
	if(addr == 20)
	{
		ptr = (char *)&IA_DATA.gf_value_20;
		for(i = 0; i < sizeof(IA_DATA.gf_value_20); i++)
		{
			if(ptr != NULL){
				EEPROM.write(addr, *ptr);
				ptr++;
				addr++;
			}
			else{
				break;}
		}
	}
	else if(addr == 100)
	{
		ptr = (char *)&IA_DATA.gf_value_100K;
		for(i = 0; i < sizeof(IA_DATA.gf_value_100K); i++)
		{
			if(ptr != NULL){
				EEPROM.write(addr, *ptr);
				ptr++;
				addr++;
			}
			else{
				break;}
		}
	}
	else{
		Serial.println("Address Error");
		return;
	}	
		

}
/*****************************************************************************************************/

void IA::setRegisterPointer(uint8_t RegAddress)
{
	Wire.beginTransmission(IA_ADDRESS);
	Wire.send(ADR_PTR_CMD);  
	Wire.send(RegAddress);
	Wire.endTransmission();
}
/*****************************************************************************
* @function: 		blockWrite
* @description: 	Write a stream of bytes to slave using block write command
* @param: numBytes: number of bytes to be sent to slave
* @param: *data:    data to be sent to slave
*
* @return: 			None
******************************************************************************/
void IA::blockWrite(int numBytes, uint8_t *data)
{
	Wire.beginTransmission(IA_ADDRESS);
	Wire.send(BLOCK_WRITE_CMD);
	Wire.send(numBytes);
	for(int i = 0; i < numBytes; i++)
	{
		//Serial.println(data[i]); // display data being transmitted to slave device
		Wire.send(data[i]);
	}
	//Serial.println("Out of BLOCK WRITE");
	Wire.endTransmission();
}

/********************************************************
* @function: 		blockRead
* @description: 	Read a block of data from slave device
* @param numBytes: 	number of bytes to be read from slave
* @param *buffer:  	buffer to store read data
* @param RegAddress:Register to start reading from
* @return 			None
*********************************************************/
void IA::blockRead (int numBytes, uint8_t *buffer, uint8_t RegAddress)
{
	
	for(int i = 0; i<numBytes; i++)
	{
		setRegisterPointer(RegAddress);
		Wire.requestFrom(IA_ADDRESS, 1);
		while(Wire.available())
		{
			buffer[i] = Wire.receive();
		}
		Wire.endTransmission();
		RegAddress++;
	}
}

/*****************************************************
* @function:	readRegisterValue
* @description: reads the value stored in a register
* @param:		Register address to read data
* @return: 		byte of data read
******************************************************/
uint8_t IA::readRegisterValue(uint8_t RegAddress)
{
	unsigned char data;
	
	setRegisterPointer(RegAddress);
	//Wire.beginTransmission(IA_ADDRESS);
	Wire.requestFrom(IA_ADDRESS, 1);
	while(Wire.available())
	{
		data = Wire.receive();
	}
	Wire.endTransmission();
	
	return data;
}
/***************************************************************************************************
* @function: 	 setControlRegister
* @description:	 this function, sets the AD5933 control modes
* @param function: Function mode of the AD5933
* @param gain:	 amplifies the response signal into the ADC by a 
*				 multiplication factor of x5 or x1
* @retrun:		 none
*
* NOTE--> Note that the control register should not be written to as part of a block write command.
****************************************************************************************************/
void IA::setControlRegister(unsigned int function, unsigned int gain)
{
	switch(function)
	{
		case 1: //Initialize with start frequency 
			ControlData[0] |= 0x10;
			break;
		case 2: //start frequency sweep
			ControlData[0] |= 0x20;
			break;
		case 3: //Increment frequency
			ControlData[0] |= 0x30;
			break;
		case 4: //Repeat Frequency
			ControlData[0] |= 0x40;
			break;
		case 9: //Measure Temperature
			ControlData[0] |= 0x90;
			break;
		case 10: //Power down mode
			ControlData[0] |= 0xA0;
			break;
		case 11: //Standby mode	
			ControlData[0] |= 0xB0;
			break;
		
		default:
			break;
	}
	
	setRange(IA_DATA.range);
	
	switch(gain)
  {
    case 0: // x5
      ControlData[0] |= 0x0;
      break;
    case 1: // x1
      ControlData[0] |= 0x1;
      break;
    default:
      break;
  }
	
	setRegisterPointer(CONTROL_REG);
	Wire.beginTransmission(IA_ADDRESS);
	Wire.send(CONTROL_REG);
	Wire.send(ControlData[0]);
	Wire.endTransmission();
}
/*********************************************
* @function: 	setStartFrequency
* @description: set start frequency for sweep
* @param frequency: start frequency
* @return 		None
**********************************************/
void IA::setStartFrequency(unsigned int frequency)
{
	unsigned long result = 0;
	
	result = frequency  * FREQUENCY_MULTIPLIER ;
	
	//Serial.print("0x");
	//Serial.println(result, HEX);
	
	StartFreqData[2] = (uint8_t) (result & 0xFF); 	
	StartFreqData[1] = (uint8_t) ((result >> 8) & 0xFF); 
	StartFreqData[0] = (uint8_t) ((result >> 16) & 0xFF);
	
	setRegisterPointer(START_FREQUENCY_REG);
    blockWrite(3, StartFreqData);	
}
/************************************************************************
* @function: 	setFrequencyIncrement
* @description:	sets the frequency delta increment between two consecutive
*				frequency points along the sweep
* @param deltaFreq: Delta Frequency to be added to current excitation 
*					frequency. 
* @return:		None
************************************************************************/
void IA::setFrequencyIncrement(unsigned int deltaFreq)
{
	unsigned long result = 0;
	
	result = deltaFreq * FREQUENCY_MULTIPLIER;
	FrequencyIncData[2] = (uint8_t) (result & 0xFF);
	FrequencyIncData[1] = (uint8_t) ((result>>8) & 0xFF);
	FrequencyIncData[0] = (uint8_t) ((result>>16) & 0xFF);
	
	setRegisterPointer(FREQUENCY_INCREMENT_REG);
	blockWrite(3, FrequencyIncData);
}
/**************************************************************************
* @function:	setNumSamples
* @description:	sets the number of frequency points in the frequency sweep
* @param samples:total number of samples 
* @return:		None
****************************************************************************/
void IA::setNumSamples(unsigned int samples)
{
	if(samples == 0x1FF || samples < 0x1FF){
		NumIncData[1] = (uint8_t)(samples & 0xFF);
		NumIncData[0] = (uint8_t)((samples>>8) & 0xFF);
	}
	else{
		//Serial.println("Num of Samples is too large");
		//Serial.println("Usage: samples < 512");
		return; 
	}
	
	setRegisterPointer(NUM_INCREMENTS_REG);
	blockWrite(2, NumIncData);
}
/**********************************************************************************
* @function:	setSettlingTime
* @description:	determines the number of output excitation cycles that are
*				allowed to pass through the unknown impedance
* @param settlingTime: 		number of settling time cycle
* @param settlingFactor: 	increases the settlingTime by either 2 or 4 or leaves 
*							it as default
* @return: 					None
************************************************************************************/
void IA::setSettlingTime(unsigned int settlingTime, unsigned int settlingFactor)
{
  uint8_t arr[2] = {0,0};
  
  if(settlingTime == 0x1FF || settlingTime < 0x1FF) {
   SettlingTimeData[1] = (uint8_t)(settlingTime & 0xFF);
   SettlingTimeData[0] = (uint8_t)((settlingTime >> 8)& 0xFF);    
  }
  else{
  //  Serial.println("Num of Settling Time is too large");
  //  Serial.println("Usage: < 512 ");
  }
  switch(settlingFactor)  {
    case 0:
      SettlingTimeData[0] |= 0x00; 
      break;
    case 1:
      SettlingTimeData[0] |= 0x2; //D10, D9 --> 01 
      break;
    case 3: 
      SettlingTimeData[0] |= 0x6; //D10, D9 --> 11
      break; 
  }
   
  setRegisterPointer(NUM_SETTLING_TIME_REG);
  blockWrite(2, SettlingTimeData);
}

/****************************************************************************************
* @function:		setRange
* @description: 	Function gives user an option to select range to use i.e, pick an 
*					output excitation voltage and feed back resistor 
* @param option: 	provides information of output voltage and feed back resistor to use		
* @return: 		
*****************************************************************************************/
void IA::setRange(int option)
{
	
	
	switch(option)
	{
		case 1: 	// 200mV, RFB = 20
			ControlData[0] |= 0x2;		
			break;
		case 2:	// 400mV, RFB = 20
			ControlData[0] |= 0x4;
			break;
		case 3:	// 1V, RFB = 20
			ControlData[0] |= 0x6;
			break;
		case 4:	// 2V, RFB = 20
			ControlData[0] |= 0x0; 
			break;
		case 5:	// 200mV, RFB = 100K
			ControlData[0] |= 0x2;
			break;
		case 6:	// 400mV, RFB = 100K
			ControlData[0] |= 0x4;
			break;
		case 7:	// 1V, RFB = 100K
			ControlData[0] |= 0x6;
			break;
		case 8:	// 2V, RFB = 100K
			ControlData[0] |= 0x0; 
			break;
		default:
			break;
			
	}
	
}

/***********************************************************************************************
* @function:		setSweepParameters
* @description: 	This function initializes the Sweep Parameter struct with sweep parameters
* @param cal_Flag: 		flag for calibration sweep to set system phase and gain factor
* @param begin_Flag: 	begin frequency sweep flag
* @param f_step:		frequency margin step
* @param nSamples:      number of samples points
* @param r_Flag: 		repeat flag for a sweep point repeat 
* @return: 		    None
*************************************************************************************************/
void IA::setSweepParameters(bool cal_Flag, int begin_Freq, int f_Step, int nSamples, bool r_Flag)
{
	SParam.calibration_Flag = cal_Flag;
	SParam.start_Freq = begin_Freq;
	SParam.freq_Step = f_Step;
	SParam.sweep_Samples = nSamples;
	SParam.repeat_Flag = r_Flag;
}
/*********************************************************************
* @function: 	PerformFrequencySweep
* @description: programs frequency sweep parameters into relevant
*				registers i.e.
*				1.Start Frequency Register	
*				2.Number of Increments Register
*				3.Frequency Increment Register
*				and then performs a frequency sweep through commands
*				to the control register.
* @param :		None	
* @retrun: 	    None
**********************************************************************/
void IA::PerformFrequencySweep()
{
	uint8_t BIT_1, BIT_2;

	setStartFrequency(SParam.start_Freq); //Hz
	setFrequencyIncrement(SParam.freq_Step); //Hz
	setNumSamples(SParam.sweep_Samples); 
	
	setSettlingTime(10, 3);
	
	if(IA_DATA.range){ //Range needs to be set before performing a freq sweep
	
		//1...............Place the AD5933 into standby mode
		setControlRegister(STAND_BY, IA_DATA.pga_gain);
		delay(50); 
		//2...............Initialize the Start Frequency Command to the Control Register
		setControlRegister(INIT_START_FREQ, IA_DATA.pga_gain);
		//3...............Program Start Frequency Sweep Command in the Control Register
		setControlRegister(START_FREQ_SWEEP, IA_DATA.pga_gain);
		delay(10);
		
		for(int num = 0; num < SParam.sweep_Samples; num++)
		{
			//4...........Poll Status register to check if the DFT conversion is complete
			setRegisterPointer(STATUS_REG);
			
			do{
				Wire.requestFrom(IA_ADDRESS,1);
				BIT_1 = Wire.receive();
				BIT_1 = BIT_1 & 0b00000010;
			}while(BIT_1 != 0x02);
			
			//5............Read Values from REAL and IMAGINARY data register
			getIA_Data();	
			
			if(SParam.calibration_Flag)
			{
				if(IA_DATA.range < 5)//20 Ohm Feed Back Resistor
				{
					CalculateGainFactor(FBR_20);
					twoPT_GF[num] = IA_DATA.gf_value_20;
					IA_DATA.gf_addr = 0;
					Phase();
					IA_DATA.SYSPhase = IA_DATA.ph_angle;
				}
				else{
					CalculateGainFactor(FBR_100K);
					twoPT_GF[num] = IA_DATA.gf_value_100K;
					IA_DATA.gf_addr = 100;
					Phase();
					IA_DATA.SYSPhase = IA_DATA.ph_angle;
				}
			}
			
			//6............Poll Status Register to check if frequency sweep is done
			do{
				Wire.requestFrom(IA_ADDRESS,1);
				BIT_2 = Wire.receive();
				BIT_2 = BIT_2 & 0b00000100;
			}while(BIT_2 != 0x04);
			
			if(SParam.sweep_Samples == 0 ){				
				break;
			}
			else if(SParam.repeat_Flag){ //Repeat Frequency Command	
				setControlRegister(REPEAT_FREQ, IA_DATA.pga_gain);
				delay(10);
			}
			else{
				setControlRegister(INC_FREQ, IA_DATA.pga_gain);
				delay(10);
			}
		}
		
	}
	else{
		//Error Range needs to set
	}
	//7..............Program the AD5933 into Power Down Mode
	setControlRegister(PWR_DOWN, IA_DATA.pga_gain);
	
}		


/**************************************************************************
* @function:	TwoPTCalibration
* @description: performs system calibration when called thereby determining
				the system gain factor and system phase shift. Saves the 
				calculated gain factor in the EEPROM
* @param:		
* @return: 		none
***************************************************************************/
void IA::TwoPTCalibration()
{
	SParam.calibration_Flag = true;
	SParam.start_Freq = 18000;
	SParam.freq_Step = 12000;
	SParam.sweep_Samples = 2;
	
	PerformFrequencySweep();
	
	double delta_GF = twoPT_GF[1] - twoPT_GF[0];
	
	if(IA_DATA.range < 5){
		IA_DATA.gf_value_20 = (delta_GF /2)+ twoPT_GF[0];
	}
	else{
		IA_DATA.gf_value_100K = (delta_GF /2)+ twoPT_GF[0];
	}
	
	EEPROMWriteGF();
		
	SParam.calibration_Flag = false;

}

/*****************************************************************
* @function: 	 CalculateGainFactor
* @description:	 Calculate gain factor of the AD5933 
* @param:        Known impedance to calibrate the system  
* @return:		 none
******************************************************************/
void IA::CalculateGainFactor(int CalibrationIMP)
{
	double gainFactor;
	double magnitude = 0.0;
	magnitude = sqrt((IA_DATA.rVAL * IA_DATA.rVAL) + ( IA_DATA.iVAL * IA_DATA.iVAL));
	
	if(IA_DATA.range < 5){
		IA_DATA.gf_value_20 = 1 / (magnitude * CalibrationIMP);
	}
	else{
		IA_DATA.gf_value_100K = 1 / (magnitude * CalibrationIMP);
	}
}
/*****************************************************************
* @function: 	 Impedance
* @description:	 Calculates impedance using a gain factor
* @param:          
* @return:		
******************************************************************/
void IA::Impedance()
{
	double Z = 0.0;
	double magnitude = 0.0;
	magnitude = sqrt((IA_DATA.rVAL * IA_DATA.rVAL) + ( IA_DATA.iVAL * IA_DATA.iVAL));
	
	if(IA_DATA.range < 5){
		IA_DATA.imp = 1 / (IA_DATA.gf_value_20 * magnitude);
	}
	else{
		IA_DATA.imp = 1 / (IA_DATA.gf_value_100K * magnitude);
	}
}

/*****************************************************************
* @function: 	 Phase
* @description:	 Calculates phase across an impedance
* @param:          
* @return:		  
******************************************************************/
void IA::Phase()
{
	double ph;
	IA_DATA.ph_angle = atan2(IA_DATA.iVAL, IA_DATA.rVAL);
}

/*****************************************************************
* @function: 	 ZReal
* @description:	 Calculates real component of the Impedance
*				 |Z_real| = |Z| * cos(Zphi)
* @param:          
* @return:		 |Z_real| 
******************************************************************/
double IA::ZReal()
{
	double ZR, Zphi = 0;
	Zphi = getPhase() - IA_DATA.SYSPhase;
	ZR = getImpedance() * cos(Zphi);
	return ZR;
}

/*****************************************************************
* @function: 	 ZImaginary
* @description:	 Calculates imaginary component of the Impedance
*				 |Z_imaginary| = |Z| * sin(Zphi)
* @param:          
* @return:		 |Z_imaginary| 
******************************************************************/
double IA::ZImaginary()
{
	double ZI, Zphi = 0;
	Zphi = getPhase() - IA_DATA.SYSPhase;
	ZI = getImpedance() * cos(Zphi);
	return ZI;
}

/************************************************************
* @function: 		getIAData
* @description: 	reads value from AD5933 registers and
*					then populates the IA Data struct. This 
*					function requires a frequency sweep to be 
*					conducted
* @param:
* @retrun: 
*************************************************************/
void IA::getIA_Data()
{
	//Real Data 
	blockRead(2, realData, REAL_DATA_REG);
	
	IA_DATA.rVAL = realData[0];
	IA_DATA.rVAL = IA_DATA.rVAL << 8;
	IA_DATA.rVAL |= realData[1]; 
	
	//Imaginary Data
	blockRead(2, imagData, IMAG_DATA_REG);
	
	IA_DATA.iVAL = imagData[0];
	IA_DATA.iVAL = IA_DATA.iVAL << 8;
	IA_DATA.iVAL = IA_DATA.iVAL | imagData[1];
}

/*****************************************************
* @function:	getGF
* @description: reads the Gain Factor from the EEPROM
* @param:		
* @return: 		
******************************************************/
double IA::getGF()
{
	double gain_value = 0.0;
	if(IA_DATA.range < 5){
		IA_DATA.gf_addr = 20;}
	else{
		IA_DATA.gf_addr = 100;}
		
	EEPROMReadGF();
	Serial.print("EEPROM GAIN FACTOR: --> ");
	switch(IA_DATA.gf_addr)
	{
		case 20: Serial.println(IA_DATA.gf_value_20, 10);
				 gain_value = IA_DATA.gf_value_20;
			break;
		case 100: Serial.println(IA_DATA.gf_value_100K, 10);
				  gain_value = IA_DATA.gf_value_100K;							//changed to .gf_value_100K from .gf_value_20 --11/06/2015 JColvin
			break;
		default:
			break;
	}
	return gain_value;
}

/****************************************************************
* @function:	getPhase
* @description: determines the phase angle of the impedance load
* @param:		
* @return: 	    phase angle of last measured impedance
*****************************************************************/
double IA::getPhase()
{
	Phase();
	return IA_DATA.ph_angle;  
}
/*****************************************************************************
* @function:	getImpedance 
* @description: gets the last measured impedance 
* @param:		
* @return: 		impedance value
********************************************************************************/
double IA::getImpedance()
{
	Impedance();
	return IA_DATA.imp;
}



