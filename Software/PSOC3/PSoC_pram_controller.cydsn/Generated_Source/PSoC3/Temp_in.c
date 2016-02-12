/*******************************************************************************
* File Name: Temp_in.c  
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
#include "Temp_in.h"


/*******************************************************************************
* Function Name: Temp_in_Write
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
void Temp_in_Write(uint8 value) 
{
    uint8 staticBits = (Temp_in_DR & (uint8)(~Temp_in_MASK));
    Temp_in_DR = staticBits | ((uint8)(value << Temp_in_SHIFT) & Temp_in_MASK);
}


/*******************************************************************************
* Function Name: Temp_in_SetDriveMode
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
void Temp_in_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Temp_in_0, mode);
}


/*******************************************************************************
* Function Name: Temp_in_Read
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
*  Macro Temp_in_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Temp_in_Read(void) 
{
    return (Temp_in_PS & Temp_in_MASK) >> Temp_in_SHIFT;
}


/*******************************************************************************
* Function Name: Temp_in_ReadDataReg
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
uint8 Temp_in_ReadDataReg(void) 
{
    return (Temp_in_DR & Temp_in_MASK) >> Temp_in_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Temp_in_INTSTAT) 

    /*******************************************************************************
    * Function Name: Temp_in_ClearInterrupt
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
    uint8 Temp_in_ClearInterrupt(void) 
    {
        return (Temp_in_INTSTAT & Temp_in_MASK) >> Temp_in_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
