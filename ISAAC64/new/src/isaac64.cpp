#include "isaac64.hpp"

isaac64::isaac64(const char *seed) {
    uint64_t n[8] = {
        0x9e3779b97f4a7c13, 0x9e3779b97f4a7c13,
        0x9e3779b97f4a7c13, 0x9e3779b97f4a7c13,
        0x9e3779b97f4a7c13, 0x9e3779b97f4a7c13,
        0x9e3779b97f4a7c13, 0x9e3779b97f4a7c13,
    };
    
    auto mix = [&]() {
        n[0] -= n[4]; n[5] ^= n[7] >> 9;  n[7] += n[0];
        n[1] -= n[5]; n[6] ^= n[0] << 9;  n[0] += n[1];
        n[2] -= n[6]; n[7] ^= n[1] >> 23; n[1] += n[2];
        n[3] -= n[7]; n[0] ^= n[2] << 15; n[2] += n[3];
        n[4] -= n[0]; n[1] ^= n[3] >> 14; n[3] += n[4];
        n[5] -= n[1]; n[2] ^= n[4] << 20; n[4] += n[5];
        n[6] -= n[2]; n[3] ^= n[5] >> 17; n[5] += n[6];
        n[7] -= n[3]; n[4] ^= n[6] << 14; n[6] += n[7];
    };
    
    const char *p = seed;
    
    for (int i = 0; i < 256; i++) {
        this->_rsl[i] = 0;
        
        for (int j = 0; j < 8; j++) {
            this->_rsl[i] = (this->_rsl[i] << 8) | (uint8_t)*p;
            
            if (!*p)
                p = seed;
            else
                p++;
        }
    }
    
    this->_a = 0;
    this->_b = 0;
    this->_c = 0;
    
    for (int i = 0; i < 4; i++)
        mix();
    
    for (int i = 0; i < 256; i += 8) {
        for (int j = 0; j < 8; j++)
            n[j] += this->_rsl[i + j];
        
        mix();
        
        for (int j = 0; j < 8; j++)
            this->_mem[i + j] = n[j];
    }
    
    for (int i = 0; i < 256; i += 8) {
        for (int j = 0; j < 8; j++)
            n[j] += this->_mem[i + j];
        
        mix();
        
        for (int j = 0; j < 8; j++)
            this->_mem[i + j] = n[j];
    }
    
    this->_update();
}

void isaac64::_update() & {
    uint64_t *r = this->_rsl,
        *m = this->_mem,
        *m2 = this->_mem + 128,
        *const mend = this->_mem + 128;
    
    auto step = [&](uint64_t mix) {
        auto ind = [&](uint64_t x) {
            return this->_mem[(x & (0xFF << 3)) >> 3];
        };
        
        uint64_t y, x = *m;
        
        this->_a = mix + *m2++;
        *m++ = y = ind(x) + this->_a + this->_b;
        *r++ = this->_b = ind(y >> 8) + x;
    };
    
    this->_b += ++this->_c;
    
    while (m < mend) {
        step(~(this->_a ^ (this->_a << 21)));
        step(this->_a ^ (this->_a >> 5));
        step(this->_a ^ (this->_a << 12));
        step(this->_a ^ (this->_a >> 33));
    }
    
    m2 = this->_mem;
    
    while (m2 < mend) {
        step(~(this->_a ^ (this->_a << 21)));
        step(this->_a ^ (this->_a >> 5));
        step(this->_a ^ (this->_a << 12));
        step(this->_a ^ (this->_a >> 33));
    }
    
    this->_cnt = 0;
}
