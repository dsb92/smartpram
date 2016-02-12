/*******************************************************************************
* File Name: Mobile_motor.h  
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

#if !defined(CY_PINS_Mobile_motor_H) /* Pins Mobile_motor_H */
#define CY_PINS_Mobile_motor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Mobile_motor_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Mobile_motor_Write(uint8 value) ;
void    Mobile_motor_SetDriveMode(uint8 mode) ;
uint8   Mobile_motor_ReadDataReg(void) ;
uint8   Mobile_motor_Read(void) ;
uint8   Mobile_motor_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Mobile_motor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Mobile_motor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Mobile_motor_DM_RES_UP          PIN_DM_RES_UP
#define Mobile_motor_DM_RES_DWN         PIN_DM_RES_DWN
#define Mobile_motor_DM_OD_LO           PIN_DM_OD_LO
#define Mobile_motor_DM_OD_HI           PIN_DM_OD_HI
#define Mobile_motor_DM_STRONG          PIN_DM_STRONG
#define Mobile_motor_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Mobile_motor_MASK               Mobile_motor__MASK
#define Mobile_motor_SHIFT              Mobile_motor__SHIFT
#define Mobile_motor_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Mobile_motor_PS                     (* (reg8 *) Mobile_motor__PS)
/* Data Register */
#define Mobile_motor_DR                     (* (reg8 *) Mobile_motor__DR)
/* Port Number */
#define Mobile_motor_PRT_NUM                (* (reg8 *) Mobile_motor__PRT) 
/* Connect to Analog Globals */                                                  
#define Mobile_motor_AG                     (* (reg8 *) Mobile_motor__AG)                       
/* Analog MUX bux enable */
#define Mobile_motor_AMUX                   (* (reg8 *) Mobile_motor__AMUX) 
/* Bidirectional Enable */                                                        
#define Mobile_motor_BIE                    (* (reg8 *) Mobile_motor__BIE)
/* Bit-mask for Aliased Register Access */
#define Mobile_motor_BIT_MASK               (* (reg8 *) Mobile_motor__BIT_MASK)
/* Bypass Enable */
#define Mobile_motor_BYP                    (* (reg8 *) Mobile_motor__BYP)
/* Port wide control signals */                                                   
#define Mobile_motor_CTL                    (* (reg8 *) Mobile_motor__CTL)
/* Drive Modes */
#define Mobile_motor_DM0                    (* (reg8 *) Mobile_motor__DM0) 
#define Mobile_motor_DM1                    (* (reg8 *) Mobile_motor__DM1)
#define Mobile_motor_DM2                    (* (reg8 *) Mobile_motor__DM2) 
/* Input Buffer Disable Override */
#define Mobile_motor_INP_DIS                (* (reg8 *) Mobile_motor__INP_DIS)
/* LCD Common or Segment Drive */
#define Mobile_motor_LCD_COM_SEG            (* (reg8 *) Mobile_motor__LCD_COM_SEG)
/* Enable Segment LCD */
#define Mobile_motor_LCD_EN                 (* (reg8 *) Mobile_motor__LCD_EN)
/* Slew Rate Control */
#define Mobile_motor_SLW                    (* (reg8 *) Mobile_motor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Mobile_motor_PRTDSI__CAPS_SEL       (* (reg8 *) Mobile_motor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Mobile_motor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Mobile_motor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Mobile_motor_PRTDSI__OE_SEL0        (* (reg8 *) Mobile_motor__PRTDSI__OE_SEL0) 
#define Mobile_motor_PRTDSI__OE_SEL1        (* (reg8 *) Mobile_motor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Mobile_motor_PRTDSI__OUT_SEL0       (* (reg8 *) Mobile_motor__PRTDSI__OUT_SEL0) 
#define Mobile_motor_PRTDSI__OUT_SEL1       (* (reg8 *) Mobile_motor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Mobile_motor_PRTDSI__SYNC_OUT       (* (reg8 *) Mobile_motor__PRTDSI__SYNC_OUT) 


#if defined(Mobile_motor__INTSTAT)  /* Interrupt Registers */

    #define Mobile_motor_INTSTAT                (* (reg8 *) Mobile_motor__INTSTAT)
    #define Mobile_motor_SNAP                   (* (reg8 *) Mobile_motor__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Mobile_motor_H */


/* [] END OF FILE */
