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

#ifndef _KeccakDuplexWidth200_h_
#define _KeccakDuplexWidth200_h_

#include "KeccakDuplex-common.h"

#ifndef KeccakP200_excluded
    #include "KeccakP-200-SnP.h"
    KCP_DeclareDuplexStructure(KeccakWidth200, KeccakP200_stateSizeInBytes, KeccakP200_stateAlignment)
    KCP_DeclareDuplexFunctions(KeccakWidth200)
#endif

#endif
