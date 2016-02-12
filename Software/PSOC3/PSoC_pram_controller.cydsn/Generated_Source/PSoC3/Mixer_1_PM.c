/*******************************************************************************
* File Name: Mixer_1_PM.c  
* Version 1.91
*
* Description:
*  This file provides the power manager source code to the API for 
*  the MIXER component.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Mixer_1.h"

static Mixer_1_BACKUP_STRUCT  Mixer_1_backup =
{
    Mixer_1_DISABLED
};


/*******************************************************************************
* Function Name: Mixer_1_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*  
* Parameters:  
*  void.
*
* Return: 
*  void.
*
*******************************************************************************/
void Mixer_1_SaveConfig(void) 
{
    /* Nothing to save before entering into sleep mode as all the registers used 
       here are retension registers. */
}


/*******************************************************************************
* Function Name: Mixer_1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void.
*
* Return: 
*  void
*
*******************************************************************************/
void Mixer_1_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************
* Function Name: Mixer_1_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  Mixer_1_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void Mixer_1_Sleep(void) 
{
    /* Save TIA enable state */
    if(Mixer_1_ACT_PWR_EN == (Mixer_1_PM_ACT_CFG_REG & Mixer_1_ACT_PWR_EN))
    {
        /* Component is enabled */
        Mixer_1_backup.enableState = Mixer_1_ENABLED;
    }
    else
    {
        /* Component is disabled */
        Mixer_1_backup.enableState = Mixer_1_DISABLED;
    }

    /* Stop the configuration */
    Mixer_1_Stop();

    /* Saves the user configuration */
    Mixer_1_SaveConfig();
}


/*******************************************************************************
* Function Name: Mixer_1_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  void
*
* Global variables:
*  Mixer_1_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void Mixer_1_Wakeup(void) 
{
    /* Restore the user configuration */
    Mixer_1_RestoreConfig();
    
    /* Enable's the component operation */
    if(Mixer_1_backup.enableState == Mixer_1_ENABLED)
    {
        Mixer_1_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
