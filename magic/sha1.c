

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void bin2hex(const char *s, uint32_t x[], int len) {
    int i;
    printf ("\n // %s", s);
    for (i=0; i<len; i++) {
      if ((i & 3)==0) putchar('\n');
      printf (" 0x%08x,", x[i]);
    }
    putchar('\n');
}

#pragma intrinsic(fabs,pow,sqrt)

uint32_t p[4]={2,3,5,10};

uint32_t sqrt2int (uint32_t x) {
    uint32_t r;
    r = (uint32_t)(fabs(sqrt((double)p[x]))*pow(2,30));
    return r;
}

int main(void)
{
    int      i;
    uint32_t k[4];
        
    // create K constants
    for (i=0; i<4; i++) {
      k[i] = sqrt2int(i);
    }
    bin2hex("SHA-1 K constants", k, 4);    
    return 0;
}
