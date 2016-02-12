/*******************************************************************************
* File Name: V_PGA.h  
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

#if !defined(CY_PINS_V_PGA_H) /* Pins V_PGA_H */
#define CY_PINS_V_PGA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "V_PGA_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    V_PGA_Write(uint8 value) ;
void    V_PGA_SetDriveMode(uint8 mode) ;
uint8   V_PGA_ReadDataReg(void) ;
uint8   V_PGA_Read(void) ;
uint8   V_PGA_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define V_PGA_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define V_PGA_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define V_PGA_DM_RES_UP          PIN_DM_RES_UP
#define V_PGA_DM_RES_DWN         PIN_DM_RES_DWN
#define V_PGA_DM_OD_LO           PIN_DM_OD_LO
#define V_PGA_DM_OD_HI           PIN_DM_OD_HI
#define V_PGA_DM_STRONG          PIN_DM_STRONG
#define V_PGA_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define V_PGA_MASK               V_PGA__MASK
#define V_PGA_SHIFT              V_PGA__SHIFT
#define V_PGA_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define V_PGA_PS                     (* (reg8 *) V_PGA__PS)
/* Data Register */
#define V_PGA_DR                     (* (reg8 *) V_PGA__DR)
/* Port Number */
#define V_PGA_PRT_NUM                (* (reg8 *) V_PGA__PRT) 
/* Connect to Analog Globals */                                                  
#define V_PGA_AG                     (* (reg8 *) V_PGA__AG)                       
/* Analog MUX bux enable */
#define V_PGA_AMUX                   (* (reg8 *) V_PGA__AMUX) 
/* Bidirectional Enable */                                                        
#define V_PGA_BIE                    (* (reg8 *) V_PGA__BIE)
/* Bit-mask for Aliased Register Access */
#define V_PGA_BIT_MASK               (* (reg8 *) V_PGA__BIT_MASK)
/* Bypass Enable */
#define V_PGA_BYP                    (* (reg8 *) V_PGA__BYP)
/* Port wide control signals */                                                   
#define V_PGA_CTL                    (* (reg8 *) V_PGA__CTL)
/* Drive Modes */
#define V_PGA_DM0                    (* (reg8 *) V_PGA__DM0) 
#define V_PGA_DM1                    (* (reg8 *) V_PGA__DM1)
#define V_PGA_DM2                    (* (reg8 *) V_PGA__DM2) 
/* Input Buffer Disable Override */
#define V_PGA_INP_DIS                (* (reg8 *) V_PGA__INP_DIS)
/* LCD Common or Segment Drive */
#define V_PGA_LCD_COM_SEG            (* (reg8 *) V_PGA__LCD_COM_SEG)
/* Enable Segment LCD */
#define V_PGA_LCD_EN                 (* (reg8 *) V_PGA__LCD_EN)
/* Slew Rate Control */
#define V_PGA_SLW                    (* (reg8 *) V_PGA__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define V_PGA_PRTDSI__CAPS_SEL       (* (reg8 *) V_PGA__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define V_PGA_PRTDSI__DBL_SYNC_IN    (* (reg8 *) V_PGA__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define V_PGA_PRTDSI__OE_SEL0        (* (reg8 *) V_PGA__PRTDSI__OE_SEL0) 
#define V_PGA_PRTDSI__OE_SEL1        (* (reg8 *) V_PGA__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define V_PGA_PRTDSI__OUT_SEL0       (* (reg8 *) V_PGA__PRTDSI__OUT_SEL0) 
#define V_PGA_PRTDSI__OUT_SEL1       (* (reg8 *) V_PGA__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define V_PGA_PRTDSI__SYNC_OUT       (* (reg8 *) V_PGA__PRTDSI__SYNC_OUT) 


#if defined(V_PGA__INTSTAT)  /* Interrupt Registers */

    #define V_PGA_INTSTAT                (* (reg8 *) V_PGA__INTSTAT)
    #define V_PGA_SNAP                   (* (reg8 *) V_PGA__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins V_PGA_H */


/* [] END OF FILE */
