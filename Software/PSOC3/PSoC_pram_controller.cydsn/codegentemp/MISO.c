/*******************************************************************************
* File Name: MISO.c  
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
#include "MISO.h"


/*******************************************************************************
* Function Name: MISO_Write
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
void MISO_Write(uint8 value) 
{
    uint8 staticBits = (MISO_DR & (uint8)(~MISO_MASK));
    MISO_DR = staticBits | ((uint8)(value << MISO_SHIFT) & MISO_MASK);
}


/*******************************************************************************
* Function Name: MISO_SetDriveMode
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
void MISO_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(MISO_0, mode);
}


/*******************************************************************************
* Function Name: MISO_Read
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
*  Macro MISO_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 MISO_Read(void) 
{
    return (MISO_PS & MISO_MASK) >> MISO_SHIFT;
}


/*******************************************************************************
* Function Name: MISO_ReadDataReg
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
uint8 MISO_ReadDataReg(void) 
{
    return (MISO_DR & MISO_MASK) >> MISO_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(MISO_INTSTAT) 

    /*******************************************************************************
    * Function Name: MISO_ClearInterrupt
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
    uint8 MISO_ClearInterrupt(void) 
    {
        return (MISO_INTSTAT & MISO_MASK) >> MISO_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
