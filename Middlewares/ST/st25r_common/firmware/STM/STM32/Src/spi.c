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
 *  \brief SPI communication handling implementation.
 *
 */
 
/* Includes ------------------------------------------------------------------*/

#include "spi.h"

#define SPI_TIMEOUT   1000

SPI_HandleTypeDef *pSpi = NULL;


void spiInit(SPI_HandleTypeDef *hspi)
{
    pSpi = hspi;

    /* enabling SPI block will put SCLK to output, guaranteeing proper state when spiSelect() gets called */
    __HAL_SPI_ENABLE(hspi);
}

void spiSelect(GPIO_TypeDef *ssPort, uint16_t ssPin)
{
    HAL_GPIO_WritePin(ssPort, ssPin, GPIO_PIN_RESET);
}

void spiDeselect(GPIO_TypeDef *ssPort, uint16_t ssPin)
{
    HAL_GPIO_WritePin(ssPort, ssPin, GPIO_PIN_SET);
}

HAL_StatusTypeDef spiTxRx(const uint8_t *txData, uint8_t *rxData, uint16_t length)
{
    if(pSpi == NULL)
    {
        return HAL_ERROR;
    }
  
    if( (txData != NULL) && (rxData == NULL) )
    {
        return HAL_SPI_Transmit(pSpi, (uint8_t*)txData, length, SPI_TIMEOUT);
    }
    else if( (txData == NULL) && (rxData != NULL) )
    {
        return HAL_SPI_Receive(pSpi, rxData, length, SPI_TIMEOUT);
    }

    return HAL_SPI_TransmitReceive(pSpi, (uint8_t*)txData, rxData, length, SPI_TIMEOUT);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
