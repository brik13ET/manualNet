#include <ipv6.h>
#include <arpa/inet.h>
#include <string.h>
ip_header ip_init(void)
{
    return (ip_header) { 0 };
}


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
)
{
    src_addr = (address_t){
        htonl(src_addr[0]),
        htonl(src_addr[1]),
        htonl(src_addr[2]),
        htonl(src_addr[3])
    };
    dest_addr = (address_t){
        htonl(dest_addr[0]),
        htonl(dest_addr[1]),
        htonl(dest_addr[2]),
        htonl(dest_addr[3])
    };
    void* raw_ptr = hdr_ptr;

    bitf_vtf bits = BITF_VTF(flow_label,t_class,version);
    bits = htonl(bits);
    
    memcpy(raw_ptr, &bits, sizeof(bits));

    payload_len = htons(payload_len);
    
    hdr_ptr->hop_lim     = hop_lim;
    hdr_ptr->next_hdr    = next_hdr;
    hdr_ptr->payload_len = payload_len;
    memcpy(&hdr_ptr->src_addr, src_addr, address_t_siz);
    memcpy(&hdr_ptr->dest_addr, dest_addr, address_t_siz);
    
    return hdr_ptr;

}