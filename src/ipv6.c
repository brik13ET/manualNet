#include <ipv6.h>

ip_header ip_init(void)
{
    return (ip_header) { 0 };
}

address_t address_init(int o1, int o2, int o3, int o4)
{
    return
        (address_t) {
            .octet =
            (uint32_t[])
            {
                o1,
                o2,
                o3,
                o4
            }
        };
}