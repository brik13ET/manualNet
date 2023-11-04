#pragma once
#include <stdint.h>

uint16_t crc16(void* data_ptr, size_t len);
uint32_t crc32(void* data_ptr, size_t len);