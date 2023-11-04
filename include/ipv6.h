#pragma once

#include <stdint.h>
#include <attribute.h>

typedef uint32_t address_t[4];
#define address_t_siz sizeof(uint32_t) * 4

typedef uint32_t bitf_vtf;
#define BITF_VTF(FLABEL,TCLASS,VERSION) (bitf_vtf)((VERSION << 28) | (TCLASS << 20) | FLABEL)

typedef struct
{
    bitf_vtf vtf;
    

    uint16_t payload_len;
    uint8_t  next_hdr;
    uint8_t  hop_lim;

    address_t src_addr;
    address_t dest_addr;
} attribute(packed) ip_header;

ip_header ip_init(void);


#define address_init(o1,o2,o3,o4) (address_t) {o1,o2,o3,o4}

ip_header* ip_header_init(
    ip_header*  hdr_ptr,
    uint8_t     version,
    uint8_t     t_class,
    uint32_t    flow_label,

    uint16_t    payload_len,
    uint8_t     next_hdr,
    uint8_t     hop_lim,

    address_t   src_addr,
    address_t   dest_addr
);

