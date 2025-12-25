#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "src/headers/pascal_string.h"


int pstring_init_empty(pstring_t *s){
    assert(s != NULL);
    s->ptr = calloc(1, sizeof(char));
    if (!s->ptr) return PSTR_ERROR_ALLOC;
    s->length = 0;
    return PSTR_OK;
}

int pstring_init_from_length(pstring_t *s, uint8_t length){
    assert(s != NULL);
    if (length == 0) return pstring_init_empty(s);

    s->ptr = calloc(length, sizeof(char));
    if (!s->ptr) return PSTR_ERROR_ALLOC;
    s->length = length;
    return PSTR_OK;
}

int pstring_init_from_buffer(pstring_t *s, const char* buffer, uint8_t len){
    assert(s != NULL);
    if (buffer == NULL){
        return PSTR_ERROR_NULL_INPUT;
    }
    int ret_code = pstring_init_from_length(s, len);    // invariants are checked inside the initializer so no need to check them here
    if (ret_code == PSTR_ERROR_ALLOC) return ret_code;
    if (len != 0)
        memcpy(s->ptr, buffer, len);

    return PSTR_OK;
}

int pstring_init_from_cstring(pstring_t *s, const char *c_str){
    assert(s != NULL);
    if (c_str == NULL){
        return PSTR_ERROR_NULL_INPUT;
    }
    size_t c_str_len = strlen(c_str);

    if (c_str_len > 255){
        return PSTR_ERROR_TOO_LONG;
    }

    int ret_code = pstring_init_from_length(s, (uint8_t)c_str_len);
    if (ret_code == PSTR_ERROR_ALLOC){
        return ret_code;
    }

    if (c_str_len != 0){
        memcpy(s->ptr, c_str, c_str_len);
    }

    return PSTR_OK;
}

int pstring_destroy(pstring_t *s){
    assert(s != NULL);
    assert(s->ptr != NULL);
    free(s->ptr);
    s->ptr = NULL;
    s->length = 0;
    return PSTR_OK;
}

