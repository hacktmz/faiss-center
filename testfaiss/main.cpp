/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: banli
 *
 * Created on 2017年6月28日, 下午3:38
 */
#include <cstdlib>
#include "../faiss/IndexFlat.h"
#include "../faiss/IndexIVFPQ.h"
#include "../faiss/index_io.h"
#include "../faissjni/jnisrc/index_manager.h"
#include "../faissjni/jnisrc/gpu_manager.h"
#include "../faiss/gpu/StandardGpuResources.h"
#include "../faiss/gpu/GpuIndexFlat.h"
#include "../faiss/gpu/GpuIndexIVFFlat.h"
#include "../faissjni/jnisrc/GLogHelper.h"
using namespace std;

  GLogHelper* g_glog = new GLogHelper("");
int main(int argc, char** argv) {

  GpuManager* pinstance = GpuManager::CreateInstance();
  if (pinstance == nullptr) {
    return -1;
  }
  for (int i = 0; i < 10; i++) {
    long long res1 = pinstance->SetMapKeyGpuResources();
    LOG(INFO) << "StandardGpuResources res= " << res1;
    long long res = res1;
    int dev = 0;
    bool useFloat16 = false;
    int d = 64;
    int nlist = 100;
    int indicesOptions = 3;
    int metricType = 0;

    long long result = pinstance->SetMapKeyGpuIndexIVFFlat(
        res, dev, 1, useFloat16, d, nlist, indicesOptions, metricType);
    LOG(INFO) << "SetMapKeyGpuIndexIVFFlat res= " << result;
  }
  bool res1 = pinstance->DelMapKeyAllGpuResources();
  bool res2 = pinstance->DelMapKeyAllGpuIndexIVFFlat();
  LOG(INFO) << "DelMapKeyAllGpuResources res= " << res1;
  LOG(INFO) << "DelMapKeyAllGpuIndexIVFFlat res= " << res2;
  pinstance->ReleaseInstance();
  return 0;
}
