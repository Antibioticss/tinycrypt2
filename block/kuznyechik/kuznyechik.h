/**
  Copyright © 2016 Odzhan. All Rights Reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met:

  1. Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

  3. The name of the author may not be used to endorse or promote products
  derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY AUTHORS "AS IS" AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */

#ifndef KUZNECHIK_H
#define KUZNECHIK_H

#include "../../macros.h"

#define KUZ_ENCRYPT 0
#define KUZ_DECRYPT 1

#define KUZ_ROUNDS 10

// cipher context
typedef struct {
	w128_t k[16];		// 10 round keys, array size increased to 16
  uint8_t pi[256];
  uint8_t pi_inv[256];
} kuz_key_t;

#ifdef __cplusplus
extern "C" {
#endif

void kuz_setkey(kuz_key_t *kuz, const uint8_t key[32]);
void kuz_setkeyx(kuz_key_t *kuz, const uint8_t key[32]);

void kuz_encrypt(kuz_key_t *key, void *blk, int enc);
void kuz_encryptx(kuz_key_t *key, void *blk, int enc);

#ifdef __cplusplus
}
#endif

#endif
