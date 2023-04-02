/********!
 * @file  crcs.hpp
 * 
 * @author
 * 	Evan Clegern <evanclegern.work@gmail.com>
 * 
 * @date
 * 	1 April 2023
 * 
 * @brief
 * 	Provides two globally-available CRC functions, CRC-16-CCITT and
 *	CRC-32-POSIX, which take pointers to any arbitrary set of data.
 * 
 * @copyright
 * 	Copyright (C) 2023 Evan Clegern
 * 
 * 	This program is free software: you can redistribute it and/or modify
 * 	it under the terms of the GNU General Public License, as published by
 * 	the Free Software Foundation, version 3 of the License.
 * 
 * 	This program is distributed in the hope that it will be useful,
 * 	but WITHOUT ANY WARRANTY; without even the implied warranty of
 * 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * 	GNU General Public License for more details.
 * 
 * 	You should have received a copy of the GNU General Public License
 * 	along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 ********/

#ifndef anoptamin_crcs
#define anoptamin_crcs

#include "base.hpp"

//! Perform a cyclic redundancy check for the data in accordance to CRC-16-CCITT.
LIBANOP_FUNC_INPUTS_NONNULL LIBANOP_FUNC_FIX_STATE uint16_t getCRC16(void* data, size_t size) {
	// Meets the CRCCALC.com CRC-16/AUG-CCITT operation outputs.
	uint16_t tmp = 0x1D0F;
	for (size_t i = 0; i < size; i++) {
		uint8_t byte = ((uint8_t*)data)[i];
		for (int8_t j = 7; j >= 0; j--) {
			uint8_t inbit = (byte & (1 << j));
			uint16_t polybit = (tmp & 0x8000);
			tmp <<= 1;
			if (inbit != polybit) {
				tmp ^= 0x1021;
			}
		}
	}
	
	return tmp;
}

//! Perform a cyclic redundancy check for the data in accordance to CRC-32-POSIX.
LIBANOP_FUNC_INPUTS_NONNULL LIBANOP_FUNC_FIX_STATE uint32_t getCRC32(void* data, size_t size) {
	// Meets the CRCCALC.com CRC-32/POSIX operation outputs.
	uint32_t tmp = 0;
	for (size_t i = 0; i < size; i++) {
		uint8_t byte = ((uint8_t*)data)[i];
		for (int8_t j = 7; j >= 0; j--) {
			uint8_t inbit = byte & (1 << j);
			uint32_t polybit = (tmp & 0x80000000);
			tmp <<= 1;
			if (inbit != polybit) {
				tmp ^= 0x04C11DB7;
			}
		}
	}
	
	return ~tmp;
}

#endif
