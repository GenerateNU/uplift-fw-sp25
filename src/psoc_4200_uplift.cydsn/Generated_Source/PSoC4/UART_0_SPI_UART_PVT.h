/***************************************************************************//**
* \file UART_0_SPI_UART_PVT.h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_PVT_UART_0_H)
#define CY_SCB_SPI_UART_PVT_UART_0_H

#include "UART_0_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (UART_0_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  UART_0_rxBufferHead;
    extern volatile uint32  UART_0_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   UART_0_rxBufferOverflow;
    /** @} globals */
#endif /* (UART_0_INTERNAL_RX_SW_BUFFER_CONST) */

#if (UART_0_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  UART_0_txBufferHead;
    extern volatile uint32  UART_0_txBufferTail;
#endif /* (UART_0_INTERNAL_TX_SW_BUFFER_CONST) */

#if (UART_0_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 UART_0_rxBufferInternal[UART_0_INTERNAL_RX_BUFFER_SIZE];
#endif /* (UART_0_INTERNAL_RX_SW_BUFFER) */

#if (UART_0_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 UART_0_txBufferInternal[UART_0_TX_BUFFER_SIZE];
#endif /* (UART_0_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void UART_0_SpiPostEnable(void);
void UART_0_SpiStop(void);

#if (UART_0_SCB_MODE_SPI_CONST_CFG)
    void UART_0_SpiInit(void);
#endif /* (UART_0_SCB_MODE_SPI_CONST_CFG) */

#if (UART_0_SPI_WAKE_ENABLE_CONST)
    void UART_0_SpiSaveConfig(void);
    void UART_0_SpiRestoreConfig(void);
#endif /* (UART_0_SPI_WAKE_ENABLE_CONST) */

void UART_0_UartPostEnable(void);
void UART_0_UartStop(void);

#if (UART_0_SCB_MODE_UART_CONST_CFG)
    void UART_0_UartInit(void);
#endif /* (UART_0_SCB_MODE_UART_CONST_CFG) */

#if (UART_0_UART_WAKE_ENABLE_CONST)
    void UART_0_UartSaveConfig(void);
    void UART_0_UartRestoreConfig(void);
#endif /* (UART_0_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in UART_0_SetPins() */
#define UART_0_UART_RX_PIN_ENABLE    (UART_0_UART_RX)
#define UART_0_UART_TX_PIN_ENABLE    (UART_0_UART_TX)

/* UART RTS and CTS position to be used in  UART_0_SetPins() */
#define UART_0_UART_RTS_PIN_ENABLE    (0x10u)
#define UART_0_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define UART_0_SpiUartEnableIntRx(intSourceMask)  UART_0_SetRxInterruptMode(intSourceMask)
#define UART_0_SpiUartEnableIntTx(intSourceMask)  UART_0_SetTxInterruptMode(intSourceMask)
uint32  UART_0_SpiUartDisableIntRx(void);
uint32  UART_0_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_UART_0_H) */


/* [] END OF FILE */
