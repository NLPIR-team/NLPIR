//
//  System.cpp
//  Segmentor
//
//  Created by 潘洪岩 on 2017/3/18.
//  Copyright © 2017年 Hongyan Pan. All rights reserved.
//

#include "FsSystem.hpp"
#include <boost/filesystem.hpp>

namespace fs=boost::filesystem;

std::string FsSystem::getpath(const char * fpath){
    fs::path p(fpath);
    return p.make_preferred().string();
}

std::string FsSystem::pathAppend(const char * src1,const char * src2){
    fs::path p(src1);
    p /=src2;
    return p.make_preferred().string();
}

//bool fexist(const char * fpath){
//    fs::file_status status;
//    fs::file_type type;
//    
//}
