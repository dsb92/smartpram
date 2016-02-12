/*******************************************************************************
* File Name: Mobile_motor.c  
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
#include "Mobile_motor.h"


/*******************************************************************************
* Function Name: Mobile_motor_Write
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
void Mobile_motor_Write(uint8 value) 
{
    uint8 staticBits = (Mobile_motor_DR & (uint8)(~Mobile_motor_MASK));
    Mobile_motor_DR = staticBits | ((uint8)(value << Mobile_motor_SHIFT) & Mobile_motor_MASK);
}


/*******************************************************************************
* Function Name: Mobile_motor_SetDriveMode
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
void Mobile_motor_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Mobile_motor_0, mode);
}


/*******************************************************************************
* Function Name: Mobile_motor_Read
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
*  Macro Mobile_motor_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Mobile_motor_Read(void) 
{
    return (Mobile_motor_PS & Mobile_motor_MASK) >> Mobile_motor_SHIFT;
}


/*******************************************************************************
* Function Name: Mobile_motor_ReadDataReg
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
uint8 Mobile_motor_ReadDataReg(void) 
{
    return (Mobile_motor_DR & Mobile_motor_MASK) >> Mobile_motor_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Mobile_motor_INTSTAT) 

    /*******************************************************************************
    * Function Name: Mobile_motor_ClearInterrupt
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
    uint8 Mobile_motor_ClearInterrupt(void) 
    {
        return (Mobile_motor_INTSTAT & Mobile_motor_MASK) >> Mobile_motor_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
