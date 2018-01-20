/**
  ******************************************************************************
  * @file    lib_NDEF_Email.h
  * @author  MMY Application Team
  * @version $Revision: 1329 $
  * @date    $Date: 2015-11-05 10:34:25 +0100 (Thu, 05 Nov 2015) $
  * @brief   This file help to manage Email NDEF file.
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under ST MYLIBERTY SOFTWARE LICENSE AGREEMENT (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/myliberty  
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied,
  * AND SPECIFICALLY DISCLAIMING THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LIB_NDEF_EMAIL_H
#define __LIB_NDEF_EMAIL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lib_NDEF.h"

/* "mailto:customer.service@st.com?subject=M24SR S/N 754FHFGJF46G329 WARRANTY&body=this is an auomatic warranty activation email" */

typedef struct
{
  char EmailAdd[64];
  char Subject[100];
  char Message[2000];
  char Information[400];
}sEmailInfo;

/* Struct defined in lib_NDEF.h */
typedef struct sRecordInfo sRecordInfo_email;

uint16_t NDEF_ReadEmail( sRecordInfo_email *pRecordStruct, sEmailInfo *pEmailStruct );
uint16_t NDEF_WriteEmail( sEmailInfo *pEmailStruct );
void NDEF_PrepareEmailMessage( sEmailInfo *pEmailStruct, uint8_t *pNDEFMessage, uint16_t *size );

#ifdef __cplusplus
}
#endif

#endif /* __LIB_NDEF_EMAIL_H */

/******************* (C) COPYRIGHT 2015 STMicroelectronics *****END OF FILE****/
