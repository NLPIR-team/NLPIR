//
//  distance.hpp
//  Word2vec
//
//  Created by 潘洪岩 on 2017/5/1.
//  Copyright © 2017年 Hongyan Pan. All rights reserved.
//

#ifndef distance_hpp
#define distance_hpp

#include <stdio.h>

class Distance
{
private:
    static const long long max_size = 2000;         // max length of strings
    static const long long N = 40;                  // number of closest words that will be shown
    static const long long max_w = 50;              // max length of vocabulary entries
public:
    char st1[max_size];
    char *bestw[N];
    char st[100][max_size];
    float dist, len, bestd[N], vec[max_size];
    long long words, size, a, b, c, d, cn, bi[100];
    char ch;
    float *M;
    char *vocab;
    int loadModel(const char * model);
    const char * calculateDistance(const char * word);
};

#endif /* distance_hpp */
