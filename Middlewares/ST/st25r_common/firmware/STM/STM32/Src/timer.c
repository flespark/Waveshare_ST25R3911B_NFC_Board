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
 *      PROJECT:   ST25R391x firmware
 *      $Revision: $
 *      LANGUAGE:  ANSI C
 */

/*! \file
 *
 *  \brief SW Timer implementation
 *
 *  \author
 *
 *   This module makes use of a System Tick in milliseconds and provides
 *   an abstraction for SW timers
 *
 */

/*
******************************************************************************
* INCLUDES
******************************************************************************
*/
#include "timer.h"
#include "rfal_platform.h"

/*
******************************************************************************
* LOCAL DEFINES
******************************************************************************
*/

/*
******************************************************************************
* LOCAL VARIABLES
******************************************************************************
*/

static uint32_t timerStopwatchTick;

/*
******************************************************************************
* GLOBAL FUNCTIONS
******************************************************************************
*/


/*******************************************************************************/
uint32_t timerCalculateTimer( uint16_t time )
{
  return (platformGetSysTick() + time);
}


/*******************************************************************************/
bool timerIsExpired( uint32_t timer )
{
  uint32_t uDiff;
  int32_t sDiff;
  
  uDiff = (timer - platformGetSysTick());   /* Calculate the diff between the timers */
  sDiff = uDiff;                            /* Convert the diff to a signed var      */
  /* Having done this has two side effects: 
   * 1) all differences smaller than -(2^31) ms (~25d) will become positive
   *    Signaling not expired: acceptable!
   * 2) Time roll-over case will be handled correctly: super!
   */
  
  /* Check if the given timer has expired already */
  if( sDiff < 0 )
  {
    return true;
  }
  
  return false;
}


/*******************************************************************************/
void timerDelay( uint16_t tOut )
{
  uint32_t t;
  
  /* Calculate the timer and wait blocking until is running */
  t = timerCalculateTimer( tOut );
  while( timerIsRunning(t) );
}


/*******************************************************************************/
void timerStopwatchStart( void )
{
  timerStopwatchTick = platformGetSysTick();
}


/*******************************************************************************/
uint32_t timerStopwatchMeasure( void )
{
  return (uint32_t)(platformGetSysTick() - timerStopwatchTick);
}

