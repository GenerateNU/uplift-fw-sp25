/*******************************************************************************
* File Name: BUTTON_TILT_EN.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_BUTTON_TILT_EN_H) /* Pins BUTTON_TILT_EN_H */
#define CY_PINS_BUTTON_TILT_EN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "BUTTON_TILT_EN_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} BUTTON_TILT_EN_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   BUTTON_TILT_EN_Read(void);
void    BUTTON_TILT_EN_Write(uint8 value);
uint8   BUTTON_TILT_EN_ReadDataReg(void);
#if defined(BUTTON_TILT_EN__PC) || (CY_PSOC4_4200L) 
    void    BUTTON_TILT_EN_SetDriveMode(uint8 mode);
#endif
void    BUTTON_TILT_EN_SetInterruptMode(uint16 position, uint16 mode);
uint8   BUTTON_TILT_EN_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void BUTTON_TILT_EN_Sleep(void); 
void BUTTON_TILT_EN_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(BUTTON_TILT_EN__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define BUTTON_TILT_EN_DRIVE_MODE_BITS        (3)
    #define BUTTON_TILT_EN_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BUTTON_TILT_EN_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the BUTTON_TILT_EN_SetDriveMode() function.
         *  @{
         */
        #define BUTTON_TILT_EN_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define BUTTON_TILT_EN_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define BUTTON_TILT_EN_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define BUTTON_TILT_EN_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define BUTTON_TILT_EN_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define BUTTON_TILT_EN_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define BUTTON_TILT_EN_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define BUTTON_TILT_EN_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define BUTTON_TILT_EN_MASK               BUTTON_TILT_EN__MASK
#define BUTTON_TILT_EN_SHIFT              BUTTON_TILT_EN__SHIFT
#define BUTTON_TILT_EN_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BUTTON_TILT_EN_SetInterruptMode() function.
     *  @{
     */
        #define BUTTON_TILT_EN_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define BUTTON_TILT_EN_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define BUTTON_TILT_EN_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define BUTTON_TILT_EN_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(BUTTON_TILT_EN__SIO)
    #define BUTTON_TILT_EN_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(BUTTON_TILT_EN__PC) && (CY_PSOC4_4200L)
    #define BUTTON_TILT_EN_USBIO_ENABLE               ((uint32)0x80000000u)
    #define BUTTON_TILT_EN_USBIO_DISABLE              ((uint32)(~BUTTON_TILT_EN_USBIO_ENABLE))
    #define BUTTON_TILT_EN_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define BUTTON_TILT_EN_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define BUTTON_TILT_EN_USBIO_ENTER_SLEEP          ((uint32)((1u << BUTTON_TILT_EN_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << BUTTON_TILT_EN_USBIO_SUSPEND_DEL_SHIFT)))
    #define BUTTON_TILT_EN_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << BUTTON_TILT_EN_USBIO_SUSPEND_SHIFT)))
    #define BUTTON_TILT_EN_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << BUTTON_TILT_EN_USBIO_SUSPEND_DEL_SHIFT)))
    #define BUTTON_TILT_EN_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(BUTTON_TILT_EN__PC)
    /* Port Configuration */
    #define BUTTON_TILT_EN_PC                 (* (reg32 *) BUTTON_TILT_EN__PC)
#endif
/* Pin State */
#define BUTTON_TILT_EN_PS                     (* (reg32 *) BUTTON_TILT_EN__PS)
/* Data Register */
#define BUTTON_TILT_EN_DR                     (* (reg32 *) BUTTON_TILT_EN__DR)
/* Input Buffer Disable Override */
#define BUTTON_TILT_EN_INP_DIS                (* (reg32 *) BUTTON_TILT_EN__PC2)

/* Interrupt configuration Registers */
#define BUTTON_TILT_EN_INTCFG                 (* (reg32 *) BUTTON_TILT_EN__INTCFG)
#define BUTTON_TILT_EN_INTSTAT                (* (reg32 *) BUTTON_TILT_EN__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define BUTTON_TILT_EN_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(BUTTON_TILT_EN__SIO)
    #define BUTTON_TILT_EN_SIO_REG            (* (reg32 *) BUTTON_TILT_EN__SIO)
#endif /* (BUTTON_TILT_EN__SIO_CFG) */

/* USBIO registers */
#if !defined(BUTTON_TILT_EN__PC) && (CY_PSOC4_4200L)
    #define BUTTON_TILT_EN_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define BUTTON_TILT_EN_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define BUTTON_TILT_EN_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define BUTTON_TILT_EN_DRIVE_MODE_SHIFT       (0x00u)
#define BUTTON_TILT_EN_DRIVE_MODE_MASK        (0x07u << BUTTON_TILT_EN_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins BUTTON_TILT_EN_H */


/* [] END OF FILE */
