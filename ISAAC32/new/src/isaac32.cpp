#include "isaac32.hpp"

isaac32::isaac32(const char *seed) {
    uint32_t n[8] = {
        0x9e3779b9, 0x9e3779b9, 0x9e3779b9, 0x9e3779b9,
        0x9e3779b9, 0x9e3779b9, 0x9e3779b9, 0x9e3779b9,
    };
    
    auto mix = [&]() {
        n[0] ^= n[1] << 11; n[3] += n[0]; n[1] += n[2];
        n[1] ^= n[2] >> 2;  n[4] += n[1]; n[2] += n[3];
        n[2] ^= n[3] << 8;  n[5] += n[2]; n[3] += n[4];
        n[3] ^= n[4] >> 16; n[6] += n[3]; n[4] += n[5];
        n[4] ^= n[5] << 10; n[7] += n[4]; n[5] += n[6];
        n[5] ^= n[6] >> 4;  n[0] += n[5]; n[6] += n[7];
        n[6] ^= n[7] << 8;  n[1] += n[6]; n[7] += n[0];
        n[7] ^= n[0] >> 9;  n[2] += n[7]; n[0] += n[1];
    };
    
    const char *p = seed;
    
    for (int i = 0; i < 256; i++) {
        this->_rsl[i] = 0;
        
        for (int j = 0; j < 4; j++) {
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

void isaac32::_update() & {
    uint32_t *r = this->_rsl,
        *m = this->_mem,
        *m2 = this->_mem + 128,
        *const mend = this->_mem + 128;
    
    auto step = [&](uint32_t mix) {
        auto ind = [&](uint32_t x) {
            return this->_mem[(x & (0xFF << 2)) >> 2];
        };
        
        uint32_t y, x = *m;
        
        this->_a = (this->_a ^ mix) + *m2++;
        *m++ = y = ind(x) + this->_a + this->_b;
        *r++ = this->_b = ind(y >> 8) + x;
    };
    
    this->_b += ++this->_c;
    
    while (m < mend) {
        step(this->_a << 13);
        step(this->_a >> 6);
        step(this->_a << 2);
        step(this->_a >> 16);
    }
    
    m2 = this->_mem;
    
    while (m2 < mend) {
        step(this->_a << 13);
        step(this->_a >> 6);
        step(this->_a << 2);
        step(this->_a >> 16);
    }
    
    this->_cnt = 0;
}
