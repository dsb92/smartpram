/*******************************************************************************
* File Name: Signal_out.h  
* Version 1.70
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PINS_Signal_out_H) /* Pins Signal_out_H */
#define CY_PINS_Signal_out_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Signal_out_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Signal_out_Write(uint8 value) ;
void    Signal_out_SetDriveMode(uint8 mode) ;
uint8   Signal_out_ReadDataReg(void) ;
uint8   Signal_out_Read(void) ;
uint8   Signal_out_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Signal_out_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Signal_out_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Signal_out_DM_RES_UP          PIN_DM_RES_UP
#define Signal_out_DM_RES_DWN         PIN_DM_RES_DWN
#define Signal_out_DM_OD_LO           PIN_DM_OD_LO
#define Signal_out_DM_OD_HI           PIN_DM_OD_HI
#define Signal_out_DM_STRONG          PIN_DM_STRONG
#define Signal_out_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Signal_out_MASK               Signal_out__MASK
#define Signal_out_SHIFT              Signal_out__SHIFT
#define Signal_out_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Signal_out_PS                     (* (reg8 *) Signal_out__PS)
/* Data Register */
#define Signal_out_DR                     (* (reg8 *) Signal_out__DR)
/* Port Number */
#define Signal_out_PRT_NUM                (* (reg8 *) Signal_out__PRT) 
/* Connect to Analog Globals */                                                  
#define Signal_out_AG                     (* (reg8 *) Signal_out__AG)                       
/* Analog MUX bux enable */
#define Signal_out_AMUX                   (* (reg8 *) Signal_out__AMUX) 
/* Bidirectional Enable */                                                        
#define Signal_out_BIE                    (* (reg8 *) Signal_out__BIE)
/* Bit-mask for Aliased Register Access */
#define Signal_out_BIT_MASK               (* (reg8 *) Signal_out__BIT_MASK)
/* Bypass Enable */
#define Signal_out_BYP                    (* (reg8 *) Signal_out__BYP)
/* Port wide control signals */                                                   
#define Signal_out_CTL                    (* (reg8 *) Signal_out__CTL)
/* Drive Modes */
#define Signal_out_DM0                    (* (reg8 *) Signal_out__DM0) 
#define Signal_out_DM1                    (* (reg8 *) Signal_out__DM1)
#define Signal_out_DM2                    (* (reg8 *) Signal_out__DM2) 
/* Input Buffer Disable Override */
#define Signal_out_INP_DIS                (* (reg8 *) Signal_out__INP_DIS)
/* LCD Common or Segment Drive */
#define Signal_out_LCD_COM_SEG            (* (reg8 *) Signal_out__LCD_COM_SEG)
/* Enable Segment LCD */
#define Signal_out_LCD_EN                 (* (reg8 *) Signal_out__LCD_EN)
/* Slew Rate Control */
#define Signal_out_SLW                    (* (reg8 *) Signal_out__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Signal_out_PRTDSI__CAPS_SEL       (* (reg8 *) Signal_out__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Signal_out_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Signal_out__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Signal_out_PRTDSI__OE_SEL0        (* (reg8 *) Signal_out__PRTDSI__OE_SEL0) 
#define Signal_out_PRTDSI__OE_SEL1        (* (reg8 *) Signal_out__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Signal_out_PRTDSI__OUT_SEL0       (* (reg8 *) Signal_out__PRTDSI__OUT_SEL0) 
#define Signal_out_PRTDSI__OUT_SEL1       (* (reg8 *) Signal_out__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Signal_out_PRTDSI__SYNC_OUT       (* (reg8 *) Signal_out__PRTDSI__SYNC_OUT) 


#if defined(Signal_out__INTSTAT)  /* Interrupt Registers */

    #define Signal_out_INTSTAT                (* (reg8 *) Signal_out__INTSTAT)
    #define Signal_out_SNAP                   (* (reg8 *) Signal_out__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Signal_out_H */


/* [] END OF FILE */
