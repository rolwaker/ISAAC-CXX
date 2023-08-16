#ifndef ISAAC64_HPP
#define ISAAC64_HPP 1
#include <stdint.h>

struct isaac64 {
private:
    uint64_t _rsl[256];
    uint64_t _mem[256];
    uint64_t _cnt, _a, _b, _c;
    
    void _update() &;
    
public:
    isaac64(const char *seed);
    
    isaac64(const isaac64 &) = default;
    
    isaac64 &operator = (const isaac64 &) & = default;
    
    ~isaac64() = default;
    
    
    uint64_t next() & {
        uint64_t rnd = this->_rsl[this->_cnt++];
        
        if (this->_cnt == 256)
            this->_update();
        
        return rnd;
    }
};

#endif
