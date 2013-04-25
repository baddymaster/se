//
//  AES.h
//  BlindStorage
//
//  Created by Muhammad Naveed on 3/18/13.
//  Copyright (c) 2013 Muhammad Naveed. All rights reserved.
//

#ifndef __BlindStorage__AES__
#define __BlindStorage__AES__

#include <iostream>

//
//  AES.cpp
//  BlindStorage
//
//  Created by Muhammad Naveed on 3/18/13.
//  Copyright (c) 2013 Muhammad Naveed. All rights reserved.
//

#include "cryptopp562/osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <cstdlib>
using std::exit;

#include "cryptopp562/cryptlib.h"
using CryptoPP::Exception;

#include "cryptopp562/hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include "cryptopp562/filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include "cryptopp562/aes.h"

#include "cryptopp562/ccm.h"
using CryptoPP::CTR_Mode;

#include "assert.h"

class AES {
private:
    byte* key;
    byte* plaintext;
    byte* ciphertext;
    
public:
    AES();
    ~AES();
    byte* keyGen();
    byte* ENC(byte* plaintext, int size, byte* key, byte* iv);
    byte* DEC(byte* ciphertext, int size, byte* key, byte* iv);
    void print(string tag, string value);
    void print(string tag, byte* value);
    
  };



#endif /* defined(__BlindStorage__AES__) */