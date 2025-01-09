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
/*! \file
 *
 *  \author 
 *
 *  \brief SPI communication header file
 *
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __spi_H
#define __spi_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "main.h"


/*!
 *****************************************************************************
 *  \brief  Initialize SPI
 * 
 *  This function initialize the SPI handle.
 *
 *  \param[in] hspi : pointer to initialized SPI block
 *
 *****************************************************************************
 */   
void spiInit(SPI_HandleTypeDef *hspi);

/*!
 *****************************************************************************
 *  \brief  Set SPI CS line
 * 
 *  \param[in] ssPort : pointer CS gpio port
 *
 *  \param[in] ssPin : CS pin
 *
 *  \return : none
 *
 *****************************************************************************
 */
void spiSelect(GPIO_TypeDef *ssPort, uint16_t ssPin);

/*!
 *****************************************************************************
 *  \brief  Reset SPI CS line
 * 
 *  \param[in] ssPort : pointer CS gpio port
 *
 *  \param[in] ssPin : CS pin
 *
 *  \return : none
 *
 *****************************************************************************
 */
void spiDeselect(GPIO_TypeDef *ssPort, uint16_t ssPin);

/*!
 *****************************************************************************
 *  \brief  Transmit Receive data 
 * 
 *  This funtion transmits first no of "length" bytes from "txData" and tries 
 *  then to receive "length" bytes.
 * 
 *  \param[in] txData : pointer to buffer to be transmitted.
 *
 *  \param[out] rxData : pointer to buffer to be received.
 *
 *  \param[in] length : buffer length
 *
 *  \return : HAL error code
 *
 *****************************************************************************
 */
HAL_StatusTypeDef spiTxRx(const uint8_t *txData, uint8_t *rxData, uint16_t length);
   
#endif /*__spi_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
