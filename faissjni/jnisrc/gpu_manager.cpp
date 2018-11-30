/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//#include "GLogHelper.h"
#include "index_manager.h"
#include "gpu_manager.h"
#include "../../faiss/gpu/StandardGpuResources.h"
#include "../../faiss/gpu/GpuIndexFlat.h"
#include "../../faiss/gpu/GpuIndexIVFFlat.h"
#include <assert.h>

GpuManager* GpuManager::pInstance_ = nullptr;

GpuManager::GpuManager() {
  map_index_ = 0;
  gpu_ivfflat_index_ = 0;
  gpu_flatl2_index_ = 0;
  cfg_index_ = 0;
}

GpuManager::~GpuManager() {}

GpuManager* GpuManager::CreateInstance() {
  if (pInstance_ == nullptr) {
    pInstance_ = new GpuManager();
    assert(pInstance_ != nullptr);
  }

  assert(pInstance_ != nullptr);

  return pInstance_;
}

GpuManager* GpuManager::GetInstance() {
  assert(pInstance_ != nullptr);

  return pInstance_;
}

int GpuManager::ReleaseInstance() {
  if (pInstance_ != nullptr) {
    delete pInstance_;
    pInstance_ = nullptr;

    return 1;
  }

  return 0;
}

bool GpuManager::DelMapKeyAllGpuResources() {
  std::map<long long, faiss::gpu::StandardGpuResources*>::iterator iter =
      gpu_res_map_.begin();
  while (iter != gpu_res_map_.end()) {
    faiss::gpu::StandardGpuResources* pindex = nullptr;
    pindex = iter->second;
    if (pindex != nullptr) {
      delete pindex;
      pindex = nullptr;
    }
    long long key = iter->first;
    iter++;
    gpu_res_map_.erase(key);
  }
  return 0;
}

long long GpuManager::SetMapKeyGpuResources() {
  faiss::gpu::StandardGpuResources* pindex =
      new faiss::gpu::StandardGpuResources();
  if (pindex == nullptr) {
    return -1;
  }
  map_index_ += 1;
  gpu_res_map_.insert(std::make_pair(map_index_, pindex));
  return map_index_;
}

bool GpuManager::DelMapKeyAllGpuIndexFlatConfig() {
  std::map<long long, faiss::gpu::GpuIndexFlatConfig*>::iterator iter =
      gpu_flat_cfg_map_.begin();
  while (iter != gpu_flat_cfg_map_.end()) {
    faiss::gpu::GpuIndexFlatConfig* pindex = nullptr;
    pindex = iter->second;
    if (pindex != nullptr) {
      delete pindex;
      pindex = nullptr;
    }
    long long key = iter->first;
    iter++;
    gpu_flat_cfg_map_.erase(key);
  }
  return 0;
}

long long GpuManager::SetMapKeyGpuIndexFlatConfig() {
  faiss::gpu::GpuIndexFlatConfig* pindex =
      new faiss::gpu::GpuIndexFlatConfig();
  if (pindex == nullptr) {
    return -1;
  }
  cfg_index_ += 1;
  gpu_flat_cfg_map_.insert(std::make_pair(cfg_index_, pindex));
  return cfg_index_;
}

bool GpuManager::DelMapKeyAllGpuIndexFlatL2() {
  std::map<long long, faiss::gpu::GpuIndexFlatL2*>::iterator iter =
  gpu_flatl2_map_.begin();
  while (iter != gpu_flatl2_map_.end()) {
    faiss::gpu::GpuIndexFlatL2* pindex = nullptr;
    pindex = iter->second;
    if (pindex != nullptr) {
      delete pindex;
      pindex = nullptr;
    }
    long long key = iter->first;
    iter++;
    gpu_flatl2_map_.erase(key);
  }
  return 0;
}

long long GpuManager::SetMapKeyGpuIndexFlatL2(long long res, int d,
                                              long long cfg) {
  faiss::gpu::StandardGpuResources* gpu_res = gpu_res_map_[res];
  faiss::gpu::GpuIndexFlatConfig* gpu_cfg = gpu_flat_cfg_map_[cfg];
  if (gpu_res == nullptr || gpu_cfg == nullptr) {
    return -1;
  }
  faiss::gpu::GpuIndexFlatL2* pindex =
      new faiss::gpu::GpuIndexFlatL2(gpu_res, d, *gpu_cfg);
  if (pindex == nullptr) {
    return -2;
  }
  gpu_flatl2_index_ += 1;
  gpu_flatl2_map_.insert(std::make_pair(gpu_flatl2_index_, pindex));
  return gpu_flatl2_index_;
}

