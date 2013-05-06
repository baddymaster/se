//
// Debug.h
// BlindStorage
//

#ifndef __BlindStorage__Debug__
#define __BlindStorage__Debug__

#include <iostream>
using std::cout;
using std::endl;
using std::string;

void printhex(unsigned char* pointer, int32_t size, string tag);
void printhex(char* pointer, int32_t size, string tag);
void printhex(unsigned char** pointer, int32_t rows, int32_t cols, string tag);
void printdec(uint32_t* pointer, int32_t size, string tag);
void printchars(unsigned char* pointer, int32_t size, string tag);
#endif /* defined(__BlindStorage__Debug__) */
