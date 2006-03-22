#include <sys/mman.h>

int main (int argc, char * argv[]) {

    char buf[16];

    buf[16] = argv[1][24];
    
    char * mem = mmap (12345678, 8765,
		       PROT_READ | PROT_WRITE,
		       MAP_ANONYMOUS | MAP_PRIVATE,
		       5, 1001);

    mem[0] = 'f';
    return mem[1];
}

