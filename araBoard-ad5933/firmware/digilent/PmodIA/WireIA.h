/**********************************************
* @file:	IA.h
* @Author: 	Wanyika Njuguna(jnjuguna@ni.com)
* @Description: Chipkit IA demo
***********************************************/

#ifndef __WIREIA_H__
#define __WIREIA_H__	

#include <inttypes.h>
#include <Wire.h> 
#include <WProgram.h>
#include <EEPROM.h>


/***********************************************/
/****************** Macros *********************/

#define IA_ADDRESS		0x0D  //IA 
#define BLOCK_WRITE_CMD 0xA0  //block write command
#define BLOCK_READ_CMD  0xA1  //block read command
#define ADR_PTR_CMD     0xB0  //address pointer command

/*Register Map*/
//      Name				Register Address
#define CONTROL_REG 			0x80
#define START_FREQUENCY_REG  	0x82
#define FREQUENCY_INCREMENT_REG 0x85
#define NUM_INCREMENTS_REG		0x88
#define NUM_SETTLING_TIME_REG	0x8A
#define STATUS_REG				0x8F
#define TEMP_DATA_REG			0x92
#define REAL_DATA_REG			0x94
#define IMAG_DATA_REG			0x96

/*CONTROL REGISTER COMMANDS*/
#define INIT_START_FREQ			0x10
#define START_FREQ_SWEEP		0x20
#define INC_FREQ				0x30
#define REPEAT_FREQ				0x40
#define MEASURE_TEMP			0x90
#define PWR_DOWN				0xA0
#define STAND_BY				0xB0

/*AD5933 CONTROL FUNCTIONS */
#define AD5933_INIT_START_FREQ 

/*Constants*/
#define  FREQUENCY_MULTIPLIER      33.5544
#define  FBR_20					   20
#define  FBR_100K				   100000


class IA{
	private:
	
		/*Register Buffers*/
		uint8_t ControlData[2]; 
		uint8_t StartFreqData[3];
		uint8_t FrequencyIncData[3];
		uint8_t NumIncData[2];
		uint8_t SettlingTimeData[2];
		uint8_t realData[2];
		uint8_t imagData[2];
		
		double twoPT_GF[2];
		
						
		typedef struct IA_STRUCT
		{
			int gf_addr;
			double gf_value_20;
			double gf_value_100K;
			int16_t rVAL;
			int16_t iVAL;
			int range;
			int pga_gain;
			double SYSPhase;
			double imp;
			double ph_angle;
		}IA_STRUCT; 
		
		IA_STRUCT IA_DATA;
		
		
		typedef  struct SWEEP_PARAM
		{
			bool calibration_Flag;
			int start_Freq;
			int freq_Step;
			int sweep_Samples;
			bool repeat_Flag;
		}SWEEP_PARAM;
		
		SWEEP_PARAM SParam;	
			
		void EEPROMReadGF();
		void EEPROMWriteGF();
	public:
		
		IA();
			
		void setRegisterPointer(uint8_t RegAddress);
		void blockWrite(int numBytes, uint8_t *data);
		void blockRead (int numBytes, uint8_t *buffer, uint8_t RegAddress);
		uint8_t readRegisterValue(uint8_t RegAddress);
		
		/*IA Initialize*/
		
		void IA_init(void);
		void IA_test(void); // testing function
		/*Set Control Register*/
		void setControlRegister(unsigned int function, unsigned int gain);
		
		/*Set the start frequency*/
		void setStartFrequency(unsigned int frequency);
		
		/*Set the frequency increment*/
		void setFrequencyIncrement(unsigned int deltaFreq);
		
		/*Set number of frequency samples*/
		void setNumSamples(unsigned int samples);
		
		/*Set settling time*/
		void setSettlingTime(unsigned int settlingTime,	unsigned int settlingFactor);
								
		void setRange(int );
		
		void setSweepParameters(bool, int, int, int, bool);
		
		/*Performing a Frequency Sweep*/
		void PerformFrequencySweep(void);		
		
		void TwoPTCalibration();		
		void CalculateGainFactor(int CalibrationIMP);
		void Impedance();
		void Phase();
		double ZReal();
		double ZImaginary();
		
		void getIA_Data();
		double getGF();
		double getPhase();
		double getImpedance();	
		
		
};

#endif