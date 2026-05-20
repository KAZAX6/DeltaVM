#include "../include/dict.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint64_t u64;

typedef struct {
    u64    hash;
    void*  data;
    size_t size;
    char*  key;
} obj;

typedef struct {
    obj*   objects;
    size_t cap;
    size_t len;
} bucket;

struct dict {
    bucket* arr;
    size_t  len;
    size_t  cap;
};

extern u64 murmur(const void *key, u64 len);
extern char* __strdup(const char* input);

static int obj_cmp_by_hash(const void* a, const void* b) {
    const obj* A = a;
    const obj* B = b;
    if (A->hash < B->hash) return -1;
    if (A->hash > B->hash) return 1;
    return 0;
}

static void bucket_binary_insert(bucket* b, obj o) {
    if (b->len == b->cap) {
        b->cap = b->cap ? b->cap * 2 : 8;
        b->objects = realloc(b->objects, b->cap * sizeof(obj));
        if (!b->objects) return;
    }

    size_t lo = 0;
    size_t hi = b->len;

    while (lo < hi) {
        size_t mid = lo + (hi - lo) / 2;
        if (b->objects[mid].hash < o.hash)
            lo = mid + 1;
        else
            hi = mid;
    }

    memmove(&b->objects[lo + 1],
            &b->objects[lo],
            (b->len - lo) * sizeof(obj));

    b->objects[lo] = o;
    b->len++;
}

static void dict_rehash(dict_t* d) {
    size_t old_cap = d->cap;
    size_t new_cap = old_cap * 2;
    size_t i, j;

    bucket* new_arr = calloc(new_cap, sizeof(bucket));
    if (!new_arr) return;

    for (i = 0; i < old_cap; i++) {
        bucket* b = &d->arr[i];
        for (j = 0; j < b->len; j++) {
            obj o = b->objects[j];
            size_t idx = o.hash % new_cap;
            bucket* nb = &new_arr[idx];
            bucket_binary_insert(nb, o);
        }
        free(b->objects);
    }

    free(d->arr);
    d->arr = new_arr;
    d->cap = new_cap;
}

static int _push_to_buck(bucket* b, const char* key, const void* data, size_t s) {
    if (!b || !data || !s || !key) return 0;

    if (!b->cap) {
        b->objects = calloc(25, sizeof(obj));
        if (!b->objects) return 0;
        b->cap = 25;
        b->len = 0;
    }

    u64 hash = murmur(key, (u64)strlen(key));
    if (!hash) return 0;

    obj o;
    o.key = __strdup(key);
    if (!o.key) return 0;

    o.data = malloc(s);
    if (!o.data) {
        free(o.key);
        return 0;
    }

    memcpy(o.data, data, s);
    o.hash = hash;
    o.size = s;

    bucket_binary_insert(b, o);
    return 1;
}

static void bdelete(bucket* b, size_t idx) {
    if (!b || idx >= b->len)
        return;

    free(b->objects[idx].data);

    if (idx < b->len - 1) {
        memmove(
            &b->objects[idx],
            &b->objects[idx + 1],
            (b->len - idx - 1) * sizeof(obj)
        );
    }

    b->len--;
}

dict_t* dict_new(size_t cap) {
    dict_t* d = malloc(sizeof(dict_t));
    if (!d) return NULL;

    if (cap == 0)
        cap = 25;

    d->arr = calloc(cap, sizeof(bucket));
    if (!d->arr) {
        free(d);
        return NULL;
    }

    d->cap = cap;
    d->len = 0;
    return d;
}

void dict_push(dict_t* d, const char* str_key, const void* data, size_t size_of_data) {
    if (!d || !str_key || !data || !size_of_data) return;

    u64 hash = murmur(str_key, (u64)strlen(str_key));

    if (!d->cap) {
        d->arr = calloc(25, sizeof(bucket));
        if (!d->arr) return;
        d->cap = 25;
        d->len = 0;
    }

    if ((d->len / (float)d->cap) >= 0.75f)
        dict_rehash(d);

    size_t idx = hash % d->cap;

    if (_push_to_buck(&d->arr[idx], str_key, data, size_of_data))
        d->len++;
}

