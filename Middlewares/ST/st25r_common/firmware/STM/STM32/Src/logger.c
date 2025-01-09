/******************************************************************************
  * @attention
  *
  * COPYRIGHT 2016 STMicroelectronics, all rights reserved
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied,
  * AND SPECIFICALLY DISCLAIMING THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
******************************************************************************/

/*
 *      PROJECT:   
 *      $Revision: $
 *      LANGUAGE:  ANSI C
 */

/*! \file
 *
 *  \author 
 *
 *  \brief Debug log output utility implementation.
 *
 */

/*
******************************************************************************
* INCLUDES
******************************************************************************
*/
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "logger.h"

/*
******************************************************************************
* LOCAL DEFINES
******************************************************************************
*/


#if (USE_LOGGER == LOGGER_ON)
#define MAX_HEX_STR         4
#define MAX_HEX_STR_LENGTH  128
char hexStr[MAX_HEX_STR][MAX_HEX_STR_LENGTH];
uint8_t hexStrIdx = 0;
#endif /* #if USE_LOGGER == LOGGER_ON */


#if (USE_LOGGER == LOGGER_OFF && !defined(HAL_UART_MODULE_ENABLED))
  #define UART_HandleTypeDef void
#endif


#define USART_TIMEOUT          1000

UART_HandleTypeDef *pLogUsart = 0;
uint8_t logUsartTx(uint8_t *data, uint16_t dataLen);

/**
  * @brief  This function initialize the UART handle.
  * @param  husart : already initialized handle to USART HW
  * @retval none :
  */
void logUsartInit(UART_HandleTypeDef *husart)
{
    pLogUsart = husart;
}

/**
  * @brief  This function Transmit data via USART
  * @param  data : data to be transmitted
  * @param  dataLen : length of data to be transmitted
  * @retval HAL_ERROR : in case the SPI HW is not initialized yet
  * @retval others : HAL status
  */
uint8_t logUsartTx(uint8_t *data, uint16_t dataLen)
{
  if(pLogUsart == 0)
  {
    return HAL_ERROR;
  }
  #if (USE_LOGGER == LOGGER_ON)
  {
    return HAL_UART_Transmit(pLogUsart, data, dataLen, USART_TIMEOUT);
  }
  #else
  {
    return HAL_OK;
  }
  #endif /* #if USE_LOGGER == LOGGER_ON */
}

int logUsart(const char* format, ...)
{
  #if (USE_LOGGER == LOGGER_ON)
  {
    #define LOG_BUFFER_SIZE 256
    char buf[LOG_BUFFER_SIZE];
    va_list argptr;
    va_start(argptr, format);
    int cnt = vsnprintf(buf, LOG_BUFFER_SIZE, format, argptr);
    va_end(argptr);
      
    /* */
    logUsartTx((uint8_t*)buf, strlen(buf));
    return cnt;
  }
  #else
  {
    return 0;
  }
  #endif /* #if USE_LOGGER == LOGGER_ON */
}

/* */

char* hex2Str(unsigned char * data, size_t dataLen)
{
#if (USE_LOGGER == LOGGER_ON)
    const char * hex = "0123456789ABCDEF";
    
    unsigned char * pin  = data;
    char *          pout = hexStr[hexStrIdx];

    uint8_t idx = hexStrIdx;

    if( dataLen > (MAX_HEX_STR_LENGTH/2) )
    {
        dataLen = (MAX_HEX_STR_LENGTH/2) - 1;
    }

    for(uint32_t i = 0; i < dataLen; i++)
    {
        *pout++ = hex[(*pin>>4) & 0x0F];
        *pout++ = hex[(*pin++)  & 0x0F];
    }
    *pout = 0;

    hexStrIdx++;
    hexStrIdx %= MAX_HEX_STR;
    
    return hexStr[idx];
#else
    return NULL;
#endif /* #if USE_LOGGER == LOGGER_ON */
}

