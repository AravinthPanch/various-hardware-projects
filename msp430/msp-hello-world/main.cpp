//
// main.cpp
// Main file
// ----------------------------------
// Developed with embedXcode
// http://embedXcode.weebly.com
//
// Project 		msp-hello-world
//
// Created by 	Aravinth Panchadcharam, 02/11/14 11:21
//              Aravinth Panchadcharam
//
// Copyright 	© Aravinth Panchadcharam, 2014
// License 		<#license#>
//
// See 			msp-hello-world.ino and ReadMe.txt for references
//
// ----------------------------------
// DO NOT EDIT THIS FILE.
// THE SKETCH IS IN msp_hello_world.ino
// ----------------------------------
//
// Last update: Aug 19, 2014 release 174

// IDE selection
#if defined(EMBEDXCODE)

// Core library and main()
#if defined(MPIDE)
// ============================================================================= chipKIT specific

//************************************************************************
//*	main.c
//*
//*	Arduino core files for PIC32
//*		Copyright (c) 2010, 2011 by Mark Sproul
//*
//*
//************************************************************************
//*	this code is based on code Copyright (c) 2005-2006 David A. Mellis
//*
//*	This library is free software; you can redistribute it and/or
//*	modify it under the terms of the GNU Lesser General Public
//*	License as published by the Free Software Foundation; either
//*	version 2.1 of the License, or (at your option) any later version.
//*
//*	This library is distributed in the hope that it will be useful,
//*	but WITHOUT ANY WARRANTY; without even the implied warranty of
//*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.//*	See the GNU
//*	Lesser General Public License for more details.
//*
//*	You should have received a copy of the GNU Lesser General
//*	Public License along with this library; if not, write to the
//*	Free Software Foundation, Inc., 59 Temple Place, Suite 330,
//*	Boston, MA  02111-1307  USA
//*
//*
//************************************************************************
//*	Edit History
//************************************************************************
//*	Oct 12,	2010	Got MPLAB X working on MacOSX 1.6 for the first time
//* Dec 12, 2011 <GeneApperson> added call to _scheduleTask() before call
//*					to loop().
//************************************************************************

#define OPT_SYSTEM_INTERNAL
#include <System_Defs.h>

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

extern "C" {
    extern void __use_isr_install(void);
    __attribute__((section(".comment"))) void (*__use_force_isr_install)(void) = &__use_isr_install;
}

//************************************************************************
int main(void)
{
	init();
    
	setup();
    
	while (1)
	{
		_scheduleTask();
		loop();
	}
	return 0;
}


#elif defined(DIGISPARK)
// ============================================================================= Digispark specific

#include "WProgram.h"

int main(void)
{
	init();
    
	setup();
    
	for (;;)
		loop();
    
	return 0;
}



#elif defined(MICRODUINO)
// ============================================================================= Microduino specific

#include "Arduino.h"

int main(void)
{
	init();
    
#if defined(USBCON)
	USBDevice.attach();
#endif
	
	setup();
    
	for (;;) {
		loop();
		if (serialEventRun) serialEventRun();
	}
    
	return 0;
}


#elif defined(ENERGIA)
// ============================================================================= LaunchPad MSP430, Stellaris and Tiva, Experimeter Board FR5739 specific

#if defined(__CC3200R1M1RGC__)

#include <Energia.h>
#include "inc/hw_gpio.h"
#include "driverlib/rom_map.h"
#include "driverlib/prcm.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include <driverlib/utils.h>
#include "inc/hw_hib1p2.h"
#include "inc/hw_hib3p3.h"

extern void (* const g_pfnVectors[])(void);

int main(void)
{
	IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);
    
	MAP_PRCMPeripheralClkEnable(PRCM_GPIOA0, PRCM_RUN_MODE_CLK);
	MAP_PRCMPeripheralClkEnable(PRCM_GPIOA1, PRCM_RUN_MODE_CLK);
	MAP_PRCMPeripheralClkEnable(PRCM_GPIOA2, PRCM_RUN_MODE_CLK);
	MAP_PRCMPeripheralClkEnable(PRCM_GPIOA3, PRCM_RUN_MODE_CLK);
    
	MAP_IntMasterEnable();
	PRCMCC3200MCUInit();
	MAP_SysTickIntEnable();
	MAP_SysTickPeriodSet(F_CPU / 1000);
	MAP_SysTickEnable();
    
	setup();
    
	for (;;) {
		loop();
		if (serialEventRun) serialEventRun();
	}
}

