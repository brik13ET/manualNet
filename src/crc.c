#pragma once
#include <stdint.h>

uint16_t calc_crc(void* data_ptr, size_t len)
{
    uint32_t sum = 0;
    uint8_t *el_ptr = data_ptr;
    for (size_t i = 0; i < (count - count % 2); i+=2)
    {
        sum += el_ptr[i] << 8 | el_ptr[i+1]
    }
    if (count % 2 != 0)
        sum += el_ptr[count - 1] << 8;
    if (sum > 0xFFFF)
        return calc_crc(&sum, sizeof(sum));
    return sum;    
}