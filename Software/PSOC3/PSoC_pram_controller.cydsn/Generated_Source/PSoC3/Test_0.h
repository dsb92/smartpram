/*******************************************************************************
* File Name: Test_0.h  
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

#if !defined(CY_PINS_Test_0_H) /* Pins Test_0_H */
#define CY_PINS_Test_0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Test_0_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Test_0_Write(uint8 value) ;
void    Test_0_SetDriveMode(uint8 mode) ;
uint8   Test_0_ReadDataReg(void) ;
uint8   Test_0_Read(void) ;
uint8   Test_0_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Test_0_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Test_0_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Test_0_DM_RES_UP          PIN_DM_RES_UP
#define Test_0_DM_RES_DWN         PIN_DM_RES_DWN
#define Test_0_DM_OD_LO           PIN_DM_OD_LO
#define Test_0_DM_OD_HI           PIN_DM_OD_HI
#define Test_0_DM_STRONG          PIN_DM_STRONG
#define Test_0_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Test_0_MASK               Test_0__MASK
#define Test_0_SHIFT              Test_0__SHIFT
#define Test_0_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Test_0_PS                     (* (reg8 *) Test_0__PS)
/* Data Register */
#define Test_0_DR                     (* (reg8 *) Test_0__DR)
/* Port Number */
#define Test_0_PRT_NUM                (* (reg8 *) Test_0__PRT) 
/* Connect to Analog Globals */                                                  
#define Test_0_AG                     (* (reg8 *) Test_0__AG)                       
/* Analog MUX bux enable */
#define Test_0_AMUX                   (* (reg8 *) Test_0__AMUX) 
/* Bidirectional Enable */                                                        
#define Test_0_BIE                    (* (reg8 *) Test_0__BIE)
/* Bit-mask for Aliased Register Access */
#define Test_0_BIT_MASK               (* (reg8 *) Test_0__BIT_MASK)
/* Bypass Enable */
#define Test_0_BYP                    (* (reg8 *) Test_0__BYP)
/* Port wide control signals */                                                   
#define Test_0_CTL                    (* (reg8 *) Test_0__CTL)
/* Drive Modes */
#define Test_0_DM0                    (* (reg8 *) Test_0__DM0) 
#define Test_0_DM1                    (* (reg8 *) Test_0__DM1)
#define Test_0_DM2                    (* (reg8 *) Test_0__DM2) 
/* Input Buffer Disable Override */
#define Test_0_INP_DIS                (* (reg8 *) Test_0__INP_DIS)
/* LCD Common or Segment Drive */
#define Test_0_LCD_COM_SEG            (* (reg8 *) Test_0__LCD_COM_SEG)
/* Enable Segment LCD */
#define Test_0_LCD_EN                 (* (reg8 *) Test_0__LCD_EN)
/* Slew Rate Control */
#define Test_0_SLW                    (* (reg8 *) Test_0__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Test_0_PRTDSI__CAPS_SEL       (* (reg8 *) Test_0__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Test_0_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Test_0__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Test_0_PRTDSI__OE_SEL0        (* (reg8 *) Test_0__PRTDSI__OE_SEL0) 
#define Test_0_PRTDSI__OE_SEL1        (* (reg8 *) Test_0__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Test_0_PRTDSI__OUT_SEL0       (* (reg8 *) Test_0__PRTDSI__OUT_SEL0) 
#define Test_0_PRTDSI__OUT_SEL1       (* (reg8 *) Test_0__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Test_0_PRTDSI__SYNC_OUT       (* (reg8 *) Test_0__PRTDSI__SYNC_OUT) 


#if defined(Test_0__INTSTAT)  /* Interrupt Registers */

    #define Test_0_INTSTAT                (* (reg8 *) Test_0__INTSTAT)
    #define Test_0_SNAP                   (* (reg8 *) Test_0__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Test_0_H */


/* [] END OF FILE */
