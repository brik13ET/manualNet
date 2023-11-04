#include <arpa/inet.h>
#include <string.h>
#include <udp.h>

udp_hdr* udp_init(
    udp_hdr* hdr_ptr,
    uint16_t port_src,
    uint16_t port_dest,
    uint16_t dg_len,
    uint16_t csum
)
{
    port_dest   = htons(port_dest);
    port_src    = htons(port_src);
    dg_len      = htons(dg_len);
    memcpy(
        &hdr_ptr->port_src,
        &port_src,
        sizeof(port_src)
    );
    memcpy(
        &hdr_ptr->port_dest,
        &port_dest,
        sizeof(port_dest)
    );
    memcpy(
        &hdr_ptr->dg_len,
        &dg_len,
        sizeof(dg_len)
    );
    memcpy(
        &hdr_ptr->csum,
        &csum,
        sizeof(csum)
    );
    return hdr_ptr;
}