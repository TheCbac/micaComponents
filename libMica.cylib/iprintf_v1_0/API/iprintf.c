/***************************************************************************//**
* \file iprintf.c
* \version 0.1.0
*
* \brief
*   Simple print functionality
*
* \date Date Created:  2017.12.19
* \date Last Modified: 2017.12.19
*
********************************************************************************
* \copyright
* Copyright 2017, MICA. All rights reserved.
*******************************************************************************/
#include "cytypes.h"
#include "`$INSTANCE_NAME`_iprintf.h"
#include "`$commName`.h"

/*******************************************************************************
* Function Name: iputc()
****************************************************************************//**
*
* \brief Function to print individial 
*
* \param pszFmt
*   Pointer to string, zero formatted. String to print out, accepts %d, %s, %x, %c
*
* \return
* None
 *******************************************************************************/
static inline void iputc(char8 ch)
{
	/* Function supplied as parameter */	
	`$commFunction`(ch);
}

/*******************************************************************************
* Function Name: change()
****************************************************************************//**
*
* \brief Changes the base to hex from decimal
*
* \param Index
*  new value
*
* \return
* None
 *******************************************************************************/
static inline uint8* change(uint32 Index)
{
    return (uint8*)("0123456789abcdef"+Index);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`()
****************************************************************************//**
*
* \brief Prints out the string
*
* \param pszFmt
*   Pointer to string, zero formatted. String to print out, accepts %d, %s, %x, %c
*
* \return
* None
 *******************************************************************************/
void `$INSTANCE_NAME`(char8 *pszFmt,...){
    #if (`$printActive`)
        uint8 *pszVal;
        uint32 iVal, xVal, i = 0, buffer[12], index = 1;
        uint8 cVal;
        uint32 *pArg;
        pArg =(uint32 *)&pszFmt;

        while(*pszFmt)
        {
            if('%' != *pszFmt)
            {
                iputc(*pszFmt);
                pszFmt++;
                continue;
            }
            pszFmt++;

            if(*pszFmt == 's')
            {
                pszVal = (uint8*)pArg[index++];
                for(; *pszVal != '\0'; pszVal++)
                    iputc(*pszVal);
                pszFmt++;
                continue;
            }
            if(*pszFmt == 'd')
            {
                iVal = pArg[index++];
                i = 0;
                do{
                    buffer[i++] = iVal % 10;
                    iVal /= 10;
                }while(iVal);
                while(i > 0)
                {
                    i--;
                    iputc(*change(buffer[i]));
                }
                pszFmt++;
                continue;
            }
            if(*pszFmt == 'c')
            {
                cVal = (uint8)pArg[index++];
                iputc(cVal);
                pszFmt++;
                continue;
            }
            if(*pszFmt == 'x')
            {
                xVal = pArg[index++];
                i = 0;
                do{
                    buffer[i++] = xVal % 16;
                    xVal /= 16;
                }while(xVal);
                if(i%2!=0)
                    buffer[i++]=0;
                if(i<2)
                    buffer[i++]=0;

                while(i > 0)
                {
                    i--;
                    iputc(*change(buffer[i]));
                }
                pszFmt++;
                continue;
            }
            if(pszFmt == '\0')
            {
                break;
            }
        }
    #else
        (void) pszFmt;
    #endif /* `$printActive` */
}

/* [] END OF FILE */
