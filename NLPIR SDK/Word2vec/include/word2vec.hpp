//
//  word2vec.hpp
//  Word2vec
//
//  Created by 潘洪岩 on 2017/4/25.
//  Copyright © 2017年 Hongyan Pan. All rights reserved.
//

#ifndef word2vec_hpp
#define word2vec_hpp

#include <stdio.h>
#include <iostream>
#include <string.h>

#define WORD2VEC extern "C"

WORD2VEC int InitWord2vec(const char * data,const char * sLicenseCode);

WORD2VEC int InitPara(int size,const char * train,const char * entity,int model,float alp,const char * outfile,int win,float sam,int h,int neg,int threads, int it,int mincount);

WORD2VEC int Train();

WORD2VEC int LoadModel(const char * model);

WORD2VEC const char * CalculateWord(const char * word,int N);

#endif /* word2vec_hpp */
