#include<stdio.h>

int main (int argc, char* argv[]) {
    int i;

    sscanf(argv[1], "%i", &i);

    printf ("%x\n", (unsigned)i);

    return 0;
}
