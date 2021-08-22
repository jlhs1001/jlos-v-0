#pragma once
#include <stddef.h>
#include <stdint.h>

class Bitmap {
public:
    // bitmap buffer size
    size_t Size;

    // pointer to start of bitmap buffer
    uint8_t* Buffer;
    
    /*
    Operator overloading to get bitmap value like 
    a standard array.
    */
    bool operator[](uint64_t index);
    void Set(uint64_t index, bool value);
};