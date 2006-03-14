#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

int g_dummy = 50;



//void printf (const char *);

int add5 (int x) {
	return x+5;
}


int main (int argc, char* argv[]) {

    char * int_str = argv[1];
    unsigned i = atoi(int_str);
    return i;
    
/*     int x = g_dummy; */
    
/*     int z = add5(x); */
    
/*     write (1, int_str, strlen(int_str)); */
/*     write (3, &i, sizeof(i)); */
/* //    char * text = (char*) malloc (20); */

/*     return i + z; */
}
