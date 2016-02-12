/*******************************************************************************
* File Name: Signal_out.c  
* Version 1.70
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "Signal_out.h"


/*******************************************************************************
* Function Name: Signal_out_Write
********************************************************************************
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  void 
*  
*******************************************************************************/
void Signal_out_Write(uint8 value) 
{
    uint8 staticBits = Signal_out_DR & ~Signal_out_MASK;
    Signal_out_DR = staticBits | ((value << Signal_out_SHIFT) & Signal_out_MASK);
}


/*******************************************************************************
* Function Name: Signal_out_SetDriveMode
********************************************************************************
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  void
*
*******************************************************************************/
void Signal_out_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Signal_out_0, mode);
}


/*******************************************************************************
* Function Name: Signal_out_Read
********************************************************************************
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro Signal_out_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Signal_out_Read(void) 
{
    return (Signal_out_PS & Signal_out_MASK) >> Signal_out_SHIFT;
}


/*******************************************************************************
* Function Name: Signal_out_ReadDataReg
********************************************************************************
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 Signal_out_ReadDataReg(void) 
{
    return (Signal_out_DR & Signal_out_MASK) >> Signal_out_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Signal_out_INTSTAT) 

    /*******************************************************************************
    * Function Name: Signal_out_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  void 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 Signal_out_ClearInterrupt(void) 
    {
        return (Signal_out_INTSTAT & Signal_out_MASK) >> Signal_out_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */ 