#elif defined(__LM4F120H5QR__) || defined(__TM4C1230C3PM__) || defined(__TM4C129XNCZAD__) || defined(__TM4C123GH6PM__)
// ----------------------------------------------------------------------------- LaunchPad Stellaris and Tiva specific
#include <Energia.h>

#if defined(PART_TM4C129XNCZAD)
#include "inc/tm4c129xnczad.h"
#elif defined(PART_TM4C1294NCPDT)
#include "inc/tm4c1294ncpdt.h"
#elif defined(PART_TM4C1233H6PM) || defined(PART_LM4F120H5QR)
#include "inc/tm4c123gh6pm.h"
#else
#error "**** No PART defined or unsupported PART ****"
#endif

#include "inc/hw_gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/eeprom.h"

#ifdef __cplusplus
extern "C" {
    
    void _init(void)
    {
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
        if(ROM_EEPROMInit() == EEPROM_INIT_ERROR) {
            if(ROM_EEPROMInit() != EEPROM_INIT_ERROR)
                EEPROMMassErase();
        }
        
        timerInit();
        
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ);
#ifdef TARGET_IS_SNOWFLAKE_RA0
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOR);
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOS);
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOT);
#endif
        
        //Unlock and commit NMI pins PD7 and PF0
        HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0x4C4F434B;
        HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x1;
        HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0x4C4F434B;
        HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= 0x80;
    } /* void _init(void) */
    
} /* extern "C" */
#endif

int main(void)
{
	setup();
    
	for (;;) {
		loop();
		if (serialEventRun) serialEventRun();
	}
}

#else
// ----------------------------------------------------------------------------- LaunchPad MSP430 and Experimeter Board FR5739 specific

#include <Energia.h>

int main(void)
{
	init();
    
	setup();
    
	for (;;) {
		loop();
		if (serialEventRun) serialEventRun();
	}
    
	return 0;
}

#endif                                                                          // Energia


#elif defined(MAPLE_IDE)
// ============================================================================= Maple specific

#include <WProgram.h>

// *****************************************************************************
//  The MIT License
//
//  Copyright (c) 2010 LeafLabs LLC.
//
//  Permission is hereby granted, free of charge, to any person
//  obtaining a copy of this software and associated documentation
//  files (the "Software"), to deal in the Software without
//  restriction, including without limitation the rights to use, copy,
//  modify, merge, publish, distribute, sublicense, and/or sell copies
//  of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be
//  included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
//  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
//  ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
// ****************************************************************************

__attribute__(( constructor )) void premain() {
    init();
}

int main(void) {
    setup();
    
    for (;;)
        loop();
    
    return 0;
}


#elif defined(TEENSYDUINO) || defined(CORE_TEENSY)
// ============================================================================= Teensy specific

#if defined(__MK20DX128__) || defined(__MK20DX256__)
// ----------------------------------------------------------------------------- Teensy 3 specific

#include "WProgram.h"

extern "C" int main(void)
{
	// Arduino's main() function just calls setup() and loop()....
	setup();
	while (1) {
		loop();
		yield();
	}
}

#else
// ----------------------------------------------------------------------------- Teensy 2 specific

#include "WProgram.h"

//int main(void) __attribute__((noreturn));
int main(void)
{
	_init_Teensyduino_internal_();
    
	setup();
    
    for (;;)
        loop();
}


#endif                                                                          // Teensy


#elif defined(WIRING)
// ============================================================================= Wiring specific

// Replace #include "WProgram.h" by #include "Wiring.h"
// Comment boardInit();

#include "Wiring.h"

int main(void)
{
    // Hardware specific initializations.
    //    boardInit();
    init();
    
    // User defined setup routine
    setup();
    // User defined loop routine
    for(;;)
        loop();
}


#elif defined(ARDUINO)
// ============================================================================= Arduino specific

#if (ARDUINO < 100)
// ----------------------------------------------------------------------------- Arduino 0023 specific

#include "WProgram.h"

int main(void)
{
	init();
    
	setup();
    
	for (;;)
		loop();
    
	return 0;
}


#elif (ARDUINO < 150)
// ----------------------------------------------------------------------------- Arduino 1.0x specific

#include "Arduino.h"

int main(void)
{
	init();
    
#if defined(USBCON)
	USBDevice.attach();
#endif
	
	setup();
    
	for (;;) {
		loop();
		if (serialEventRun) serialEventRun();
	}
    
	return 0;
}


