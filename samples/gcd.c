#include <stdlib.h>

int gcd (int a, int b)
{
    int temp, i;

    while (b != 0) {
	temp	= b;
	b	= a % b;
	a	= temp;
    }

    return a;
}


int main (int argc, char* argv[])
{
    char *int_strs[2] = { argv[1], argv[2] };
    int a = atoi(int_strs[0]), b = atoi(int_strs[1]); 
    
    return gcd (a, b);
}
