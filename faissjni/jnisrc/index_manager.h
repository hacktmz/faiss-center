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

#ifndef INDEX_MANAGER_H
#define INDEX_MANAGER_H
#include <map>
namespace faiss {
struct IndexFlatL2;
struct IndexIVFFlat;
struct IndexIVFPQ;
};
class IndexManager {
 public:
  static IndexManager *CreateInstance();
  static IndexManager *GetInstance();
  static int ReleaseInstance();
  IndexManager();
  ~IndexManager();

 public:
  long long GetMapSizeFlatL2();
  long long SetMapKeyFlatL2(int ivec);
  bool DelMapKeyFlatL2(long long key);
  bool DelMapKeyAllFlatL2();
  faiss::IndexFlatL2 *GetMapKeyFlatL2(long long key);

 public:
  long long GetMapSizeIVFFlat();
  long long SetMapKeyIVFFlat(long long key, int d, int nlist, int metricType);
  faiss::IndexIVFFlat *GetMapKeyIVFFlat(long long key);
  bool DelMapKeyAllIVFFlat();

 public:
  long long SetMapKeyIVFPQ(long long key, int d, int nlist, int m, int nbits);
  faiss::IndexIVFPQ *GetMapKeyIVFPQ(long long key);
  bool DelMapKeyAllIVFPQ();  

 private:
  static IndexManager *pInstance_;
  std::map<long long, faiss::IndexFlatL2 *> flatl2_map_;
  std::map<long long, faiss::IndexIVFFlat *> ivfflat_map_;
  std::map<long long, faiss::IndexIVFPQ *> ivfpq_map_;
  long long map_index_;
};
#endif /* INDEX_MANAGER_H */
