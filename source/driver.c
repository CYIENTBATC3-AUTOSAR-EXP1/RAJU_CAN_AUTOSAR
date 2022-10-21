/*
 * File:   main.c
 * Author: rb65404
 *
 * Created on October 11, 2022, 4:49 PM
 */


#include <xc.h>
#include "CAN_Driver.h"

/*
 * System Init
 * Initializing Interrupts and all
 */
void sys_Init()
{
    GIE = 1;    /* Enabling Global Interrupts */
    PEIE = 1;   /* Enabling Peripheral Interrupts */
    
    TRISBbits.RB0 = 0;
    TRISBbits.RB2 = 0;
}

/*
 * CAN Initialization
 */
void CAN_Init()
{
    TRISBbits.RB2 = 0;  // CAN TX
    TRISBbits.RB3 = 1;  // CAN RX
}

/* 
 *  This Function is used for CAN MODE setting
 *  "MODE" is a variable to set MODE
 *  "Buffer" is that which Buffer is going to used
 */
char CAN_Mode_Config(char MODE,char Buffer)
{
    CANCON = MODE | Buffer;
    while(!((CANCON & 0xF0) == MODE ));
    if( (CANCON & 0xF0) == MODE)
    {
      return 0;  
    }
    else{
      return 1;   
    }
}

/* 
 *  This Function is used for Baud Rate setting
 *  "BAUD_RATE" is a variable for the value of Baud Rate 
 */
char CAN_Baud_rate_set(char BAUD_RATE)
{
    char status=0;
    status = CAN_Mode_Config(CONFIG_MODE, Transmit_Buffer0); // getting into CAN Normal mode

//    CANCON = 0x80;
    __delay_ms(50);

    /* 125KHz*/
    if(BAUD_RATE == 125){
        BRGCON1 = 0xC1;
        BRGCON2 = 0xB1;
        BRGCON3 = 0x45;
        if( (BRGCON1 == 0xC1) && (BRGCON2 == 0xB1) && (BRGCON3 == 0x45))
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
    
    /* 250KHz*/
    if(BAUD_RATE == 250){
        BRGCON1 = 0xC1;
        BRGCON2 = 0xAE;
        BRGCON3 = 0xA5;
    
        if( (BRGCON1 == 0xC1) && (BRGCON2 == 0xAE) && (BRGCON3 == 0xA5))
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
}

void Fill_CAN_TX_Buff(char Frame_type,int ID,char DLC,char* Data)
{
    char status=0;
    status = CAN_Mode_Config(NORMAL_MODE,Transmit_Buffer0); // getting into CAN Normal mode
//    CANCON = 0x08;
    if(Frame_type)    /* Standard Mode */
    {
        TXB0SIDH = ((ID >> 3) & 0xFF);
        TXB0SIDL = ((ID << 5) & 0xFF);
        
        __delay_ms(10); /* making some 10 ms delay to set Identifier*/
                
        TXB0DLC = DLC; /* Filling Data Length Code in reg*/
        
        /* Filling with data in transmit buffers */
        TXB0D0 = Data[0];
        TXB0D1 = Data[1];
        TXB0D2 = Data[2];
        TXB0D3 = Data[3];
        TXB0D4 = Data[4];
        TXB0D5 = Data[5];
        TXB0D6 = Data[6];
        TXB0D7 = Data[7];
        
        TXB0CON = 0x08;  /* Request to send the data */
        
         __delay_ms(10); /* making some 10 ms delay*/
        
    }
    else
    {
        
    }   
        status = CAN_Mode_Config(NORMAL_MODE,Transmit_Buffer0 ); // getting into CAN Normal mode

    
}

void CAN_Read(int ID,char DLC,char* Data)
{
    char status=0;
    DLC     = RXB0DLC; /* Taking DLC Data from CAN RX */
    
    /* Reading CAN Identifier */
    ID  = ((RXB0SIDL >> 5)&0x0F) | ((RXB0SIDH << 5)& 0xFFF0);
    
    /* Reading RX Buffers */
    Data[0] = RXB0D0;
    Data[1] = RXB0D1;
    Data[2] = RXB0D2;
    Data[3] = RXB0D3;
    Data[4] = RXB0D4;
    Data[5] = RXB0D5;
    Data[6] = RXB0D6;
    Data[7] = RXB0D7;
    
    RXB0CONbits.RXFUL = 0;  /* Resetting control register */
    
    status = CAN_Mode_Config(NORMAL_MODE, Receive_Buffer0); // getting into CAN Normal mode
}