void dict_find(dict_t* d, const char* str_key, size_t out[2]) {
    out[0] = SIZE_MAX;
    out[1] = SIZE_MAX;

    if (!d || !str_key || !d->cap)
        return;

    u64 h = murmur(str_key, (u64)strlen(str_key));
    if (!h)
        return;

    size_t buck = h % d->cap;
    bucket* b = &d->arr[buck];

    if (b->len == 0)
        return;

    obj key = { .hash = h };
    obj* found = bsearch(
        &key,
        b->objects,
        b->len,
        sizeof(obj),
        obj_cmp_by_hash
    );

    if (!found)
        return;

    out[0] = buck;
    out[1] = (size_t)(found - b->objects);
}

void* dict_get(dict_t* d, const char* str_key, size_t* out_s) {
    if (!d || !d->arr || !str_key || !out_s) return NULL;

    size_t indexes[2];
    dict_find(d, str_key, indexes);

    if (indexes[0] == SIZE_MAX || indexes[1] == SIZE_MAX) return NULL;

    obj* o = &d->arr[indexes[0]].objects[indexes[1]];
    if (!o->data) return NULL;

    void* newd = malloc(o->size);
    if (!newd) return NULL;

    memcpy(newd, o->data, o->size);
    *out_s = o->size;

    return newd;
}

int dict_delete(dict_t* d, const char* str_key) {
    if (!d || !str_key) return 0;

    size_t o[2];
    dict_find(d, str_key, o);

    if (o[0] == SIZE_MAX || o[1] == SIZE_MAX) return 0;

    bdelete(&d->arr[o[0]], o[1]);
    d->len--;

    return 1;
}

void dict_foreach(dict_t* d, void (*fptr)(const char* key, void* value)) {
    if (!d || !fptr) return;

    size_t i, j;
    for (i = 0; i < d->cap; i++)
        for (j = 0; j < d->arr[i].len; j++)
            fptr(d->arr[i].objects[j].key, d->arr[i].objects[j].data);
}

void dict_set(dict_t* d, const char* key, const void* newd, size_t sizeofd) {
    if (!d || !key || !newd || !sizeofd) return;

    size_t o[2];
    dict_find(d, key, o);

    if (o[0] == SIZE_MAX || o[1] == SIZE_MAX) {
        dict_push(d, key, newd, sizeofd);
        return;
    }

    obj* ob = &d->arr[o[0]].objects[o[1]];

    void* newdat = malloc(sizeofd);
    if (!newdat) return;

    memcpy(newdat, newd, sizeofd);
    free(ob->data);

    ob->data = newdat;
    ob->size = sizeofd;
}

dict_t* dict_copy(dict_t* input) {
    if (!input) return NULL;

    dict_t* d = dict_new(input->cap);
    if (!d) return NULL;

    size_t i, j;
    for (i = 0; i < input->cap; i++) {
        bucket* b = &input->arr[i];
        for (j = 0; j < b->len; j++) {
            obj* o = &b->objects[j];
            dict_push(
                d,
                o->key,
                o->data,
                o->size
            );
        }
    }

    return d;
}

dict_t* dict_move(dict_t** input) {
    if (!input || !(*input)) return NULL;

    dict_t* p = *input;
    *input = NULL;

    return p;
}

void dict_free(dict_t** d) {
    if (!d || !*d) return;

    dict_t* dc = *d;
    size_t i, j;

    for (i = 0; i < dc->cap; i++) {
        bucket* b = &dc->arr[i];
        for (j = 0; j < b->len; j++) {
            obj* o = &b->objects[j];
            free(o->key);
            free(o->data);
        }
        free(b->objects);
    }

    free(dc->arr);
    free(dc);
    *d = NULL;
}