faiss::gpu::GpuIndexFlatL2* GpuManager::GetMapKeyGpuIndexFlatL2(long long key) {
  if (gpu_flatl2_map_.size() < 1) {
    return nullptr;
  }
  faiss::gpu::GpuIndexFlatL2* pindex = nullptr;
  pindex = gpu_flatl2_map_[key];
  return pindex;
}
/*
long long GpuManager::SetMapKeyGpuIndexIVFFlat(long long res, int dev,
                                               long long gpu_index,
                                               bool useFloat16, int d,
                                               int nlist, int indicesOptions,
                                               int metricType) {
  faiss::gpu::StandardGpuResources* gpu_res = gpu_res_map_[res];
  IndexManager* pinstance = IndexManager::GetInstance();
  faiss::IndexIVFFlat* index_ivfflat = pinstance->GetMapKeyIVFFlat(gpu_index);
  if (index_ivfflat == nullptr || pinstance == nullptr) {
    return -1;
  }
  faiss::gpu::IndicesOptions options;
  switch (indicesOptions) {
    case 0:
      options = faiss::gpu::IndicesOptions::INDICES_CPU;
      break;
    case 1:
      options = faiss::gpu::IndicesOptions::INDICES_IVF;
      break;
    case 2:
      options = faiss::gpu::IndicesOptions::INDICES_32_BIT;
      break;
    case 3:
      options = faiss::gpu::IndicesOptions::INDICES_64_BIT;
      break;
    default:
      return -2;
  }
  faiss::gpu::GpuIndexIVFFlatConfig config;
  config.device = dev;
  config.indicesOptions = options;
  // config.flatConfig.useFloat16 = useFloat16CoarseQuantizer;
  // config.flatConfig.storeTransposed = storeTransposed;
  config.useFloat16IVFStorage = useFloat16;

  faiss::gpu::GpuIndexIVFFlat* gpu_index_ivfflat =
      new faiss::gpu::GpuIndexIVFFlat(gpu_res, index_ivfflat, config);
  if (gpu_index_ivfflat == nullptr) {
    return -3;
  }
  gpu_ivfflat_index_ += 1;
  gpu_ivfflat_map_.insert(std::make_pair(gpu_ivfflat_index_, gpu_index_ivfflat));
  return gpu_ivfflat_index_;
}
*/
faiss::gpu::GpuIndexIVFFlat* GpuManager::GetMapKeyGpuIndexIVFFlat(long long key) {
  if (gpu_ivfflat_map_.size() < 1) {
    return nullptr;
  }
  faiss::gpu::GpuIndexIVFFlat* pindex = nullptr;
  pindex = gpu_ivfflat_map_[key];
  return pindex;
}

bool GpuManager::DelMapKeyAllGpuIndexIVFFlat() {
  std::map<long long, faiss::gpu::GpuIndexIVFFlat*>::iterator iter =
  gpu_ivfflat_map_.begin();
  while (iter != gpu_ivfflat_map_.end()) {
    faiss::gpu::GpuIndexIVFFlat* pindex = nullptr;
    pindex = iter->second;
    if (pindex != nullptr) {
      delete pindex;
      pindex = nullptr;
    }
    long long key = iter->first;
    iter++;
    gpu_ivfflat_map_.erase(key);
  }
  return 0;
}

long long GpuManager::SetMapKeyGpuIndexIVFFlat(long long res, int dev,
                                               long long gpu_index,
                                               bool useFloat16, int d,
                                               int nlist, int indicesOptions,
                                               int metricType) {
  faiss::MetricType mt;
  if (metricType == 0) {
    mt = faiss::MetricType::METRIC_INNER_PRODUCT;
  } else {
    mt = faiss::MetricType::METRIC_L2;
  }
  faiss::gpu::StandardGpuResources* gpu_res = gpu_res_map_[res];
  if (gpu_res == nullptr) {
    return -4;
  }
  faiss::gpu::IndicesOptions options;
  switch (indicesOptions) {
    case 0:
      options = faiss::gpu::IndicesOptions::INDICES_CPU;
      break;
    case 1:
      options = faiss::gpu::IndicesOptions::INDICES_IVF;
      break;
    case 2:
      options = faiss::gpu::IndicesOptions::INDICES_32_BIT;
      break;
    case 3:
      options = faiss::gpu::IndicesOptions::INDICES_64_BIT;
      break;
    default:
      return -2;
  }
  faiss::gpu::GpuIndexIVFFlatConfig config;
  config.device = dev;
  config.indicesOptions = options;
  // config.flatConfig.useFloat16 = useFloat16CoarseQuantizer;
  // config.flatConfig.storeTransposed = storeTransposed;
  config.useFloat16IVFStorage = useFloat16;

  faiss::gpu::GpuIndexIVFFlat* gpu_index_ivfflat =
      new faiss::gpu::GpuIndexIVFFlat(gpu_res, d, nlist, mt, config);
  if (gpu_index_ivfflat == nullptr) {
    return -3;
  }
  gpu_ivfflat_index_ += 1;
  gpu_ivfflat_map_.insert(
      std::make_pair(gpu_ivfflat_index_, gpu_index_ivfflat));
  return gpu_ivfflat_index_;
}