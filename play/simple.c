#include <stdio.h>
#include <stdlib.h>

int g_dummy = 42;



//void printf (const char *);

int add5 (int x) {
	return x+5;
}


int main (int argc, char** argv) {

    int x = g_dummy;
    
    int z = add5(x);
    
//    char * text = (char*) malloc (20);

    return x + z;
}
