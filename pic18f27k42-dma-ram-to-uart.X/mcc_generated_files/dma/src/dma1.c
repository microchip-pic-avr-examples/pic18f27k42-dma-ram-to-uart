/**
 * DMA1 Generated Driver File.
 * 
 * @file dma1.c
 * 
 * @ingroup  dma1
 * 
 * @brief This file contains the API implementations for the DMA1 driver.
 *
 * @version DMA1 Driver Version 2.12.1
 */ 

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

 /**
   Section: Included Files
 */

#include <xc.h>
#include "../dma1.h"

uint8_t txData[23];

/**
  Section: DMA1 APIs
*/

void DMA1_Initialize(void)
{   
    
    //Source Address : (uint24_t) &txData
    DMA1SSA = (uint24_t) &txData;
    //Destination Address : (uint16_t) &U1TXB
    DMA1DSA = (uint16_t) &U1TXB;
    //SSTP cleared; SMODE incremented; SMR GPR; DSTP not cleared; DMODE unchanged; 
    DMA1CON1 = 0x3;
    //Source Message Size : 23
    DMA1SSZ = 23;
    //Destination Message Size : 1
    DMA1DSZ = 1;
    //Start Trigger : SIRQ U1TX; 
    DMA1SIRQ = 0x1C;
    //Abort Trigger : AIRQ None; 
    DMA1AIRQ = 0x0;
	
    // Clear Destination Count Interrupt Flag bit
    PIR2bits.DMA1DCNTIF = 0; 
    // Clear Source Count Interrupt Flag bit
    PIR2bits.DMA1SCNTIF = 0; 
    // Clear Abort Interrupt Flag bit
    PIR2bits.DMA1AIF = 0; 
    // Clear Overrun Interrupt Flag bit
    PIR2bits.DMA1ORIF =0; 
    
    PIE2bits.DMA1DCNTIE = 0;
    PIE2bits.DMA1SCNTIE = 0;
    PIE2bits.DMA1AIE = 0;
    PIE2bits.DMA1ORIE = 0;
	
    //AIRQEN disabled; DGO not in progress; SIRQEN disabled; EN enabled; 
    DMA1CON0 = 0x80;
	 
}

void DMA1_Enable(void)
{
    DMA1CON0bits.EN = 0x1;
}

void DMA1_Disable(void)
{
    DMA1CON0bits.EN = 0x0;
}

void DMA1_SourceRegionSelect(uint8_t region)
{
	DMA1CON1bits.SMR  = region;
}

void DMA1_SourceAddressSet(uint24_t address)
{
	DMA1SSA = address;
}

uint24_t DMA1_SourceAddressGet(void)
{
    return DMA1SSA;
}

void DMA1_DestinationAddressSet(uint16_t address)
{
	DMA1DSA = address;
}

uint16_t DMA1_DestinationAddressGet(void)
{
    return DMA1DSA;
}

void DMA1_SourceSizeSet(uint16_t size)
{
	DMA1SSZ= size;
}

uint16_t DMA1_SourceSizeGet(void)
{
    return DMA1SSZ;
}

void DMA1_DestinationSizeSet(uint16_t size)
{                     
	DMA1DSZ= size;
}

uint16_t DMA1_DestinationSizeGet(void)
{                     
    return DMA1DSZ;
}

uint24_t DMA1_SourcePointerGet(void)
{
	return DMA1SPTR;
}

uint16_t DMA1_DestinationPointerGet(void)
{
	return DMA1DPTR;
}

uint16_t DMA1_SourceCountGet(void)
{
    return DMA1SCNT;
}

uint16_t DMA1_DestinationCountGet(void)
{                     
    return DMA1DCNT;
}

void DMA1_StartTriggerSet(uint8_t sirq)
{
	DMA1SIRQ = sirq;
}

void DMA1_AbortTriggerSet(uint8_t airq)
{
	DMA1AIRQ = airq;
}

void DMA1_TransferStart(void)
{
	DMA1CON0bits.DGO = 1;
}

void DMA1_TransferWithTriggerStart(void)
{
	DMA1CON0bits.SIRQEN = 1;
}

void DMA1_TransferStop(void)
{
	DMA1CON0bits.SIRQEN = 0; 
	DMA1CON0bits.DGO = 0;
}

void DMA1_DMAPrioritySet(uint8_t priority)
{
    uint8_t GIESaveState = INTCON0bits.GIE;
    INTCON0bits.GIE = 0;
	PRLOCK = 0x55;
	PRLOCK = 0xAA;
	PRLOCKbits.PRLOCKED = 0;
	DMA1PR = priority;
	PRLOCK = 0x55;
	PRLOCK = 0xAA;
	PRLOCKbits.PRLOCKED = 1;
    INTCON0bits.GIE = GIESaveState;
}

/**
 End of File
*/