#else
// ----------------------------------------------------------------------------- Arduino 1.5x specific

#if defined(__ARDUINO_X86__)
// ............................................................................. Arduino 1.5x X86 architecture specific

/*
 main.cpp userspace main loop for Intel Galileo family boards
 Copyright (C) 2014 Intel Corporation
 
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
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 
 */
// Arduino hooks
#include <Arduino.h>
#include <trace.h>
#include <interrupt.h>
#include <sys/stat.h>

#define PLATFORM_NAME_PATH "/sys/devices/platform/"

/************************ Static *************************/
#define MY_TRACE_PREFIX __FILE__

/************************ Global *************************/
int main(int argc, char * argv[])
{
	char *platform_path = NULL;
	struct stat s;
	int err;
    
	// Install a signal handler
    
	// make ttyprintk at some point
	stdout = freopen("/tmp/log.txt", "w", stdout);
	if (stdout == NULL){
	    fprintf(stderr, "unable to remap stdout !\n");
	    exit(-1);
	}
	fflush(stdout);
    
	stderr = freopen("/tmp/log_er.txt", "w", stderr);
	if (stderr == NULL){
	    printf("Unable to remap stderr !\n");
	    exit(-1);
	}
	fflush(stderr);
    
	// Snapshot time counter
	if (timeInit() < 0)
		exit(-1);
    
	// debug for the user
	if (argc < 2){
		fprintf(stderr, "./sketch tty0\n");
		return -1;
	}
	printf("started with binary=%s Serial=%s\n", argv[0], argv[1]);
	fflush(stdout);
    
	// check if we're running on the correct platform
	// and refuse to run if no match
    
	platform_path = (char *)malloc(sizeof(PLATFORM_NAME_PATH) + sizeof(PLATFORM_NAME));
	sprintf(platform_path,"%s%s", PLATFORM_NAME_PATH, PLATFORM_NAME);
    
	printf("checking platform_path [%s]\n", platform_path);
	fflush(stdout);
    
	err = stat(platform_path, &s);
    
	if(err != 0) {
		fprintf(stderr, "stat failed checking for %s with error code %d\n", PLATFORM_NAME, err);
		free(platform_path);
		return -1;
	}
	if(!S_ISDIR(s.st_mode)) {
		/* exists but is no dir */
		fprintf(stderr, "Target board not a %s\n", PLATFORM_NAME);
		free(platform_path);
		return -1;
	}
    
	printf("Running on a %s platform (%s)\n", PLATFORM_NAME, platform_path);
	fflush(stdout);
    
	free(platform_path);
    
	// TODO: derive trace level and optional IP from command line
	trace_init(VARIANT_TRACE_LEVEL, 0);
	trace_target_enable(TRACE_TARGET_UART);
    
	// Call Arduino init
	init(argc, argv);
    
	// Init IRQ layer
	// Called after init() to ensure I/O permissions inherited by pthread
	interrupt_init();
    
#if defined(USBCON)
	USBDevice.attach();
#endif
    
	setup();
	for (;;) {
		loop();
		//if (serialEventRun) serialEventRun();
	}
	return 0;
}


#elif defined(__SAM3X8E__)
// ............................................................................. Arduino 1.5x SAM architecture specific

/*
 Copyright (c) 2011 Arduino.  All rights reserved.
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#define ARDUINO_MAIN
#include "Arduino.h"

/*
 * Cortex-M3 Systick IT handler
 */
/*
 extern void SysTick_Handler( void )
 {
 // Increment tick count each ms
 TimeTick_Increment() ;
 }
 */

/*
 * \brief Main entry point of Arduino application
 */
int main( void )
{
	init();
    
	delay(1);
    
#if defined(USBCON)
	USBDevice.attach();
#endif
    
	setup();
    
	for (;;)
	{
		loop();
		if (serialEventRun) serialEventRun();
	}
    
	return 0;
}

#else
// ............................................................................. Arduino 1.5x AVR architecture specific

#include "Arduino.h"

int main(void)
{
	init();
    
#if defined(USBCON)
	USBDevice.attach();
#endif
	
	setup();
    
	for (;;) {
		loop();
		if (serialEventRun) serialEventRun();
	}
    
	return 0;
}


#endif                                                                          // architecture
#endif                                                                          // Arduino

#else                                                                           // error
#error Platform not defined
#endif                                                                          // end IDE

// Sketch
#include "msp_hello_world.ino"


#endif                                                                          // end embedXcode

