#include <stdlib.h>
#include <ethernet2.h>
#include <string.h>

eth_hdr* eth_init(eth_hdr* hdr_ptr, mac_addr src, mac_addr dest)
{
    hdr_ptr->type = htons(IPv6);
    memcpy(&(hdr_ptr->dest), dest, sizeof(mac_addr) );
    memcpy(&(hdr_ptr->src), src, sizeof(mac_addr) );
    return hdr_ptr;
}