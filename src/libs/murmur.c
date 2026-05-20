#include <stdint.h>
#include <errno.h>

typedef uint64_t u64;
typedef uint8_t  u8;

static u64 rotl64(u64 x, int r) {
    r &= 63;
    return (x << r) | (x >> (64 - r));
}

static u64 salt = 0;

static void init_salt(void) {
    if (salt == 0) {
        unsigned long a = (unsigned long)&init_salt;
        unsigned long b = (unsigned long)&errno;
        unsigned long c = (unsigned long)&salt;

        unsigned long x = a ^ (b << 1) ^ (c << 2);
        salt = (u64)(x ^ (x >> 32));
    }
}

u64 make_seed(void);

u64 murmur(const void *key, u64 len) {
    init_salt();

    const u8 *data = (const u8*)key;
    u64 nblocks = len / 8;

    u64 h = make_seed() ^ salt;
    const u64 c1 = 0x87c37b91114253d5ULL;
    const u64 c2 = 0x4cf5ad432745937fULL;

    const u64 *blocks = (const u64*)data;

    for (u64 i = 0; i < nblocks; i++) {
        u64 k = blocks[i];
        k *= c1;
        k = rotl64(k, 31);
        k *= c2;

        h ^= k;
        h = rotl64(h, 27);
        h = h * 5 + 0x52dce729ULL;
    }

    const u8 *tail = data + nblocks * 8;
    u64 k1 = 0;

    switch (len & 7) {
        case 7: k1 ^= (u64)tail[6] << 48;
        case 6: k1 ^= (u64)tail[5] << 40;
        case 5: k1 ^= (u64)tail[4] << 32;
        case 4: k1 ^= (u64)tail[3] << 24;
        case 3: k1 ^= (u64)tail[2] << 16;
        case 2: k1 ^= (u64)tail[1] << 8;
        case 1:
            k1 ^= (u64)tail[0];
            k1 *= c1;
            k1 = rotl64(k1, 31);
            k1 *= c2;
            h ^= k1;
    }

    h ^= len;
    h ^= h >> 33;
    h *= 0xff51afd7ed558ccdULL;
    h ^= h >> 33;
    h *= 0xc4ceb9fe1a85ec53ULL;
    h ^= h >> 33;
    h = rotl64(h, (int)((h ^ salt) & 63));

    return h;
}

u64 make_seed(void) {
    unsigned long a = (unsigned long)&make_seed;
    unsigned long b = (unsigned long)&murmur;
    unsigned long c = (unsigned long)&errno;
    unsigned long x = a ^ (b << 1) ^ (c << 2);
    return (u64)(x ^ (x >> 32));
}
