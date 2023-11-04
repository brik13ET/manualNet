#include <sock.h>

#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <net/if.h>  
#include <net/if_arp.h>

#include <linux/if_packet.h>
#include <unistd.h>
#include <errno.h>

struct sockaddr_ll addr;
socklen_t ad_len;
int sd;
int result;

int8_t init
(
    char* interfaceName
)
{
    addr = (struct sockaddr_ll)
    {
        .sll_family = AF_PACKET,
        .sll_protocol = ETH_P_ALL,
        .sll_ifindex = if_nametoindex(interfaceName),
        .sll_hatype = ARPHRD_RAWIP,
        .sll_pkttype = PACKET_HOST,
        .sll_halen = 6,
        .sll_addr = { 0 }
    };
    ad_len = sizeof(addr);
    sd = socket (AF_PACKET, SOCK_RAW, 0);
    if (sd < 0){
        char buf[40] = { 0 };
        printf(buf, "%s,%d:\terrno: %d\n",__FILE__,__LINE__-3, errno);
        return errno;   
    }
    return 0;
}

void deinit
(

)
{
    memset(&addr, 0, sizeof(addr));
    close(sd);
}

int sendTo
(
    uint8_t* buf,
    size_t arr_len
)
{
    
    // uint8_t* mbuf = (uint8_t*)malloc(arr_len);
    if (buf <= 0)
        return -1;

    int res = sendto(
        sd,
        buf,
        arr_len,
        0,
        (struct sockaddr*)&addr,
        sizeof(addr)
    );
    // free(mbuf);
    return res < 0 ? errno : arr_len;
}

uint8_t* recvFrom
(
    uint8_t* buf,
    size_t buf_siz,
    int offset
)
{
    uint8_t* mbuf = (uint8_t*)malloc(buf_siz);
    if (mbuf <= 0)
        return NULL;

    struct sockaddr_ll recv_sock = addr;
    socklen_t recv_sock_siz = sizeof(recv_sock);
    recvfrom(
        sd,
        mbuf,
        buf_siz+offset,
        0,
        (struct sockaddr*)&recv_sock,
        &recv_sock_siz
    );
    // do
    // {
    // } while (memcmp(mbuf + offset, mbuf, buf_siz));

    memcpy(buf,mbuf,buf_siz);

    free(mbuf);
    return buf;
}