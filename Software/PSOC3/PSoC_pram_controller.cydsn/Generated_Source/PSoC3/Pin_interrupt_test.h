/*******************************************************************************
* File Name: Pin_interrupt_test.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Pin_interrupt_test_H) /* Pins Pin_interrupt_test_H */
#define CY_PINS_Pin_interrupt_test_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin_interrupt_test_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_interrupt_test_Write(uint8 value) ;
void    Pin_interrupt_test_SetDriveMode(uint8 mode) ;
uint8   Pin_interrupt_test_ReadDataReg(void) ;
uint8   Pin_interrupt_test_Read(void) ;
uint8   Pin_interrupt_test_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_interrupt_test_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin_interrupt_test_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin_interrupt_test_DM_RES_UP          PIN_DM_RES_UP
#define Pin_interrupt_test_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin_interrupt_test_DM_OD_LO           PIN_DM_OD_LO
#define Pin_interrupt_test_DM_OD_HI           PIN_DM_OD_HI
#define Pin_interrupt_test_DM_STRONG          PIN_DM_STRONG
#define Pin_interrupt_test_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin_interrupt_test_MASK               Pin_interrupt_test__MASK
#define Pin_interrupt_test_SHIFT              Pin_interrupt_test__SHIFT
#define Pin_interrupt_test_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_interrupt_test_PS                     (* (reg8 *) Pin_interrupt_test__PS)
/* Data Register */
#define Pin_interrupt_test_DR                     (* (reg8 *) Pin_interrupt_test__DR)
/* Port Number */
#define Pin_interrupt_test_PRT_NUM                (* (reg8 *) Pin_interrupt_test__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin_interrupt_test_AG                     (* (reg8 *) Pin_interrupt_test__AG)                       
/* Analog MUX bux enable */
#define Pin_interrupt_test_AMUX                   (* (reg8 *) Pin_interrupt_test__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin_interrupt_test_BIE                    (* (reg8 *) Pin_interrupt_test__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin_interrupt_test_BIT_MASK               (* (reg8 *) Pin_interrupt_test__BIT_MASK)
/* Bypass Enable */
#define Pin_interrupt_test_BYP                    (* (reg8 *) Pin_interrupt_test__BYP)
/* Port wide control signals */                                                   
#define Pin_interrupt_test_CTL                    (* (reg8 *) Pin_interrupt_test__CTL)
/* Drive Modes */
#define Pin_interrupt_test_DM0                    (* (reg8 *) Pin_interrupt_test__DM0) 
#define Pin_interrupt_test_DM1                    (* (reg8 *) Pin_interrupt_test__DM1)
#define Pin_interrupt_test_DM2                    (* (reg8 *) Pin_interrupt_test__DM2) 
/* Input Buffer Disable Override */
#define Pin_interrupt_test_INP_DIS                (* (reg8 *) Pin_interrupt_test__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin_interrupt_test_LCD_COM_SEG            (* (reg8 *) Pin_interrupt_test__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin_interrupt_test_LCD_EN                 (* (reg8 *) Pin_interrupt_test__LCD_EN)
/* Slew Rate Control */
#define Pin_interrupt_test_SLW                    (* (reg8 *) Pin_interrupt_test__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin_interrupt_test_PRTDSI__CAPS_SEL       (* (reg8 *) Pin_interrupt_test__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin_interrupt_test_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin_interrupt_test__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin_interrupt_test_PRTDSI__OE_SEL0        (* (reg8 *) Pin_interrupt_test__PRTDSI__OE_SEL0) 
#define Pin_interrupt_test_PRTDSI__OE_SEL1        (* (reg8 *) Pin_interrupt_test__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin_interrupt_test_PRTDSI__OUT_SEL0       (* (reg8 *) Pin_interrupt_test__PRTDSI__OUT_SEL0) 
#define Pin_interrupt_test_PRTDSI__OUT_SEL1       (* (reg8 *) Pin_interrupt_test__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin_interrupt_test_PRTDSI__SYNC_OUT       (* (reg8 *) Pin_interrupt_test__PRTDSI__SYNC_OUT) 


#if defined(Pin_interrupt_test__INTSTAT)  /* Interrupt Registers */

    #define Pin_interrupt_test_INTSTAT                (* (reg8 *) Pin_interrupt_test__INTSTAT)
    #define Pin_interrupt_test_SNAP                   (* (reg8 *) Pin_interrupt_test__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Pin_interrupt_test_H */


/* [] END OF FILE */
