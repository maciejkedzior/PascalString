#ifndef PASCAL_STRING
#define PASCAL_STRING
#include <stdint.h>

/*
PascalString type invariants:
1. ptr is never NULL
2. PascalString has always length of 0 <= length < capacity <= 255
3. ptr always points to some writable memory of at least capacity bytes
4. only first length bytes is valid data
*/

// Error codes
enum PascalStringReturnCodes{
    PSTR_OK,
    PSTR_ERROR_ALLOC,
    PSTR_ERROR_TOO_LONG,
    PSTR_ERROR_NULL_INPUT,
    PSTR_ERROR_OUT_OF_BOUNDS
};

typedef struct PascalString{
    char *ptr;
    uint8_t length;
    uint8_t capacity;
} pstring_t;

int pstring_init_empty(pstring_t* s);
int pstring_init_from_length(pstring_t *s, uint8_t length);
int pstring_init_from_cstring(pstring_t *s, const char *c_str);
int pstring_init_from_buffer(pstring_t *s, const char buffer[], uint8_t len);
int pstring_destroy(pstring_t *s);


char pstring_get_char_at(const pstring_t *s, uint8_t idx);
int pstring_set_char_at(pstring_t *s, char ch, uint8_t idx);

// Mutations
int pstring_fill(pstring_t *s, const char *src, uint8_t src_len);
int pstring_fill_cstring(pstring_t *s, const char *c_str);

#endif