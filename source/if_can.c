/*
 * File:   com.c
 * Author: rb65404
 *
 * Created on October 20, 2022, 10:58 AM
 */


#include "CAN_Driver.h"
#include "CAN_IF.h"
#include "PDUR_Config.h"
/*
 * CAN_IF is used to call Mode Setting functions
 * "MODE" is a variable to set MODE
 *  "Buffer" is that which Buffer is going to used
 */
//char CAN_IF(char Transmission_Type,char Buffer)



//char CAN_IF(char Transmission_Type,char Buffer,int ID,char DLC,int Data)
//{
//    char Status=0;
//    if(Transmission_Type) /* TX Type */
//    {
//        Status = CAN_Mode_Config(NORMAL_MODE,Transmit_Buffer0); /* Calling API to set CAN TX Mode */ 
//    }
//    else            /* RX Type */
//    {
//        Status = CAN_Mode_Config(NORMAL_MODE,Receive_Buffer0); /* Calling API to set CAN RX Mode */
////        CAN_Read(ID,DLC,Data); /* Calling Driver API to Read CAN RX Data */
//    }
//
//    return Status;
//}

void Take_CAN_RX_Index(int ID,char DLC,char* Data)
{
//    CAN_Read(ID,DLC,Data); /* Calling Driver API to Read CAN RX Data */
}



void   CAN_IF_Send_Msg(PDUR_COM_MSg_list_E Msg_no,int CAN_ID,char CAN_DLC,char Data[])
{
    switch(Msg_no)
    {
        case 0:
            Fill_CAN_TX_Buff(PDUR_Frame[Msg_no],CAN_ID,CAN_DLC,Data);
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
    }
}
