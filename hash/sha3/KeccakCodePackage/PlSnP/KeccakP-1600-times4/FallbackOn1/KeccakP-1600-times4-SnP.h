/*
Implementation by the Keccak, Keyak and Ketje Teams, namely, Guido Bertoni,
Joan Daemen, Michaël Peeters, Gilles Van Assche and Ronny Van Keer, hereby
denoted as "the implementer".

For more information, feedback or questions, please refer to our websites:
http://keccak.noekeon.org/
http://keyak.noekeon.org/
http://ketje.noekeon.org/

To the extent possible under law, the implementer has waived all copyright
and related or neighboring rights to the source code in this file.
http://creativecommons.org/publicdomain/zero/1.0/
*/

#ifndef _KeccakP_1600_times4_SnP_h_
#define _KeccakP_1600_times4_SnP_h_

/** For the documentation, see PlSnP-documentation.h.
 */

#include "KeccakP-1600-SnP.h"

#define KeccakP1600times4_implementation        "fallback on serial implementation (" KeccakP1600_implementation ")"
#define KeccakP1600times4_statesSizeInBytes     (((KeccakP1600_stateSizeInBytes+(KeccakP1600_stateAlignment-1))/KeccakP1600_stateAlignment)*KeccakP1600_stateAlignment*4)
#define KeccakP1600times4_statesAlignment       KeccakP1600_stateAlignment

void KeccakP1600times4_StaticInitialize( void );
void KeccakP1600times4_InitializeAll(void *states);
void KeccakP1600times4_AddByte(void *states, unsigned int instanceIndex, unsigned char data, unsigned int offset);
void KeccakP1600times4_AddBytes(void *states, unsigned int instanceIndex, const unsigned char *data, unsigned int offset, unsigned int length);
void KeccakP1600times4_AddLanesAll(void *states, const unsigned char *data, unsigned int laneCount, unsigned int laneOffset);
void KeccakP1600times4_OverwriteBytes(void *states, unsigned int instanceIndex, const unsigned char *data, unsigned int offset, unsigned int length);
void KeccakP1600times4_OverwriteLanesAll(void *states, const unsigned char *data, unsigned int laneCount, unsigned int laneOffset);
void KeccakP1600times4_OverwriteWithZeroes(void *states, unsigned int instanceIndex, unsigned int byteCount);
void KeccakP1600times4_PermuteAll_4rounds(void *states);
void KeccakP1600times4_PermuteAll_6rounds(void *states);
void KeccakP1600times4_PermuteAll_12rounds(void *states);
void KeccakP1600times4_PermuteAll_24rounds(void *states);
void KeccakP1600times4_ExtractBytes(const void *states, unsigned int instanceIndex, unsigned char *data, unsigned int offset, unsigned int length);
void KeccakP1600times4_ExtractLanesAll(const void *states, unsigned char *data, unsigned int laneCount, unsigned int laneOffset);
void KeccakP1600times4_ExtractAndAddBytes(const void *states, unsigned int instanceIndex,  const unsigned char *input, unsigned char *output, unsigned int offset, unsigned int length);
void KeccakP1600times4_ExtractAndAddLanesAll(const void *states, const unsigned char *input, unsigned char *output, unsigned int laneCount, unsigned int laneOffset);

#endif
