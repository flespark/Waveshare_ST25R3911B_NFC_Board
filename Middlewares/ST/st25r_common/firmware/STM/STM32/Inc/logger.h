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
 *  \brief Serial output log declaration file
 *
 */

/*!
 *
 * This driver provides a printf-like way to output log messages
 * via the UART interface. It makes use of the uart driver.
 *
 */

#ifndef LOGGER_H
#define LOGGER_H

/*
******************************************************************************
* INCLUDES
******************************************************************************
*/
#include <string.h>
#include "main.h"


#if (USE_LOGGER == LOGGER_OFF && !defined(HAL_UART_MODULE_ENABLED))
  #define UART_HandleTypeDef void
#endif

/*
******************************************************************************
* DEFINES
******************************************************************************
*/
#define LOGGER_ON   1
#define LOGGER_OFF  0

/*!
 *****************************************************************************
 *  \brief  Writes out a formated string via UART interface
 *
 *  This function is used to write a formated string via the UART interface.
 *
 *****************************************************************************
 */
extern void logUsartInit(UART_HandleTypeDef *husart);

/*!
 *****************************************************************************
 *  \brief  Writes out a formated string via UART interface
 *
 *  This function is used to write a formated string via the UART interface.
 *
 *****************************************************************************
 */
extern int logUsart(const char* format, ...);

/*!
 *****************************************************************************
 *  \brief  helper to convert hex data into formated string
 *
 *  \param[in] data : pointer to buffer to be dumped.
 *
 *  \param[in] dataLen : buffer length
 *
 *  \return hex formated string
 *
 *****************************************************************************
 */
extern char* hex2Str(unsigned char * data, size_t dataLen);

#endif /* LOGGER_H */

