/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   index_manager.h
 * Author: banli
 *
 * Created on 2017年6月29日, 下午2:10
 */

#ifndef GPU_MANAGER_H
#define GPU_MANAGER_H
#include <map>
namespace faiss {
struct IndexFlatL2;
struct IndexIVFFlat;
struct IndexIVFPQ;
namespace gpu{
  class StandardGpuResources;
  struct GpuIndexFlatConfig;
  class GpuIndexFlatL2;
  class GpuIndexIVFFlat;
};
};
class GpuManager {
 public:
  static GpuManager *CreateInstance();
  static GpuManager *GetInstance();
  static int ReleaseInstance();
  GpuManager();
  ~GpuManager();

 public:
  long long SetMapKeyGpuResources();
  bool DelMapKeyAllGpuResources();

  long long SetMapKeyGpuIndexFlatConfig();
  bool DelMapKeyAllGpuIndexFlatConfig();

  long long SetMapKeyGpuIndexFlatL2(long long res, int d, long long cfg);
  bool DelMapKeyAllGpuIndexFlatL2();
  faiss::gpu::GpuIndexFlatL2* GetMapKeyGpuIndexFlatL2(long long key);

  long long SetMapKeyGpuIndexIVFFlat(long long res, int dev,
                                     long long gpu_index, bool useFloat16,
                                     int d, int nlist, int indicesOptions,
                                     int metricType);
  bool DelMapKeyAllGpuIndexIVFFlat();
  faiss::gpu::GpuIndexIVFFlat *GetMapKeyGpuIndexIVFFlat(long long key);

 private:
  static GpuManager *pInstance_;

  std::map<long long, faiss::gpu::StandardGpuResources *> gpu_res_map_;
  std::map<long long, faiss::gpu::GpuIndexFlatConfig *> gpu_flat_cfg_map_;
  std::map<long long, faiss::gpu::GpuIndexFlatL2 *> gpu_flatl2_map_;
  std::map<long long, faiss::gpu::GpuIndexIVFFlat *> gpu_ivfflat_map_;

  long long gpu_ivfflat_index_;
  long long gpu_flatl2_index_;
  long long map_index_;
  long long cfg_index_;
};
#endif /* GPU_MANAGER_H */
