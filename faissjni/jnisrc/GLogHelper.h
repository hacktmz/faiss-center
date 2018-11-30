/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GLogHelper.h
 * Author: banli
 *
 * Created on 2017年9月29日, 下午3:25
 */

#ifndef GLOGHELPER_H
#define GLOGHELPER_H
#include "./glog/logging.h"
#include "./glog/raw_logging.h"

//将信息输出到单独的文件和 LOG(ERROR)
void SignalHandle(const char* data, int size);

class GLogHelper
{
public:
    //GLOG配置：
    GLogHelper(char* program);
    //GLOG内存清理：
    ~GLogHelper();
};


#endif /* GLOGHELPER_H */

