#include <stdint.h>
static inline uint64_t __rotl64(uint64_t x, unsigned r) {
    r &= 63;
    return (x << r) | (x >> ((64 - r) & 63));
}
static inline uint64_t __rotr64(uint64_t x, unsigned r) {
    r &= 63;
    return (x >> r) | (x << ((64 - r) & 63));
}
static inline uint64_t __rtpatt(uint64_t x) {
    uint64_t y = __rotl64(x,7);
    y ^= ~(y & (y >> ((y ^ x) & 63ULL)));
    y = __rotr64(y,3);
    y *= 0x9E3779B97F4A7C15ULL;
    y = __rotl64(y, (x >> ((x ^ y) & 63)) & 31);
    return y;
}