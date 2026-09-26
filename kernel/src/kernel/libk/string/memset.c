
#include <kernel/libk/string.h>
#include <stdint.h>

/**
 * @author Avis
 *
 * @brief Fills count bytes at dst with value
 *
 * @return Pointer to bytes
 * */
void* memset(void* dst, int value, size_t count) {
    uint8_t* d = (uint8_t*) dst;
    uint8_t v = (uint8_t) value;

    for (size_t i = 0; i < count; i++) {
        d[i] = v;
    }

    return dst;
}
