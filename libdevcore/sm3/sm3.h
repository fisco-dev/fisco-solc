/*
	This file is part of fisco-solc.

	fisco-solc is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	fisco-solc is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with fisco-solc.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * @file: sm3.h
 * @author: websterchen
 * 
 * @date: 2018
 */
#ifndef SM3_H
#define SM3_H


/**
* \brief          SM3 context structure
*/
typedef struct
{
	unsigned long total[2];     /*!< number of bytes processed  */
	unsigned long state[8];     /*!< intermediate digest state  */
	unsigned char buffer[64];   /*!< data block being processed */

	unsigned char ipad[64];     /*!< HMAC: inner padding        */
	unsigned char opad[64];     /*!< HMAC: outer padding        */

}
sm3_context;

#ifdef __cplusplus
extern "C" {
#endif

	void sm3_starts(sm3_context *ctx);

	void sm3_update(sm3_context *ctx, unsigned char *input, int ilen);

	void sm3_finish(sm3_context *ctx, unsigned char output[32]);

	void SM3(unsigned char *input, int ilen,
		unsigned char output[32]);
#ifdef __cplusplus
}
#endif

#endif /* sm3.h */