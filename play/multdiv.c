#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>


int mydiv (int x, int y) {
    x = x / 10;

    return x;
}

int main (int argc, char* argv[]) {

    char *int_strs[2] = { argv[1], argv[2] };
    int is[2] = { atoi(int_strs[0]), atoi(int_strs[1]) };
    
    int res = mydiv (is[0], is[1]);

    return res;
//    return is[0] % is[1];
}
