/* A simple program which creates an rodata section */

#include <unistd.h>
#include <string.h>

int main ()
{
    /* the string constant goes into rodata */
    const char msg[] = "kuku makes the world go round";

    write (1, msg, strlen(msg));
    return 0;
}

