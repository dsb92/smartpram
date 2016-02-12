/*******************************************************************************
* File Name: IRQ_Zigbee.h  
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

#if !defined(CY_PINS_IRQ_Zigbee_H) /* Pins IRQ_Zigbee_H */
#define CY_PINS_IRQ_Zigbee_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IRQ_Zigbee_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    IRQ_Zigbee_Write(uint8 value) ;
void    IRQ_Zigbee_SetDriveMode(uint8 mode) ;
uint8   IRQ_Zigbee_ReadDataReg(void) ;
uint8   IRQ_Zigbee_Read(void) ;
uint8   IRQ_Zigbee_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define IRQ_Zigbee_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define IRQ_Zigbee_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define IRQ_Zigbee_DM_RES_UP          PIN_DM_RES_UP
#define IRQ_Zigbee_DM_RES_DWN         PIN_DM_RES_DWN
#define IRQ_Zigbee_DM_OD_LO           PIN_DM_OD_LO
#define IRQ_Zigbee_DM_OD_HI           PIN_DM_OD_HI
#define IRQ_Zigbee_DM_STRONG          PIN_DM_STRONG
#define IRQ_Zigbee_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define IRQ_Zigbee_MASK               IRQ_Zigbee__MASK
#define IRQ_Zigbee_SHIFT              IRQ_Zigbee__SHIFT
#define IRQ_Zigbee_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IRQ_Zigbee_PS                     (* (reg8 *) IRQ_Zigbee__PS)
/* Data Register */
#define IRQ_Zigbee_DR                     (* (reg8 *) IRQ_Zigbee__DR)
/* Port Number */
#define IRQ_Zigbee_PRT_NUM                (* (reg8 *) IRQ_Zigbee__PRT) 
/* Connect to Analog Globals */                                                  
#define IRQ_Zigbee_AG                     (* (reg8 *) IRQ_Zigbee__AG)                       
/* Analog MUX bux enable */
#define IRQ_Zigbee_AMUX                   (* (reg8 *) IRQ_Zigbee__AMUX) 
/* Bidirectional Enable */                                                        
#define IRQ_Zigbee_BIE                    (* (reg8 *) IRQ_Zigbee__BIE)
/* Bit-mask for Aliased Register Access */
#define IRQ_Zigbee_BIT_MASK               (* (reg8 *) IRQ_Zigbee__BIT_MASK)
/* Bypass Enable */
#define IRQ_Zigbee_BYP                    (* (reg8 *) IRQ_Zigbee__BYP)
/* Port wide control signals */                                                   
#define IRQ_Zigbee_CTL                    (* (reg8 *) IRQ_Zigbee__CTL)
/* Drive Modes */
#define IRQ_Zigbee_DM0                    (* (reg8 *) IRQ_Zigbee__DM0) 
#define IRQ_Zigbee_DM1                    (* (reg8 *) IRQ_Zigbee__DM1)
#define IRQ_Zigbee_DM2                    (* (reg8 *) IRQ_Zigbee__DM2) 
/* Input Buffer Disable Override */
#define IRQ_Zigbee_INP_DIS                (* (reg8 *) IRQ_Zigbee__INP_DIS)
/* LCD Common or Segment Drive */
#define IRQ_Zigbee_LCD_COM_SEG            (* (reg8 *) IRQ_Zigbee__LCD_COM_SEG)
/* Enable Segment LCD */
#define IRQ_Zigbee_LCD_EN                 (* (reg8 *) IRQ_Zigbee__LCD_EN)
/* Slew Rate Control */
#define IRQ_Zigbee_SLW                    (* (reg8 *) IRQ_Zigbee__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IRQ_Zigbee_PRTDSI__CAPS_SEL       (* (reg8 *) IRQ_Zigbee__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IRQ_Zigbee_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IRQ_Zigbee__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IRQ_Zigbee_PRTDSI__OE_SEL0        (* (reg8 *) IRQ_Zigbee__PRTDSI__OE_SEL0) 
#define IRQ_Zigbee_PRTDSI__OE_SEL1        (* (reg8 *) IRQ_Zigbee__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IRQ_Zigbee_PRTDSI__OUT_SEL0       (* (reg8 *) IRQ_Zigbee__PRTDSI__OUT_SEL0) 
#define IRQ_Zigbee_PRTDSI__OUT_SEL1       (* (reg8 *) IRQ_Zigbee__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IRQ_Zigbee_PRTDSI__SYNC_OUT       (* (reg8 *) IRQ_Zigbee__PRTDSI__SYNC_OUT) 


#if defined(IRQ_Zigbee__INTSTAT)  /* Interrupt Registers */

    #define IRQ_Zigbee_INTSTAT                (* (reg8 *) IRQ_Zigbee__INTSTAT)
    #define IRQ_Zigbee_SNAP                   (* (reg8 *) IRQ_Zigbee__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins IRQ_Zigbee_H */


/* [] END OF FILE */
