#pragma once
#ifndef SCREEN_R5LI9P21
#define SCREEN_R5LI9P21

#include "types.h" 

namespace screen {

static const unsigned char * RAMSCREEN = (unsigned char *)0xB8000;
static const unsigned char * SCREENLIM  = (unsigned char *)0xB8000;
static const unsigned int SIZESCREEN = 0xFA0;

class tty
{
 private:
    int _attr = 0x0E; 
    int x = 0;
    int y = 0;
 public:
    void attr(int attr) {this->_attr = attr;};
    int  attr() {return _attr;}
    void scrollup(unsigned int n);
    void putcar(unsigned char c);
    void puts(char const *str);
};

}

extern screen::tty tty;
#endif /* end of include guard: SCREEN_R5LI9P21 */
