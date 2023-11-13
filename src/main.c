#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <errno.h>

#include <ethernet2.h>
#include <ipv6.h>
#include <udp.h>
#include <crc.h>
#include <sock.h>

#define DBG
#include <debug.h>

#include <variant.h>

#define ptr_cmp(Pb,Pe) (void*)Pe - (void*)Pb

// #define PRINT_LAYOUT
#define SAVE_PKG

typedef struct
{
    void* heap_ptr;
    size_t size;
} heap_obj;


heap_obj make_pkg(void* data, size_t data_siz)
{
    uint8_t pkg_size = sizeof(eth_hdr) + sizeof(ip_header) + sizeof(udp_hdr) + data_siz + sizeof(uint32_t);
    void* raw_pkg = malloc(pkg_size);

    memset(raw_pkg, 0, pkg_size); 

    eth_hdr*    eth_h   = (eth_hdr*)raw_pkg;
    ip_header*  ip_h    = (ip_header*)( (void*)eth_h + sizeof(eth_hdr) );
    udp_hdr*    udp_h   = (udp_hdr*)( (void*)ip_h + sizeof(ip_header) );
    void*       pload   = (void*)udp_h + sizeof(udp_hdr);
    uint32_t*   eth_cs  = (uint32_t*)(pload + data_siz);

    
    eth_init(
        eth_h,
        mac(0x00,0xe0,0x4c,0x68,0x00,0x07),
        mac(0x00,0xe0,0x4c,0x68,0x00,0x07)
    );

    ip_header_init(
        ip_h,
        6,
        0, // Attended bulk data traffic
        0x12345,
        FIO_siz + sizeof(udp_hdr),
        17, // UDP
        4,
        address_init(0,0,0,1),
        address_init(0,0,0,1)
    );
    udp_init(
        udp_h,
        5075,
        43522,
        FIO_siz + sizeof(udp_hdr),
        crc16(data + sizeof(ip_header), sizeof(udp_hdr) + FIO_siz)
    );

    memcpy(pload, data, data_siz);

    *eth_cs = crc32(data, pkg_size);
    return (heap_obj){.heap_ptr = raw_pkg, .size = pkg_size};
}

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
    
    heap_obj pkg = make_pkg(FIO, FIO_siz);

    #ifdef SAVE_PKG
    FILE* fd = fopen("./pkg_dump.bin", "wb+");

    fwrite(pkg.heap_ptr, pkg.size, 1, fd);

    fclose(fd);
    #endif
    
    if (init("lo\0"))
    {
        fprintf(stderr, "Init fail: %d\n", errno);
        exit(errno);
    }
    printf("Init()\tOK\n");

    int sendro_res = sendTo(pkg.heap_ptr, pkg.size);
    printf("sendTo()\tOK\n");

    uint8_t buf[4];
    uint8_t* rx_dat = recvFrom(
        buf,
        0,
        0
    );
    printf("recvFrom()\tOK\n");

    deinit();
    
    free(pkg.heap_ptr);

}
