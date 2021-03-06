/*******************************************************************************
* File Name: IRQ_Zigbee.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "IRQ_Zigbee.h"


/*******************************************************************************
* Function Name: IRQ_Zigbee_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void IRQ_Zigbee_Write(uint8 value) 
{
    uint8 staticBits = (IRQ_Zigbee_DR & (uint8)(~IRQ_Zigbee_MASK));
    IRQ_Zigbee_DR = staticBits | ((uint8)(value << IRQ_Zigbee_SHIFT) & IRQ_Zigbee_MASK);
}


/*******************************************************************************
* Function Name: IRQ_Zigbee_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void IRQ_Zigbee_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(IRQ_Zigbee_0, mode);
}


/*******************************************************************************
* Function Name: IRQ_Zigbee_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro IRQ_Zigbee_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 IRQ_Zigbee_Read(void) 
{
    return (IRQ_Zigbee_PS & IRQ_Zigbee_MASK) >> IRQ_Zigbee_SHIFT;
}


/*******************************************************************************
* Function Name: IRQ_Zigbee_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 IRQ_Zigbee_ReadDataReg(void) 
{
    return (IRQ_Zigbee_DR & IRQ_Zigbee_MASK) >> IRQ_Zigbee_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(IRQ_Zigbee_INTSTAT) 

    /*******************************************************************************
    * Function Name: IRQ_Zigbee_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 IRQ_Zigbee_ClearInterrupt(void) 
    {
        return (IRQ_Zigbee_INTSTAT & IRQ_Zigbee_MASK) >> IRQ_Zigbee_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
