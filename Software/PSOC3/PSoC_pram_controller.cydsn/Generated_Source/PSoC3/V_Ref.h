/*******************************************************************************
* File Name: V_Ref.h  
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

#if !defined(CY_PINS_V_Ref_H) /* Pins V_Ref_H */
#define CY_PINS_V_Ref_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "V_Ref_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    V_Ref_Write(uint8 value) ;
void    V_Ref_SetDriveMode(uint8 mode) ;
uint8   V_Ref_ReadDataReg(void) ;
uint8   V_Ref_Read(void) ;
uint8   V_Ref_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define V_Ref_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define V_Ref_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define V_Ref_DM_RES_UP          PIN_DM_RES_UP
#define V_Ref_DM_RES_DWN         PIN_DM_RES_DWN
#define V_Ref_DM_OD_LO           PIN_DM_OD_LO
#define V_Ref_DM_OD_HI           PIN_DM_OD_HI
#define V_Ref_DM_STRONG          PIN_DM_STRONG
#define V_Ref_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define V_Ref_MASK               V_Ref__MASK
#define V_Ref_SHIFT              V_Ref__SHIFT
#define V_Ref_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define V_Ref_PS                     (* (reg8 *) V_Ref__PS)
/* Data Register */
#define V_Ref_DR                     (* (reg8 *) V_Ref__DR)
/* Port Number */
#define V_Ref_PRT_NUM                (* (reg8 *) V_Ref__PRT) 
/* Connect to Analog Globals */                                                  
#define V_Ref_AG                     (* (reg8 *) V_Ref__AG)                       
/* Analog MUX bux enable */
#define V_Ref_AMUX                   (* (reg8 *) V_Ref__AMUX) 
/* Bidirectional Enable */                                                        
#define V_Ref_BIE                    (* (reg8 *) V_Ref__BIE)
/* Bit-mask for Aliased Register Access */
#define V_Ref_BIT_MASK               (* (reg8 *) V_Ref__BIT_MASK)
/* Bypass Enable */
#define V_Ref_BYP                    (* (reg8 *) V_Ref__BYP)
/* Port wide control signals */                                                   
#define V_Ref_CTL                    (* (reg8 *) V_Ref__CTL)
/* Drive Modes */
#define V_Ref_DM0                    (* (reg8 *) V_Ref__DM0) 
#define V_Ref_DM1                    (* (reg8 *) V_Ref__DM1)
#define V_Ref_DM2                    (* (reg8 *) V_Ref__DM2) 
/* Input Buffer Disable Override */
#define V_Ref_INP_DIS                (* (reg8 *) V_Ref__INP_DIS)
/* LCD Common or Segment Drive */
#define V_Ref_LCD_COM_SEG            (* (reg8 *) V_Ref__LCD_COM_SEG)
/* Enable Segment LCD */
#define V_Ref_LCD_EN                 (* (reg8 *) V_Ref__LCD_EN)
/* Slew Rate Control */
#define V_Ref_SLW                    (* (reg8 *) V_Ref__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define V_Ref_PRTDSI__CAPS_SEL       (* (reg8 *) V_Ref__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define V_Ref_PRTDSI__DBL_SYNC_IN    (* (reg8 *) V_Ref__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define V_Ref_PRTDSI__OE_SEL0        (* (reg8 *) V_Ref__PRTDSI__OE_SEL0) 
#define V_Ref_PRTDSI__OE_SEL1        (* (reg8 *) V_Ref__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define V_Ref_PRTDSI__OUT_SEL0       (* (reg8 *) V_Ref__PRTDSI__OUT_SEL0) 
#define V_Ref_PRTDSI__OUT_SEL1       (* (reg8 *) V_Ref__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define V_Ref_PRTDSI__SYNC_OUT       (* (reg8 *) V_Ref__PRTDSI__SYNC_OUT) 


#if defined(V_Ref__INTSTAT)  /* Interrupt Registers */

    #define V_Ref_INTSTAT                (* (reg8 *) V_Ref__INTSTAT)
    #define V_Ref_SNAP                   (* (reg8 *) V_Ref__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins V_Ref_H */


/* [] END OF FILE */
