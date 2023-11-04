#include <stdint.h>
#include <stddef.h>

uint16_t crc16(void* data_ptr, size_t len)
{
    uint32_t sum = 0;
    uint16_t *el_ptr = data_ptr;
    for (size_t i = 0; i < len / 2; i++)
        sum += el_ptr[i];
    if (len % 2 != 0)
        sum += el_ptr[len / 2 + 1];
    if (sum > 0xFFFF)
        return crc16(&sum, sizeof(sum));
    return ~sum;
}


uint32_t crc32(void* data_ptr, size_t len)
{
    uint64_t sum = 0;
    uint32_t *el_ptr = data_ptr;
    for (size_t i = 0; i < len / 4; i ++)
        sum += el_ptr[i];
    if (len % 4 != 0)
        sum += el_ptr[len % 4 + 1];
    if (sum > 0xFFFFFFFF)
        return crc16(&sum, sizeof(sum));
    return ~sum;
}