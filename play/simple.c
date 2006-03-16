#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

int g_dummy = 100;



//void printf (const char *);

int add5 (int x) {
    return x+5;
}


int main (int argc, char* argv[]) {

/*     char *int_strs[2] = { argv[1], argv[2] }; */
/*     unsigned is[2] = { atoi(int_strs[0]), atoi(int_strs[1]) }; */

//    char * arg = argv[1];
    char s1[] = "012345678901234567";
//    char s2[32] = " papa bye bye";

    int len;

//    strcat (s2, s1);

    len = sizeof(s1);

    write (1, s1, len);
    
    return len;
//    return g_dummy + is[0] * is[1];

//    int x = g_dummy;
    
//    int z = add5(x);
    
//    write (1, int_str, strlen(int_str));
//    write (3, &i, sizeof(i));
//    char * text = (char*) malloc (20);

//    return i + strlen(int_str) + z;
}
