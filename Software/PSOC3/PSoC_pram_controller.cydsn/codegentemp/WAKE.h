/*******************************************************************************
* File Name: WAKE.h  
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

#if !defined(CY_PINS_WAKE_H) /* Pins WAKE_H */
#define CY_PINS_WAKE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "WAKE_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    WAKE_Write(uint8 value) ;
void    WAKE_SetDriveMode(uint8 mode) ;
uint8   WAKE_ReadDataReg(void) ;
uint8   WAKE_Read(void) ;
uint8   WAKE_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define WAKE_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define WAKE_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define WAKE_DM_RES_UP          PIN_DM_RES_UP
#define WAKE_DM_RES_DWN         PIN_DM_RES_DWN
#define WAKE_DM_OD_LO           PIN_DM_OD_LO
#define WAKE_DM_OD_HI           PIN_DM_OD_HI
#define WAKE_DM_STRONG          PIN_DM_STRONG
#define WAKE_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define WAKE_MASK               WAKE__MASK
#define WAKE_SHIFT              WAKE__SHIFT
#define WAKE_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define WAKE_PS                     (* (reg8 *) WAKE__PS)
/* Data Register */
#define WAKE_DR                     (* (reg8 *) WAKE__DR)
/* Port Number */
#define WAKE_PRT_NUM                (* (reg8 *) WAKE__PRT) 
/* Connect to Analog Globals */                                                  
#define WAKE_AG                     (* (reg8 *) WAKE__AG)                       
/* Analog MUX bux enable */
#define WAKE_AMUX                   (* (reg8 *) WAKE__AMUX) 
/* Bidirectional Enable */                                                        
#define WAKE_BIE                    (* (reg8 *) WAKE__BIE)
/* Bit-mask for Aliased Register Access */
#define WAKE_BIT_MASK               (* (reg8 *) WAKE__BIT_MASK)
/* Bypass Enable */
#define WAKE_BYP                    (* (reg8 *) WAKE__BYP)
/* Port wide control signals */                                                   
#define WAKE_CTL                    (* (reg8 *) WAKE__CTL)
/* Drive Modes */
#define WAKE_DM0                    (* (reg8 *) WAKE__DM0) 
#define WAKE_DM1                    (* (reg8 *) WAKE__DM1)
#define WAKE_DM2                    (* (reg8 *) WAKE__DM2) 
/* Input Buffer Disable Override */
#define WAKE_INP_DIS                (* (reg8 *) WAKE__INP_DIS)
/* LCD Common or Segment Drive */
#define WAKE_LCD_COM_SEG            (* (reg8 *) WAKE__LCD_COM_SEG)
/* Enable Segment LCD */
#define WAKE_LCD_EN                 (* (reg8 *) WAKE__LCD_EN)
/* Slew Rate Control */
#define WAKE_SLW                    (* (reg8 *) WAKE__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define WAKE_PRTDSI__CAPS_SEL       (* (reg8 *) WAKE__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define WAKE_PRTDSI__DBL_SYNC_IN    (* (reg8 *) WAKE__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define WAKE_PRTDSI__OE_SEL0        (* (reg8 *) WAKE__PRTDSI__OE_SEL0) 
#define WAKE_PRTDSI__OE_SEL1        (* (reg8 *) WAKE__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define WAKE_PRTDSI__OUT_SEL0       (* (reg8 *) WAKE__PRTDSI__OUT_SEL0) 
#define WAKE_PRTDSI__OUT_SEL1       (* (reg8 *) WAKE__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define WAKE_PRTDSI__SYNC_OUT       (* (reg8 *) WAKE__PRTDSI__SYNC_OUT) 


#if defined(WAKE__INTSTAT)  /* Interrupt Registers */

    #define WAKE_INTSTAT                (* (reg8 *) WAKE__INTSTAT)
    #define WAKE_SNAP                   (* (reg8 *) WAKE__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins WAKE_H */


/* [] END OF FILE */
