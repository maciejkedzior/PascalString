#include <stdio.h>
#include "src/headers/pascal_string.h"


int main(void){
    pstring_t empty_str;
    int ret = init_pstring_empty(&empty_str);
    if (ret == PSTR_OK){
        printf("Successfully created empty pstring with length: %d\n", empty_str.length);
    }
    else if (ret == PSTR_ERROR_ALLOC){
        perror("Failed to allocate memory!\n");
    }

    pstring_t str_with_length;
    int len_ret = init_pstring_from_length(&str_with_length, 10);
    if (len_ret == PSTR_OK){
        printf("Successfully created pstring with length: %d\n", str_with_length.length);
    }
    else if (len_ret == PSTR_ERROR_ALLOC){
        perror("Failed to allocate memory!\n");
    }

    pstring_t str_from_buf;
    char buffer[] = "abcde";
    int buf_ret = init_pstring_from_buffer(&str_from_buf, buffer, 6);
    if (buf_ret == PSTR_OK){
        printf("Successfully created pstring with length: %d and content: %s\n", str_from_buf.length, str_from_buf.ptr);
    }
    else if (buf_ret == PSTR_ERROR_ALLOC){
        perror("Failed to allocate memory!\n");
    }

    pstring_t str_from_c_str;
    char *cstr = "legia to dzbany";
    int cstr_ret = init_pstring_from_cstring(&str_from_c_str, cstr);
    if (cstr_ret == PSTR_OK){
        printf("Successfully created pstring with length: %d and content: %s\n", str_from_c_str.length, str_from_c_str.ptr);
    }
    else if (cstr_ret == PSTR_ERROR_ALLOC){
        perror("Failed to allocate memory!\n");
    }

    pstring_t str_too_long;
    char *too_long = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";
    //pstring_t arr[2] = {empty_str, str_with_length};
    int too_long_code = init_pstring_from_cstring(&str_too_long, too_long);

    if (too_long_code == PSTR_ERROR_TOO_LONG){
        printf("It was too long! Nothing created!\n");
    }

    destroy_pstring(&empty_str);
    destroy_pstring(&str_with_length);
    destroy_pstring(&str_from_buf);
    destroy_pstring(&str_from_c_str);
}