/**
  UART1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    uart1.c

  @Summary
    This is the generated driver implementation file for the UART1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for UART1.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65
        Device            :  PIC18F27K42
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB             :  MPLAB X 4.10
*/
/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/
/**
  Section: Included Files
*/
#include <xc.h>
#include "uart1.h"


/**
  Section: UART1 APIs
*/

void UART1_Initialize(void)
{

    // Set the UART1 module to the options selected in the user interface.

    // P1L 0; 
    U1P1L = 0x00;

    // P1H 0; 
    U1P1H = 0x00;

    // P2L 0; 
    U1P2L = 0x00;

    // P2H 0; 
    U1P2H = 0x00;

    // P3L 0; 
    U1P3L = 0x00;

    // P3H 0; 
    U1P3H = 0x00;

    // BRGS high speed; MODE Asynchronous 8-bit mode; RXEN disabled; TXEN enabled; ABDEN disabled; 
    U1CON0 = 0xA0;

    // RXBIMD Set RXBKIF on rising RX input; BRKOVR disabled; WUE disabled; SENDB disabled; ON enabled; 
    U1CON1 = 0x80;

    // TXPOL not inverted; FLO off; C0EN Checksum Mode 0; RXPOL not inverted; RUNOVF RX input shifter stops all activity; STP Transmit 1Stop bit, receiver verifies first Stop bit; 
    U1CON2 = 0x00;

    // BRGL 51; 
    U1BRGL = 0x33;

    // BRGH 0; 
    U1BRGH = 0x00;

    // STPMD in middle of first Stop bit; TXWRE No error; 
    U1FIFO = 0x00;

    // ABDIF Auto-baud not enabled or not complete; WUIF WUE not enabled by software; ABDIE disabled; 
    U1UIR = 0x00;

    // ABDOVF Not overflowed; TXCIF 0; RXBKIF No Break detected; RXFOIF not overflowed; CERIF No Checksum error; 
    U1ERRIR = 0x00;

    // TXCIE disabled; FERIE disabled; TXMTIE disabled; ABDOVE disabled; CERIE disabled; RXFOIE disabled; PERIE disabled; RXBKIE disabled; 
    U1ERRIE = 0x00;


}

uint8_t UART1_Read(void)
{
    U1CON0bits.RXEN = 1;	

    while(!PIR3bits.U1RXIF)
    {
    }

    if(1 == U1ERRIRbits.FERIF)
    {
        // UART1 error - restart

        U1CON1bits.ON = 0; 
        U1CON1bits.ON = 1; 
    }

    return U1RXB;
}
void UART1_Write(uint8_t txData)
{
    while(0 == PIR3bits.U1TXIF)
    {
    }

    U1TXB = txData;    // Write the data byte to the USART.
}

/**
  End of File
*/
