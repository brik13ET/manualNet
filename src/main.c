#include <stdio.h>
#include <locale.h>

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

    
}
