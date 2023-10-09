#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include <ipv6.h>
#include <udp.h>
#include <crc.h>
#include <variant.h>

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru_RU.UTF8");
    printf(
        "Hello, from CNet!\n"
        "%s\n"
        "%zu\t%zu\t%zu\n",
        FIO, F_len, I_len, O_len
    );
    printf(
        "%s\t%s\n",
        F_len % 3 == 0 ? "ping" :
        F_len % 3 == 2 ? "udp" :
            "tcp",
        I_len % 2 == 0 ? "IPv4" : "IPv6"
    );

    uint8_t pkg_size = sizeof(ip_header) + sizeof(udp_hdr) + FIO_len;
    void* data = malloc(pkg_size);

    ip_header* ip_h = (ip_header*)data;
    udp_hdr* udp_h = (udp_hdr*)(data + sizeof(ip_header));
    void* pload = data + sizeof(ip_header) + sizeof(udp_hdr);

    ip_h->version = 6;
    ip_h->t_class = 4 << 2 | 4 << 5 | 1;
    ip_h->flow_label = 0x55555;
    ip_h->payload_len = FIO_len + sizeof(udp_h);
    ip->next_hdr = 17; // UDP
    ip_h->hop_lim = 0xFF;
    ip_h->src_addr = address_init(0,0,0,1);
    ip_h->dest_addr = address_init(0,0,0,1);

    udp_h->ip->src_addr = address_init(0,0,0,1);
    udp_h->ip->dst_addr = address_init(0,0,0,1);
    udp_h->ip->udp_len = FIO_len + sizeof(udp_h);
    udp_h->ip->zeros = 0;
    udp_h->ip->next_hdr = 17; // UDP
    udp_h->port_src = 43521;
    udp_h->port_dest = 43521;
    udp_h->dg_len = FIO_len;
    udp_h->csum = calc_crc(data + sizeof(ip_header), sizeof(udp_hdr) + FIO_len);

    
    free(data);

}
