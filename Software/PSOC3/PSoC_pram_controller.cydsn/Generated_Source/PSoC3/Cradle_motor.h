/*******************************************************************************
* File Name: Cradle_motor.h  
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

#if !defined(CY_PINS_Cradle_motor_H) /* Pins Cradle_motor_H */
#define CY_PINS_Cradle_motor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Cradle_motor_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Cradle_motor_Write(uint8 value) ;
void    Cradle_motor_SetDriveMode(uint8 mode) ;
uint8   Cradle_motor_ReadDataReg(void) ;
uint8   Cradle_motor_Read(void) ;
uint8   Cradle_motor_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Cradle_motor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Cradle_motor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Cradle_motor_DM_RES_UP          PIN_DM_RES_UP
#define Cradle_motor_DM_RES_DWN         PIN_DM_RES_DWN
#define Cradle_motor_DM_OD_LO           PIN_DM_OD_LO
#define Cradle_motor_DM_OD_HI           PIN_DM_OD_HI
#define Cradle_motor_DM_STRONG          PIN_DM_STRONG
#define Cradle_motor_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Cradle_motor_MASK               Cradle_motor__MASK
#define Cradle_motor_SHIFT              Cradle_motor__SHIFT
#define Cradle_motor_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Cradle_motor_PS                     (* (reg8 *) Cradle_motor__PS)
/* Data Register */
#define Cradle_motor_DR                     (* (reg8 *) Cradle_motor__DR)
/* Port Number */
#define Cradle_motor_PRT_NUM                (* (reg8 *) Cradle_motor__PRT) 
/* Connect to Analog Globals */                                                  
#define Cradle_motor_AG                     (* (reg8 *) Cradle_motor__AG)                       
/* Analog MUX bux enable */
#define Cradle_motor_AMUX                   (* (reg8 *) Cradle_motor__AMUX) 
/* Bidirectional Enable */                                                        
#define Cradle_motor_BIE                    (* (reg8 *) Cradle_motor__BIE)
/* Bit-mask for Aliased Register Access */
#define Cradle_motor_BIT_MASK               (* (reg8 *) Cradle_motor__BIT_MASK)
/* Bypass Enable */
#define Cradle_motor_BYP                    (* (reg8 *) Cradle_motor__BYP)
/* Port wide control signals */                                                   
#define Cradle_motor_CTL                    (* (reg8 *) Cradle_motor__CTL)
/* Drive Modes */
#define Cradle_motor_DM0                    (* (reg8 *) Cradle_motor__DM0) 
#define Cradle_motor_DM1                    (* (reg8 *) Cradle_motor__DM1)
#define Cradle_motor_DM2                    (* (reg8 *) Cradle_motor__DM2) 
/* Input Buffer Disable Override */
#define Cradle_motor_INP_DIS                (* (reg8 *) Cradle_motor__INP_DIS)
/* LCD Common or Segment Drive */
#define Cradle_motor_LCD_COM_SEG            (* (reg8 *) Cradle_motor__LCD_COM_SEG)
/* Enable Segment LCD */
#define Cradle_motor_LCD_EN                 (* (reg8 *) Cradle_motor__LCD_EN)
/* Slew Rate Control */
#define Cradle_motor_SLW                    (* (reg8 *) Cradle_motor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Cradle_motor_PRTDSI__CAPS_SEL       (* (reg8 *) Cradle_motor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Cradle_motor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Cradle_motor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Cradle_motor_PRTDSI__OE_SEL0        (* (reg8 *) Cradle_motor__PRTDSI__OE_SEL0) 
#define Cradle_motor_PRTDSI__OE_SEL1        (* (reg8 *) Cradle_motor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Cradle_motor_PRTDSI__OUT_SEL0       (* (reg8 *) Cradle_motor__PRTDSI__OUT_SEL0) 
#define Cradle_motor_PRTDSI__OUT_SEL1       (* (reg8 *) Cradle_motor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Cradle_motor_PRTDSI__SYNC_OUT       (* (reg8 *) Cradle_motor__PRTDSI__SYNC_OUT) 


#if defined(Cradle_motor__INTSTAT)  /* Interrupt Registers */

    #define Cradle_motor_INTSTAT                (* (reg8 *) Cradle_motor__INTSTAT)
    #define Cradle_motor_SNAP                   (* (reg8 *) Cradle_motor__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Cradle_motor_H */


/* [] END OF FILE */
