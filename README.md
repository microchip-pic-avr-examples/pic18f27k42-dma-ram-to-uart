[![MCHP](images/microchip.png)](https://www.microchip.com)
# PIC18F27K42 DMA - RAM to UART TX Buffer - Hardware Triggered

# Introduction
The newer PIC18 family of devices showcase the Direct memory Access (DMA) module. This module can be used to move data within the micro-controller without the CPU. This frees up the CPU to attend to other tasks.

The DMA module on the new PIC micro-controllers allows the user to read data from the Flash memory/EEPROM and the user RAM area and write it to the user RAM area. The DMA module has configurable source and destination addresses and programmable hardware triggers to start and abort the transaction.

On devices that feature the DMA module, the priority of the data buses is decided by a system arbiter. the priorities are programmable by the user and help provide greater flexibility for different types of applications.

# Description
In this example, we will configure the DMA module to read data from an array stored in the RAM and write it in to the UART TX buffer. We will configure the hardware trigger for the DMA module to be the UART Transmit Interrupt, so the DMA will load the next data byte automatically. This hardware triggers allow the DMA module to wait until a byte of data is transmitted out of the TX buffer.

# MCC settings
Here are the setting in Microchip Code Configurator (MCC) for the DMA module. Open MCC to modify these settings if needed.

### DMA Control registers
These are settings for the DMAxCON0 and DMAxCON1 registers. Look at the dma.c file to understand more about these selections.

![](https://i.imgur.com/5GpaMID.jpg)

### DMA Source Address and Size registers
These are the settings for the source size and address location. The source size is 23 bytes (0x0017). We will modify the generated dma.c file to provide the address of the source data array.

![](https://i.imgur.com/YFIWfRd.jpg)

### DMA Destination Address and Size registers
These are the settings for the destination size and address location. The destination size is 1 byte (0x0001). i.e. UART TX buffer.  We will modify the generated dma.c file to provide the address of UART TX buffer.

![](https://i.imgur.com/woWfaxm.jpg)

### Other MCC settings
MCC is also used to setup the UART module as a transmitter and also to setup the I/O pins. Please open the project and MCC to look at these settings.

# Operation
Here is the modified code in dma.c which now has the edited source and destination addresses.

```
void DMA1_Initialize(void)
{
    DMA1SSA = &TX_DATA;         //set source start address
    DMA1DSA = &U1TXB;           //set destination start address
    DMA1CON1 = 0x03;            //DMODE = 00 | DSTP = 0 | SMR = 01 | SMODE = 01 | SSTP = 1
    DMA1SSZ = 0x0017;           //set source size = 23 bytes
    DMA1DSZ = 0x0001;           //set destination size = 1 byte
    DMA1SIRQ = 0x1C;            //set DMA Transfer Trigger Source = U1TX
    DMA1AIRQ = 0x00;            //set DMA Transfer abort Source

    PIR2bits.DMA1DCNTIF = 0;    //clear Destination Count Interrupt Flag bit
    PIR2bits.DMA1SCNTIF = 0;    //clear Source Count Interrupt Flag bit
    PIR2bits.DMA1AIF = 0;       //clear abort Interrupt Flag bit
    PIR2bits.DMA1ORIF = 0;      //clear overrun Interrupt Flag bit

    PIE2bits.DMA1DCNTIE = 0;    //disable Destination Count 0 Interrupt
    PIE2bits.DMA1SCNTIE = 0;    //disable Source Count Interrupt
    PIE2bits.DMA1AIE = 0;       //disable abort Interrupt
    PIE2bits.DMA1ORIE = 0;      //disable overrun Interrupt

    asm("BCF INTCON0,7");       //disable Global Interrupts

    asm ("BANKSEL PRLOCK");     //
    asm ("MOVLW 0x55");         //
    asm ("MOVWF PRLOCK");       //Arbiter Priority lock
    asm ("MOVLW 0xAA");         //sequence   
    asm ("MOVWF PRLOCK");       //
    asm ("BSF PRLOCK, 0");      //

    asm("BSF INTCON0,7");       //enable Global Interrupts

    DMA1CON0 = 0x80;            //EN = 1 | SIRQEN = 0 | DGO = 0 |xx| AIRQEN = 0 |x| XIP = 0
}
```

The DMA trigger has been selected but not enabled. Note that enabling the trigger will initiate the DMA transfer immediately as the TX buffer is empty at start. Subsequent triggers are generated every time a byte has been sent out the TX buffer.

The following line of code in main.c will enable the trigger.

```
DMA1CON0bits.SIRQEN = 1;
```

# Results
The data from the UART module can be observed on pin RC6. It is to be observed that all this data is handled by the DMA module while the CPU is idling. This time can be used to perform other important tasks.

![](https://i.imgur.com/tubrWps.jpg)
