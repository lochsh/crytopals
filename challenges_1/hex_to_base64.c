#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


uint8_t hex_char_to_padded_byte(char hex_char) {
    const uint8_t mask = 15;
    const uint32_t boundary = 64;
    return (hex_char & mask) + (hex_char / boundary) * 9;
}


uint8_t hex_char_pair_to_byte(char hex_ms, char hex_ls) {
    return (hex_char_to_padded_byte(hex_ms) << 4) + \
            hex_char_to_padded_byte(hex_ls);
}


uint8_t* hex_str_to_bytes(char* hex_str) {
    int num_bytes = strlen(hex_str) / 2;
    uint8_t *bytes = (uint8_t *) malloc(num_bytes);

    if (bytes == NULL) {
        perror("Error allocating memory");
        return NULL;
    }

    for (int i = 0; i < num_bytes; i++) {
        bytes[i] = hex_char_pair_to_byte(hex_str[i*2], hex_str[i*2 + 1]);
    }

    return bytes;
}
