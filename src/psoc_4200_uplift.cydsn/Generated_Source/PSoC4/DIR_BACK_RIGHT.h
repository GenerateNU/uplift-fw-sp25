/*******************************************************************************
* File Name: DIR_BACK_RIGHT.h  
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

#if !defined(CY_PINS_DIR_BACK_RIGHT_H) /* Pins DIR_BACK_RIGHT_H */
#define CY_PINS_DIR_BACK_RIGHT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DIR_BACK_RIGHT_aliases.h"


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
} DIR_BACK_RIGHT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DIR_BACK_RIGHT_Read(void);
void    DIR_BACK_RIGHT_Write(uint8 value);
uint8   DIR_BACK_RIGHT_ReadDataReg(void);
#if defined(DIR_BACK_RIGHT__PC) || (CY_PSOC4_4200L) 
    void    DIR_BACK_RIGHT_SetDriveMode(uint8 mode);
#endif
void    DIR_BACK_RIGHT_SetInterruptMode(uint16 position, uint16 mode);
uint8   DIR_BACK_RIGHT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DIR_BACK_RIGHT_Sleep(void); 
void DIR_BACK_RIGHT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DIR_BACK_RIGHT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DIR_BACK_RIGHT_DRIVE_MODE_BITS        (3)
    #define DIR_BACK_RIGHT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DIR_BACK_RIGHT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DIR_BACK_RIGHT_SetDriveMode() function.
         *  @{
         */
        #define DIR_BACK_RIGHT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DIR_BACK_RIGHT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DIR_BACK_RIGHT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DIR_BACK_RIGHT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DIR_BACK_RIGHT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DIR_BACK_RIGHT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DIR_BACK_RIGHT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DIR_BACK_RIGHT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DIR_BACK_RIGHT_MASK               DIR_BACK_RIGHT__MASK
#define DIR_BACK_RIGHT_SHIFT              DIR_BACK_RIGHT__SHIFT
#define DIR_BACK_RIGHT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DIR_BACK_RIGHT_SetInterruptMode() function.
     *  @{
     */
        #define DIR_BACK_RIGHT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DIR_BACK_RIGHT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DIR_BACK_RIGHT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DIR_BACK_RIGHT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DIR_BACK_RIGHT__SIO)
    #define DIR_BACK_RIGHT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DIR_BACK_RIGHT__PC) && (CY_PSOC4_4200L)
    #define DIR_BACK_RIGHT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DIR_BACK_RIGHT_USBIO_DISABLE              ((uint32)(~DIR_BACK_RIGHT_USBIO_ENABLE))
    #define DIR_BACK_RIGHT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DIR_BACK_RIGHT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DIR_BACK_RIGHT_USBIO_ENTER_SLEEP          ((uint32)((1u << DIR_BACK_RIGHT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DIR_BACK_RIGHT_USBIO_SUSPEND_DEL_SHIFT)))
    #define DIR_BACK_RIGHT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DIR_BACK_RIGHT_USBIO_SUSPEND_SHIFT)))
    #define DIR_BACK_RIGHT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DIR_BACK_RIGHT_USBIO_SUSPEND_DEL_SHIFT)))
    #define DIR_BACK_RIGHT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DIR_BACK_RIGHT__PC)
    /* Port Configuration */
    #define DIR_BACK_RIGHT_PC                 (* (reg32 *) DIR_BACK_RIGHT__PC)
#endif
/* Pin State */
#define DIR_BACK_RIGHT_PS                     (* (reg32 *) DIR_BACK_RIGHT__PS)
/* Data Register */
#define DIR_BACK_RIGHT_DR                     (* (reg32 *) DIR_BACK_RIGHT__DR)
/* Input Buffer Disable Override */
#define DIR_BACK_RIGHT_INP_DIS                (* (reg32 *) DIR_BACK_RIGHT__PC2)

/* Interrupt configuration Registers */
#define DIR_BACK_RIGHT_INTCFG                 (* (reg32 *) DIR_BACK_RIGHT__INTCFG)
#define DIR_BACK_RIGHT_INTSTAT                (* (reg32 *) DIR_BACK_RIGHT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DIR_BACK_RIGHT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DIR_BACK_RIGHT__SIO)
    #define DIR_BACK_RIGHT_SIO_REG            (* (reg32 *) DIR_BACK_RIGHT__SIO)
#endif /* (DIR_BACK_RIGHT__SIO_CFG) */

/* USBIO registers */
#if !defined(DIR_BACK_RIGHT__PC) && (CY_PSOC4_4200L)
    #define DIR_BACK_RIGHT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DIR_BACK_RIGHT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DIR_BACK_RIGHT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DIR_BACK_RIGHT_DRIVE_MODE_SHIFT       (0x00u)
#define DIR_BACK_RIGHT_DRIVE_MODE_MASK        (0x07u << DIR_BACK_RIGHT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DIR_BACK_RIGHT_H */


/* [] END OF FILE */
