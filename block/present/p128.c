/**
  Copyright © 2017 Odzhan. All Rights Reserved.

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

#include "present.h"

uint8_t sub_byte(uint8_t x)
{
  const uint8_t sbox[16] =
  { 0xc, 0x5, 0x6, 0xb, 0x9, 0x0, 0xa, 0xd,
    0x3, 0xe, 0xf, 0x8, 0x4, 0x7, 0x1, 0x2 };

  return (sbox[(x & 0xF0) >> 4] << 4) |
          sbox[(x & 0x0F)];
}

#ifndef SINGLE

void present128_setkey(present_ctx *ctx, void *key) {
  w64_t  k1, k0, t;
  int    rnd;
  w128_t *k=(w128_t*)key;

  // load 128-bit key
  k0.q = k->q[0]; k1.q = k->q[1];

  for (rnd=0; rnd<PRESENT_RNDS; rnd++)
  {
    // save round key
    ctx->key[rnd] = k1.q;

    // create next
    k0.q   ^= (rnd + rnd) + 2;
    t.q     = k1.q;

    k1.q = (k1.q << 61) | (k0.q >> 3);
    k0.q = (k0.q << 61) | ( t.q >> 3);

    k1.q    = ROTL64(k1.q, 8);
    k1.b[0] = sub_byte(k1.b[0]);
    k1.q    = ROTR64(k1.q, 8);
  }
}

void present128_encrypt(present_ctx *ctx, void *data) {
  w64_t p, t;
  int   i, j, r;
  w64_t *x=(w64_t*)data;

  p.q = x->q;

  for (i=0; i<PRESENT_RNDS-1; i++) {
    // apply key whitening
    p.q ^= ctx->key[i];
    // apply non-linear operation
    // replace 16 nibbles with sbox values
    for (j=0; j<8; j++) {
      p.b[j] = sub_byte(p.b[j]);
    }
    // apply linear operation
    // bit permutation
    t.q = 0;
    r   = 0x30201000;
    for (j=0; j<64; j++) {
      // test bit at j'th position and shift left
      t.q |= ((p.q >> j) & 1) << (r & 255);
      r = ROTR32(r+1, 8);
    }
    p.q = t.q;
  }
  // post whitening
  p.q ^= ctx->key[PRESENT_RNDS-1];
  x->q = p.q;
}

#else

void present128_encryptx(void *key, void *data) {
  w64_t  p, t, k0, k1;
  int    i, j, r;

  w128_t *k=(w128_t*)key;
  w64_t  *x=(w64_t*)data;

  // load 128-bit key
  k0.q = k->q[0]; k1.q = k->q[1];

  // load 64-bit plain text
  p.q = x->q;

  for (i=0; i<PRESENT_RNDS-1; i++) {
    // apply key whitening
    p.q ^= k1.q;
    // apply non-linear operation
    // replace 16 nibbles with sbox values
    for (j=0; j<8; j++) {
      p.b[j] = sub_byte(p.b[j]);
    }
    // apply linear operation
    // bit permutation
    t.q = 0;
    r   = 0x30201000;

    for (j=0; j<64; j++) {
      t.q |= ((p.q >> j) & 1) << (r & 255);
      r = ROTR32(r+1, 8);
    }
    p.q = t.q;

    // create next round key
    k0.q ^= (i + i) + 2;
    t.q   = k1.q;

    // rotate
    k1.q = (k1.q << 61) | (k0.q >> 3);
    k0.q = (k0.q << 61) | ( t.q >> 3);

    //
    k1.q    = ROTL64(k1.q, 8);
    k1.b[0] = sub_byte(k1.b[0]);
    k1.q    = ROTR64(k1.q, 8);
  }
  // post whitening and save
  x->q = (p.q ^ k1.q);
}

#endif
