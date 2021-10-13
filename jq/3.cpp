#include <stdio.h>

int main(int x, int p){
    int y, z;
    while(y = ++x) {
        // for (z=0; 
        //     z<y ? z=z*8 + y%8, y/=8, p = (z==y) | (z/8==y), 1 : (x-++p || printf("%o\n",x)) && x%p;
        //     );
        for (z=0; ;) {
            if (z<y) {
                z=z*8 + y%8;
                y/=8;
                p = (z==y) | (z/8==y);
            } else {
                p++;
                if (x == p) {
                    printf("%o\n",x);
                }
                if (x%p == 0 || (x==p && x==0)) {
                    break;
                }
            }
        }
    }
    return 0;
}