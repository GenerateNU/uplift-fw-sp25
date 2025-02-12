/*******************************************************************************
* File Name: DIR_FRONT_LEFT.h  
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

#if !defined(CY_PINS_DIR_FRONT_LEFT_H) /* Pins DIR_FRONT_LEFT_H */
#define CY_PINS_DIR_FRONT_LEFT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DIR_FRONT_LEFT_aliases.h"


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
} DIR_FRONT_LEFT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DIR_FRONT_LEFT_Read(void);
void    DIR_FRONT_LEFT_Write(uint8 value);
uint8   DIR_FRONT_LEFT_ReadDataReg(void);
#if defined(DIR_FRONT_LEFT__PC) || (CY_PSOC4_4200L) 
    void    DIR_FRONT_LEFT_SetDriveMode(uint8 mode);
#endif
void    DIR_FRONT_LEFT_SetInterruptMode(uint16 position, uint16 mode);
uint8   DIR_FRONT_LEFT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DIR_FRONT_LEFT_Sleep(void); 
void DIR_FRONT_LEFT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DIR_FRONT_LEFT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DIR_FRONT_LEFT_DRIVE_MODE_BITS        (3)
    #define DIR_FRONT_LEFT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DIR_FRONT_LEFT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DIR_FRONT_LEFT_SetDriveMode() function.
         *  @{
         */
        #define DIR_FRONT_LEFT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DIR_FRONT_LEFT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DIR_FRONT_LEFT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DIR_FRONT_LEFT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DIR_FRONT_LEFT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DIR_FRONT_LEFT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DIR_FRONT_LEFT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DIR_FRONT_LEFT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DIR_FRONT_LEFT_MASK               DIR_FRONT_LEFT__MASK
#define DIR_FRONT_LEFT_SHIFT              DIR_FRONT_LEFT__SHIFT
#define DIR_FRONT_LEFT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DIR_FRONT_LEFT_SetInterruptMode() function.
     *  @{
     */
        #define DIR_FRONT_LEFT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DIR_FRONT_LEFT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DIR_FRONT_LEFT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DIR_FRONT_LEFT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DIR_FRONT_LEFT__SIO)
    #define DIR_FRONT_LEFT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DIR_FRONT_LEFT__PC) && (CY_PSOC4_4200L)
    #define DIR_FRONT_LEFT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DIR_FRONT_LEFT_USBIO_DISABLE              ((uint32)(~DIR_FRONT_LEFT_USBIO_ENABLE))
    #define DIR_FRONT_LEFT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DIR_FRONT_LEFT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DIR_FRONT_LEFT_USBIO_ENTER_SLEEP          ((uint32)((1u << DIR_FRONT_LEFT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DIR_FRONT_LEFT_USBIO_SUSPEND_DEL_SHIFT)))
    #define DIR_FRONT_LEFT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DIR_FRONT_LEFT_USBIO_SUSPEND_SHIFT)))
    #define DIR_FRONT_LEFT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DIR_FRONT_LEFT_USBIO_SUSPEND_DEL_SHIFT)))
    #define DIR_FRONT_LEFT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DIR_FRONT_LEFT__PC)
    /* Port Configuration */
    #define DIR_FRONT_LEFT_PC                 (* (reg32 *) DIR_FRONT_LEFT__PC)
#endif
/* Pin State */
#define DIR_FRONT_LEFT_PS                     (* (reg32 *) DIR_FRONT_LEFT__PS)
/* Data Register */
#define DIR_FRONT_LEFT_DR                     (* (reg32 *) DIR_FRONT_LEFT__DR)
/* Input Buffer Disable Override */
#define DIR_FRONT_LEFT_INP_DIS                (* (reg32 *) DIR_FRONT_LEFT__PC2)

/* Interrupt configuration Registers */
#define DIR_FRONT_LEFT_INTCFG                 (* (reg32 *) DIR_FRONT_LEFT__INTCFG)
#define DIR_FRONT_LEFT_INTSTAT                (* (reg32 *) DIR_FRONT_LEFT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DIR_FRONT_LEFT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DIR_FRONT_LEFT__SIO)
    #define DIR_FRONT_LEFT_SIO_REG            (* (reg32 *) DIR_FRONT_LEFT__SIO)
#endif /* (DIR_FRONT_LEFT__SIO_CFG) */

/* USBIO registers */
#if !defined(DIR_FRONT_LEFT__PC) && (CY_PSOC4_4200L)
    #define DIR_FRONT_LEFT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DIR_FRONT_LEFT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DIR_FRONT_LEFT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DIR_FRONT_LEFT_DRIVE_MODE_SHIFT       (0x00u)
#define DIR_FRONT_LEFT_DRIVE_MODE_MASK        (0x07u << DIR_FRONT_LEFT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DIR_FRONT_LEFT_H */


/* [] END OF FILE */
