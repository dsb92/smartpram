/*******************************************************************************
* File Name: Temp_in.h  
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

#if !defined(CY_PINS_Temp_in_H) /* Pins Temp_in_H */
#define CY_PINS_Temp_in_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Temp_in_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Temp_in_Write(uint8 value) ;
void    Temp_in_SetDriveMode(uint8 mode) ;
uint8   Temp_in_ReadDataReg(void) ;
uint8   Temp_in_Read(void) ;
uint8   Temp_in_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Temp_in_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Temp_in_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Temp_in_DM_RES_UP          PIN_DM_RES_UP
#define Temp_in_DM_RES_DWN         PIN_DM_RES_DWN
#define Temp_in_DM_OD_LO           PIN_DM_OD_LO
#define Temp_in_DM_OD_HI           PIN_DM_OD_HI
#define Temp_in_DM_STRONG          PIN_DM_STRONG
#define Temp_in_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Temp_in_MASK               Temp_in__MASK
#define Temp_in_SHIFT              Temp_in__SHIFT
#define Temp_in_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Temp_in_PS                     (* (reg8 *) Temp_in__PS)
/* Data Register */
#define Temp_in_DR                     (* (reg8 *) Temp_in__DR)
/* Port Number */
#define Temp_in_PRT_NUM                (* (reg8 *) Temp_in__PRT) 
/* Connect to Analog Globals */                                                  
#define Temp_in_AG                     (* (reg8 *) Temp_in__AG)                       
/* Analog MUX bux enable */
#define Temp_in_AMUX                   (* (reg8 *) Temp_in__AMUX) 
/* Bidirectional Enable */                                                        
#define Temp_in_BIE                    (* (reg8 *) Temp_in__BIE)
/* Bit-mask for Aliased Register Access */
#define Temp_in_BIT_MASK               (* (reg8 *) Temp_in__BIT_MASK)
/* Bypass Enable */
#define Temp_in_BYP                    (* (reg8 *) Temp_in__BYP)
/* Port wide control signals */                                                   
#define Temp_in_CTL                    (* (reg8 *) Temp_in__CTL)
/* Drive Modes */
#define Temp_in_DM0                    (* (reg8 *) Temp_in__DM0) 
#define Temp_in_DM1                    (* (reg8 *) Temp_in__DM1)
#define Temp_in_DM2                    (* (reg8 *) Temp_in__DM2) 
/* Input Buffer Disable Override */
#define Temp_in_INP_DIS                (* (reg8 *) Temp_in__INP_DIS)
/* LCD Common or Segment Drive */
#define Temp_in_LCD_COM_SEG            (* (reg8 *) Temp_in__LCD_COM_SEG)
/* Enable Segment LCD */
#define Temp_in_LCD_EN                 (* (reg8 *) Temp_in__LCD_EN)
/* Slew Rate Control */
#define Temp_in_SLW                    (* (reg8 *) Temp_in__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Temp_in_PRTDSI__CAPS_SEL       (* (reg8 *) Temp_in__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Temp_in_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Temp_in__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Temp_in_PRTDSI__OE_SEL0        (* (reg8 *) Temp_in__PRTDSI__OE_SEL0) 
#define Temp_in_PRTDSI__OE_SEL1        (* (reg8 *) Temp_in__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Temp_in_PRTDSI__OUT_SEL0       (* (reg8 *) Temp_in__PRTDSI__OUT_SEL0) 
#define Temp_in_PRTDSI__OUT_SEL1       (* (reg8 *) Temp_in__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Temp_in_PRTDSI__SYNC_OUT       (* (reg8 *) Temp_in__PRTDSI__SYNC_OUT) 


#if defined(Temp_in__INTSTAT)  /* Interrupt Registers */

    #define Temp_in_INTSTAT                (* (reg8 *) Temp_in__INTSTAT)
    #define Temp_in_SNAP                   (* (reg8 *) Temp_in__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Temp_in_H */


/* [] END OF FILE */
