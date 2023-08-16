#ifndef ISAAC32_HPP
#define ISAAC32_HPP 1
#include <stdint.h>

struct isaac32 {
private:
    uint32_t _rsl[256];
    uint32_t _mem[256];
    uint32_t _cnt, _a, _b, _c;
    
    void _update() &;
    
public:
    isaac32(const char *seed);
    
    isaac32(const isaac32 &) = default;
    
    isaac32 &operator = (const isaac32 &) & = default;
    
    ~isaac32() = default;
    
    
    uint32_t next() & {
        uint32_t rnd = this->_rsl[this->_cnt++];
        
        if (this->_cnt == 256)
            this->_update();
        
        return rnd;
    }
};

#endif
