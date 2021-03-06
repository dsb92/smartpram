/*******************************************************************************
* File Name: isr_Receive_Data.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_ISR_isr_Receive_Data_H)
#define CY_ISR_isr_Receive_Data_H

#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isr_Receive_Data_Start(void) ;
void isr_Receive_Data_StartEx(cyisraddress address) ;
void isr_Receive_Data_Stop(void) ;

CY_ISR_PROTO(isr_Receive_Data_Interrupt);

void isr_Receive_Data_SetVector(cyisraddress address) ;
cyisraddress isr_Receive_Data_GetVector(void) ;

void isr_Receive_Data_SetPriority(uint8 priority) ;
uint8 isr_Receive_Data_GetPriority(void) ;

void isr_Receive_Data_Enable(void) ;
uint8 isr_Receive_Data_GetState(void) ;
void isr_Receive_Data_Disable(void) ;

void isr_Receive_Data_SetPending(void) ;
void isr_Receive_Data_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_Receive_Data ISR. */
#define isr_Receive_Data_INTC_VECTOR            ((reg16 *) isr_Receive_Data__INTC_VECT)

/* Address of the isr_Receive_Data ISR priority. */
#define isr_Receive_Data_INTC_PRIOR             ((reg8 *) isr_Receive_Data__INTC_PRIOR_REG)

/* Priority of the isr_Receive_Data interrupt. */
#define isr_Receive_Data_INTC_PRIOR_NUMBER      isr_Receive_Data__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_Receive_Data interrupt. */
#define isr_Receive_Data_INTC_SET_EN            ((reg8 *) isr_Receive_Data__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_Receive_Data interrupt. */
#define isr_Receive_Data_INTC_CLR_EN            ((reg8 *) isr_Receive_Data__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_Receive_Data interrupt state to pending. */
#define isr_Receive_Data_INTC_SET_PD            ((reg8 *) isr_Receive_Data__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_Receive_Data interrupt. */
#define isr_Receive_Data_INTC_CLR_PD            ((reg8 *) isr_Receive_Data__INTC_CLR_PD_REG)



#endif /* CY_ISR_isr_Receive_Data_H */


/* [] END OF FILE */
