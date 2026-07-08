
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include "rot.h"
#define h_VAL    0x77EBBAAC0088678F
#define PRM1_VAL 0xC6F67EDD9087AA88
#define PRM2_VAL 0xF8C8EE9D2007AB08
#define PRM3_VAL 0x67760099FFBE789A
#define LOOP_ITERS_MAX 14
#ifdef _DEBUG
    #include <stdio.h>
    #define LOG(ms,...) printf(ms,##__VA_ARGS__) 
#else
    #define LOG(ms,...)
#endif
typedef unsigned __int128 uint128_t;

void __hash_word(uint64_t word, uint128_t* h, uint64_t* PRM1, uint64_t* PRM2,
                        uint64_t* PRM3, uint64_t seed) {
    if (*h == 0) *h = (uint128_t)h_VAL << 64 | h_VAL;
    if (*PRM1 == 0) *PRM1 = PRM1_VAL;
    if (*PRM2 == 0) *PRM2 = PRM2_VAL;
    if (*PRM3 == 0) *PRM3 = PRM3_VAL;
    if (seed == 0) seed ^= ~((PRM1_VAL) ^ ~(PRM2_VAL >> 32)) ^ (uint64_t)(*h);
    uint64_t h_lo = (uint64_t)(*h);
    uint64_t h_hi = (uint64_t)(*h >> 64);
    h_lo ^= ~((__rtpatt(*PRM1) ^ ~(*PRM2 & (*PRM3 >> (*PRM2 & 33)))) ^ 
              (word >> ((word ^ (*PRM1 >> 37)) & 63)));
    h_hi ^= ~((__rtpatt(*PRM2) ^ ~(*PRM3 & (*PRM1 >> (*PRM3 & 33)))) ^ 
              (word >> ((word ^ (*PRM2 >> 37)) & 63)));
    word ^= (h_lo ^ (__rtpatt((*PRM1 ^ ~(word >> (*PRM2 & 63))))));
    word ^= (h_hi ^ (__rtpatt((*PRM2 ^ ~(word >> (*PRM3 & 63))))));
    uint64_t c = 2;
    uint32_t w  = (uint32_t)word;
    uint32_t w2 = (uint32_t)(word >> 32);
    w ^= (w2 >> (*PRM1 & 63));
    w ^= ~((w2 >> (((uint8_t)word ^ (~(uint8_t)h_lo)) & 63)) ^
           ((w2 >> (*PRM2 & 63)) ^ (w >> (*PRM1 & 63))));
    for (; c != 0; c--) {
        w ^= ((~w) & (w2 ^ ~((*PRM1 >> 47)) ^ seed));
        w2 ^= w ^ (*PRM1 ^ (w2 ^ ~(w & (w >> 27))));
        w ^= w2;
        word ^= (h_lo ^ (__rtpatt((*PRM1 ^ ~(word >> (*PRM2 & 63))))));
        word ^= (h_hi ^ (__rtpatt((*PRM2 ^ ~(word >> (*PRM3 & 63)))))); 
        _Bool d = 0;
        for (int i = 0; i < (int)(w & LOOP_ITERS_MAX); i++) {
            if (d) {
                h_lo = __rotl64(h_lo, (w ^ (i & ~w)));
                h_hi = __rotr64(h_hi, (w ^ (i & ~w)));
            } else {
                h_lo = __rotr64(h_lo, (w ^ (i & ~w)));
                h_hi = __rotl64(h_hi, (w ^ (i & ~w)));
            }
            d = !d;
            word ^= (h_lo ^ (__rtpatt((*PRM1 ^ ~(word >> (*PRM2 & 63))))));
            word ^= (h_hi ^ (__rtpatt((*PRM2 ^ ~(word >> (*PRM3 & 63))))));
            w ^= (w2 >> (*PRM1 & 63));
            w ^= ~((w2 >> (((uint8_t)word ^ (~(uint8_t)h_lo)) & 63)) ^
                   ((w2 >> (*PRM2 & 63)) ^ (w >> (*PRM1 & 63))));
        }
        h_lo ^= w;
        h_lo = __rtpatt(h_lo);
        h_hi ^= w2;
        h_hi = __rtpatt(h_hi);
        *PRM1 ^= ~(seed ^ ~((*PRM2 & (*PRM3 ^ (*PRM1 >> 20)))));
        *PRM2 ^= ~(seed ^ w);
        *PRM3 ^= h_lo ^ h_hi;
        if (h_lo == 0) h_lo = h_VAL;
        if (h_hi == 0) h_hi = h_VAL;
        if (*PRM1 == 0) *PRM1 = PRM1_VAL;
        if (*PRM2 == 0) *PRM2 = PRM2_VAL;
        if (*PRM3 == 0) *PRM3 = PRM3_VAL;
        word ^= (h_lo ^ (__rtpatt((*PRM1 ^ ~(word >> (*PRM2 & 63))))));
        word ^= (h_hi ^ (__rtpatt((*PRM2 ^ ~(word >> (*PRM3 & 63))))));
        w ^= (w2 >> (*PRM1 & 63));
        w ^= ~((w2 >> (((uint8_t)word ^ (~(uint8_t)h_lo)) & 63)) ^
               ((w2 >> (*PRM2 & 63)) ^ (w >> (*PRM1 & 63))));
    }
    *h = ((uint128_t)h_hi << 64) | h_lo;
}
uint64_t __Limbo64(void* data,size_t len,size_t seed,uint64_t salt) {
    __uint128_t h = h_VAL;
    uint64_t PRM1 = PRM1_VAL;
    uint64_t PRM2 = PRM2_VAL;
    uint64_t PRM3 = PRM3_VAL;
    h ^= seed;
    PRM1 ^= seed;
    PRM2 ^= seed;
    PRM3 ^= seed;
    if (h == 0) h = h_VAL;
    if (PRM1 == 0) PRM1 = PRM1_VAL;
    if (PRM2 == 0) PRM2 = PRM2_VAL;
    if (PRM3 == 0) PRM3 = PRM3_VAL;
    size_t full = len & ~7ULL;
    size_t tail = len & 7ULL;
    for (size_t off = 0; off < full; off += 8) {
        uint64_t word;
        memcpy(&word, (uint8_t*)data + off, 8);
        __hash_word(word, &h, &PRM1, &PRM2, &PRM3, seed);
    }
    if (tail) {
        uint8_t buf[8] = {0};
        memcpy(buf, (uint8_t*)data + full, tail);
        size_t need = 8 - tail;
        memcpy(buf + tail, data, need);
        uint64_t word;
        memcpy(&word, buf, 8);
        __hash_word(word, &h, &PRM1, &PRM2, &PRM3, seed);
    }
    if (h == 0) h = h_VAL;
    if (PRM1 == 0) PRM1 = PRM1_VAL;
    if (PRM2 == 0) PRM2 = PRM2_VAL;
    if (PRM3 == 0) PRM3 = PRM3_VAL;
    if (seed == 0) seed ^= ~((PRM1_VAL) ^ ~(PRM2_VAL >> 32)) ^ h;
    PRM1 ^= (PRM2 ^ (seed ^ (len ^ h)));
    PRM2 = ((PRM2 >> 45) ^ PRM3);
    h ^= PRM1;
    h *= PRM2;
    h ^= PRM3;
    uint64_t slt2 = (salt ^ ~(h & (PRM1 ^ ~PRM2)));
    __hash_word(seed, &h, &PRM1, &PRM2, &PRM3,slt2);
    if (h == 0) h = h_VAL;
    if (PRM1 == 0) PRM1 = PRM1_VAL;
    if (PRM2 == 0) PRM2 = PRM2_VAL;
    if (PRM3 == 0) PRM3 = PRM3_VAL;
    h ^= ~(slt2 ^ (salt & PRM1));
    PRM1 ^= slt2;
    PRM2 ^= h;
    PRM3 ^= salt;
    for (int i = 0;i <3;i++) h = __rtpatt(h);
    PRM2 |= (PRM3 ^ (seed ^ len));
    h ^= ~((h ^ PRM3) & PRM2);
    h ^= ~((h ^ slt2) >> 
    (((PRM3 ^ ~(slt2) ^ (PRM1 ^ PRM2)) >> 
    ((h ^ (slt2 ^ (salt >> 26))) & 33 ))));
    h ^= ~((h ^ PRM1) | ((PRM2 ^ slt2) ^ (PRM3 ^ ~((salt) ^ (salt >> 32)))));
    return (uint64_t)h;
}
unsigned __int128 __Limbo128(void* data,size_t len,size_t seed,unsigned __int128 salt) {
    if (len == 0) return h_VAL;
    size_t newl1 = len / 2;
    size_t newl2 = len - newl1;
    uint64_t s_hi = (uint64_t)(salt >> 64);
    uint64_t s_lo = (uint64_t)salt;
    uint64_t h1 = __Limbo64(data,newl1, seed, s_hi);
    uint64_t h2 = __Limbo64((uint8_t*)data + newl1, newl2, seed, s_lo);
    unsigned __int128 fh = ((unsigned __int128)h1 << 64) | h2;
    fh ^= salt;
    fh ^= (unsigned __int128)len << 96;
    fh ^= (unsigned __int128)seed << 32;
    h2 ^= ~((uint64_t)salt ^ (s_hi ^ ~((h2 >> 34) & ((s_lo ^ h1) >> 31))));
    uint64_t hi = (uint64_t)(fh >> 64);
    uint64_t lo = (uint64_t)fh;
    uint64_t mix = (uint64_t)(salt ^ seed);
    mix ^= hi;
    mix ^= ~(((hi ^ (lo >> 32))) ^ ~lo);
    uint32_t r1 = (mix      & 63u) | 1u;
    uint32_t r2 = ((mix>>6) & 63u) | 1u;
    uint32_t r3 = ((mix>>12)& 63u) | 1u;
    lo += hi;  hi ^= lo;  lo = __rotl64(lo, r1);
    hi += lo;  lo ^= hi;  hi = __rotl64(hi, r2);
    lo += hi;  hi ^= lo;  lo = __rotl64(lo, r3);
    hi += lo;  lo ^= hi;  hi = __rotl64(hi, 23);
    fh = ((unsigned __int128)hi << 64) | lo;
    fh = ((unsigned __int128)hi << 64) | lo;
    uint64_t x = (uint64_t)fh;
    uint64_t y = (uint64_t)(fh >> 64);
    x ^= x >> 33;
    x *= 0xff51afd7ed558ccdULL;
    x ^= x >> 33;
    x *= 0xc4ceb9fe1a85ec53ULL;
    x ^= x >> 33;
    y ^= x;
    y ^= y >> 29;
    y *= 0x9e3779b97f4a7c15ULL;
    y ^= y >> 32;
    fh = ((unsigned __int128)y << 64) | x;
    return fh;
}
