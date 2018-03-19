/*
  <:copyright-BRCM:2015:proprietary:standard
  
     Copyright (c) 2015 Broadcom 
     All Rights Reserved
  
   This program is the proprietary software of Broadcom and/or its
   licensors, and may only be used, duplicated, modified or distributed pursuant
   to the terms and conditions of a separate, written license agreement executed
   between you and Broadcom (an "Authorized License").  Except as set forth in
   an Authorized License, Broadcom grants no license (express or implied), right
   to use, or waiver of any kind with respect to the Software, and Broadcom
   expressly reserves all rights in and to the Software and all intellectual
   property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU HAVE
   NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY
   BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.
  
   Except as expressly set forth in the Authorized License,
  
   1. This program, including its structure, sequence and organization,
      constitutes the valuable trade secrets of Broadcom, and you shall use
      all reasonable efforts to protect the confidentiality thereof, and to
      use this information only in connection with your use of Broadcom
      integrated circuit products.
  
   2. TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
      AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
      WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
      RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND
      ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT,
      FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR
      COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE
      TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF USE OR
      PERFORMANCE OF THE SOFTWARE.
  
   3. TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR
      ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL,
      INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY
      WAY RELATING TO YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN
      IF BROADCOM HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES;
      OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT ACTUALLY PAID FOR THE
      SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE LIMITATIONS
      SHALL APPLY NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF ANY
      LIMITED REMEDY.
  :>
*/


/** @file eagle_onu10g_dependencies.h
 * Dependencies to be provided by IP User
 */

#ifndef EAGLE_ONU10G_API_DEPENDENCIES_H
#define EAGLE_ONU10G_API_DEPENDENCIES_H

#include "eagle_onu10g_usr_includes.h"
#include "common/srds_api_err_code.h"
#include "eagle_onu10g_ipconfig.h"

/** Read a register from the currently selected Serdes IP Lane.
 * @param address Address of register to be read
 * @param *val value read out from the register
 * @return Error code generated by read function (returns ERR_CODE_NONE if no errors)
 */
err_code_t eagle_onu10g_pmd_rdt_reg(uint16_t address, uint16_t *val);

/** Write to a register from the currently selected Serdes IP Lane.
 * @param address Address of register to be written
 * @param val Value to be written to the register
 * @return Error code generated by write function (returns ERR_CODE_NONE if no errors)
 */
err_code_t eagle_onu10g_pmd_wr_reg(uint16_t address, uint16_t val);

/** Masked Register Write to the currently selected Serdes IP core/lane.
 * If using Serdes MDIO controller to access the registers, implement this function using eagle_onu10g_pmd_mdio_mwr_reg(..)
 *
 * If NOT using a Serdes MDIO controller or the Serdes PMI Masked write feature, please use the following code to
 * implement this function
 *
 *    eagle_onu10g_pmd_wr_reg(addr, ((eagle_onu10g_pmd_rdt_reg(addr) & ~mask) | (mask & (val << lsb))));
 *
 * @param addr Address of register to be written
 * @param mask 16-bit mask indicating the position of the field with bits of 1s
 * @param lsb  LSB of the field
 * @param val  16bit value to be written
 * @return Error code generated by write function (returns ERR_CODE_NONE if no errors)
 */
err_code_t eagle_onu10g_pmd_mwr_reg(uint16_t addr, uint16_t mask, uint8_t lsb, uint16_t val);


/** Write message to the logger with the designated verbose level.
 * Output is sent to stdout and a logfile
 * @param message_verbose_level   Verbose level for the current message
 * @param *format Format string as in printf
 * @param ... Additional variables used as in printf
 * @return Error code generated by function (returns ERR_CODE_NONE if no errors)
 */
int logger_write(int message_verbose_level, const char *format, ...);

/** Delay the execution of the code for atleast specified amount of time in nanoseconds.
 * This function is used ONLY for delays less than 1 microsecond, non-zero error code may be returned otherwise.
 * The user can implement this as an empty function if their register access latency exceeds 1 microsecond.
 * @param delay_ns Delay in nanoseconds
 * @return Error code generated by delay function (returns ERR_CODE_NONE if no errors)
 */
err_code_t eagle_onu10g_delay_ns(uint16_t delay_ns);

/** Delay the execution of the code for atleast specified amount of time in microseconds.
 * For longer delays, accuracy is required. When requested delay is > 100ms, the implemented delay is assumed
 * to be < 10% bigger than requested.
 * This function is used ONLY for delays greater than or equal to 1 microsecond.
 * @param delay_us Delay in microseconds
 * @return Error code generated by delay function (returns ERR_CODE_NONE if no errors)
 */
err_code_t eagle_onu10g_delay_us(uint32_t delay_us);

/** Delay the execution of the code for atleast specified amount of time in milliseconds.
 * For longer delays, accuracy is required. When requested delay is > 100ms, the implemented delay is assumed
 * to be < 10% bigger than requested.
 * This function is used ONLY for delays greater than or equal to 1 millisecond.
 * @param delay_ms Delay in milliseconds
 * @return Error code generated by delay function (returns ERR_CODE_NONE if no errors)
 */
err_code_t eagle_onu10g_delay_ms(uint32_t delay_ms);

/** Return the address of current selected Serdes IP Core.
 * @return the IP level address of the current core.
 */
uint8_t eagle_onu10g_get_core(void);

/** Return the address of current selected Serdes IP lane.
 * @return the IP level address of the current lane. 0 to N-1, for an N lane IP
 */
uint8_t eagle_onu10g_get_lane(void);


/** Return the address of current selected Serdes IP PLL.
 * @return the IP level address of the current PLL. 0 to N-1, for an N-PLL IP
 */
uint8_t eagle_onu10g_get_pll(void);

/** Set the address of current selected Serdes IP PLL.  Used in disgnoztic
 * and core-level management functions.
 * @return Any error code generated during execution; ERR_CODE NONE otherwise.
 */
err_code_t eagle_onu10g_set_pll(uint8_t pll_index);

/** Set the address of current selected Serdes IP lane.  Used in disgnoztic
 * and core-level management functions.
 * @return Any error code generated during execution; ERR_CODE NONE otherwise.
 */
err_code_t eagle_onu10g_set_lane(uint8_t lane_index);

/** Convert uC lane index.
* Convert uC lane index to system ID string.
* @param string a 16-byte output buffer to receive system ID
* @param uc_lane_idx uC lane index
* @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
* The textual identifier is pre-filled with a default:  implementors may
* safely return without modifying it if the default text is sufficient.
*/
err_code_t eagle_onu10g_uc_lane_idx_to_system_id(char string[16], uint8_t uc_lane_idx);


#endif