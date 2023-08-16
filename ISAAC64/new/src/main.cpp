#include <stdio.h>
#include "isaac64.hpp"

int main() {
    isaac64 isaac{""};
    
    for (int i = 0; i < 1024; i++) {
        printf("%.16llx", (unsigned long long)isaac.next());
        
        if ((i & 3) == 3)
            putchar('\n');
    }
}
