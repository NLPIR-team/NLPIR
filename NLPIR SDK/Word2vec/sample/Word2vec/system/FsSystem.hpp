//
//  System.hpp
//  Segmentor
//
//  Created by 潘洪岩 on 2017/3/18.
//  Copyright © 2017年 Hongyan Pan. All rights reserved.
//

#ifndef System_hpp
#define System_hpp

#include <stdio.h>
#include <iostream>
#include <string>

class FsSystem{
    
public:
    std::string getpath(const char * fpath);
    std::string pathAppend(const char * src1,const char * src2);
};

#endif /* System_hpp */
