//
//  CountMinSketch.hpp
//  AdvAlgoProj
//
//  Created by Nakul Srivathsa on 10/10/18.
//  Copyright © 2018 Nakul Srivathsa. All rights reserved.
//

#ifndef CountMinSketch_hpp
#define CountMinSketch_hpp

#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <string.h>
#include <limits.h>

class countMinSketch {
    int **cms;
    int l, b;
public:
    countMinSketch();
    ~countMinSketch();
    void inc(char *x);
    int cnt(char *x);
};

unsigned hash1(void *str, int len);
unsigned hash2(void *str, int len);

#endif /* CountMinSketch_hpp */
