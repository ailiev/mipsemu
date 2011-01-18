#include <stdio.h>

#include <ctype.h>

#include <faerieplay/common/utils-macros.h>

void print_ascii_byte(unsigned u, int byte_idx)
{
    int c = GETBITS(u, (byte_idx*8), (byte_idx*8)+7);
    if (isprint(c)) {
        printf("%c", c);
    }
    else {
        printf("\\%x", c);
    }
}


int main (int argc, char * argv[]) {
    char * val = argv[1];
    unsigned uval;
    sscanf(val, "%x", &uval);

    print_ascii_byte(uval, 0);
    print_ascii_byte(uval, 1);
    print_ascii_byte(uval, 2);
    print_ascii_byte(uval, 3);
    printf("%s", "\n");

    return 0;
}
