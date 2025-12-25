#ifndef PASCAL_STRING
#define PASCAL_STRING
#include <stdint.h>

/*
PascalString type invariants:
1. ptr is never NULL
2. PascalString has always length of 0 <= length <= 255
3. ptr always points to some writable memory
4. the buffer always contains at least length bytes (so no un-allocated memory)
*/

// Error codes
enum PascalStringErrorCodes{
    PSTR_OK,
    PSTR_ERROR_ALLOC,
    PSTR_ERROR_TOO_LONG,
    PSTR_ERROR_NULL_INPUT
};

typedef struct PascalString{
    char *ptr;
    uint8_t length;
} pstring_t;

int init_pstring_empty(pstring_t* s);
int init_pstring_from_length(pstring_t *s, uint8_t length);
int init_pstring_from_cstring(pstring_t *s, const char *c_str);
int init_pstring_from_buffer(pstring_t *s, const char buffer[], uint8_t len);
int destroy_pstring(pstring_t *s);

#endif