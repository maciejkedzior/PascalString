#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../headers/pascal_string.h"


int pstring_init_empty(pstring_t *s){
    assert(s != NULL);
    s->ptr = calloc(1, sizeof(char));
    if (!s->ptr) return PSTR_ERROR_ALLOC;
    s->length = 0;
    s->capacity = 1;
    return PSTR_OK;
}

int pstring_init_from_length(pstring_t *s, uint8_t length){
    assert(s != NULL);
    if (length == 0) return pstring_init_empty(s);

    s->ptr = calloc(length, sizeof(char));
    if (!s->ptr) return PSTR_ERROR_ALLOC;
    s->length = length;
    s->capacity = length;
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
    s->capacity = 0;
    return PSTR_OK;
}


char pstring_get_char_at(const pstring_t *s, uint8_t idx){
    assert(s != NULL);
    
    if (idx >= s->length){
        return '\0';
    }
    return s->ptr[idx];
}

int pstring_set_char_at(pstring_t *s, char ch, uint8_t idx){
    assert(s != NULL);

    if (idx >= s->length){
        return PSTR_ERROR_OUT_OF_BOUNDS;
    }

    s->ptr[idx] = ch;

    return PSTR_OK;
}

int pstring_fill(pstring_t *s, const char *src, uint8_t src_len){
    assert(s != NULL);
    if (src == NULL){
        return PSTR_ERROR_NULL_INPUT;
    }

    if (src_len == s->length){
        memcpy(s->ptr, src, src_len);
        return PSTR_OK;
    }

    if (src_len > s->capacity){
        s->ptr = realloc(s->ptr, sizeof(char) * src_len);

        if (s->ptr == NULL){
            return PSTR_ERROR_ALLOC;
        }

        s->capacity = src_len;
    }

    memcpy(s->ptr, src, src_len);

    if (src_len < s->length){
        memset(s->ptr+src_len, 0, s->capacity-src_len);
    }

    s->length = src_len;
    return PSTR_OK;
}


int pstring_fill_cstring(pstring_t *s, const char *c_str){
    assert(s != NULL);
    if (c_str == NULL){
        return PSTR_ERROR_NULL_INPUT;
    }

    size_t raw_src_len = strlen(c_str);
    if (raw_src_len > 255){
        return PSTR_ERROR_TOO_LONG;
    }

    uint8_t src_len = raw_src_len;

    if (src_len == s->length){
        memcpy(s->ptr, c_str, src_len);
        return PSTR_OK;
    }

    if (src_len > s->capacity){
        s->ptr = realloc(s->ptr, sizeof(char) * src_len);

        if (s->ptr == NULL){
            return PSTR_ERROR_ALLOC;
        }

        s->capacity = src_len;
    }

    memcpy(s->ptr, c_str, src_len);

    if (src_len < s->length){
        memset(s->ptr+src_len, 0, s->capacity-src_len);
    }

    s->length = src_len;
    return PSTR_OK;
}