#include <stdio.h>
#include "isaac32.hpp"

int main() {
    isaac32 isaac{""};
    
    for (int i = 0; i < 1024; i++) {
        printf("%.8lx", (unsigned long)isaac.next());
        
        if ((i & 7) == 7)
            putchar('\n');
    }
}
