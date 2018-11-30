/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   com_jiuyan_faiss_NativeClient.cpp
 * Author: banli
 *
 * Created on 2017年6月28日, 下午2:20
 */
#include "../../common/com_jiuyan_faiss_NativeClient.h"
#include <cstdio>
#include <cstdlib>

#include "../../faiss/IndexFlat.h"
#include "../../faiss/IndexIVFPQ.h"
#include "../../faiss/index_io.h"
#include "index_manager.h"
#include "gpu_manager.h"
#include "../../faiss/gpu/StandardGpuResources.h"
#include "../../faiss/gpu/GpuIndexFlat.h"
#include "../../faiss/gpu/GpuIndexIVFFlat.h"
//#include "GLogHelper.h"
//GLogHelper*  g_glog = new GLogHelper("");

JNIEXPORT jlong JNICALL Java_com_jiuyan_faiss_NativeClient_test(JNIEnv*,
                                                                jclass) {
/*
  GpuManager* pinstance = GpuManager::CreateInstance();
  if (pinstance == nullptr) {
    return 2000;
  }
  long long res1 = pinstance->SetMapKeyGpuResources();
  int  dev1 = 0;
  bool useFloat161 = false;
  int  d1 = 64;
  int nlist1 = 100;
  int indicesOptions1 = 3;
  int metricType1 = 0;

  long long result = pinstance->SetMapKeyGpuIndexIVFFlat(
      res1, dev1, 22, useFloat161, d1, nlist1, indicesOptions1, metricType1);*/
  return 1000;
}

JNIEXPORT jlong JNICALL Java_com_jiuyan_faiss_NativeClient_indexFlatL2_1index(
    JNIEnv* env, jclass cls, jint idimension) {
  if (idimension < 0) {
    return -1;
  }
  IndexManager* pinstance = IndexManager::CreateInstance();
  long long indexkey = pinstance->SetMapKeyFlatL2(idimension);
  return indexkey;
}

JNIEXPORT jint JNICALL Java_com_jiuyan_faiss_NativeClient_close(JNIEnv* env,
                                                                jclass cls,
                                                                jlong lhandle) {
  int res = 0;
  IndexManager* pinstance = IndexManager::CreateInstance();
  int resflatl2 = pinstance->DelMapKeyAllFlatL2();
  int resivfflat = pinstance->DelMapKeyAllIVFFlat();
  int resivfpq = pinstance->DelMapKeyAllIVFPQ();
  if (resflatl2 == 0 && resivfflat == 0 && resivfpq == 0) {
    res = pinstance->ReleaseInstance();
  } else {
    return -2;
  }
  GpuManager* pinstance_gpu = GpuManager::CreateInstance();
  int res_gpu_res = pinstance_gpu->DelMapKeyAllGpuResources();
  int res_gpu_cfg = pinstance_gpu->DelMapKeyAllGpuIndexFlatConfig();
  int res_gpu_flatl2 = pinstance_gpu->DelMapKeyAllGpuIndexFlatL2();
  int res_gpu_ivfflat = pinstance_gpu->DelMapKeyAllGpuIndexIVFFlat();
  if (res_gpu_res == 0 && res_gpu_cfg == 0 && res_gpu_flatl2 == 0 &&
      res_gpu_ivfflat == 0) {
    res = pinstance_gpu->ReleaseInstance();
  } else {
    return -3;
  }
  return res;
}

JNIEXPORT jint JNICALL Java_com_jiuyan_faiss_NativeClient_indexFlatL2_1add(
    JNIEnv* env, jclass cls, jlong lhandle, jint nb, jfloatArray j_array) {
  jint arr_len = env->GetArrayLength(j_array);
  // jfloat* c_array = (jfloat*)new jfloatArray[sizeof(jfloat) * arr_len];
  // memset(c_array, 0x00, sizeof(jfloat) * arr_len);
  // env->GetFloatArrayRegion()
  jfloat* pbuffer = env->GetFloatArrayElements(j_array, JNI_FALSE);
  IndexManager* pinstance = IndexManager::CreateInstance();
  faiss::IndexFlatL2* pindex = pinstance->GetMapKeyFlatL2(lhandle);
  if (pindex == nullptr) {
    return -1;
  }
  pindex->add(nb, pbuffer);
  env->ReleaseFloatArrayElements(j_array, pbuffer, 0);
  return 0;
}

JNIEXPORT jint JNICALL Java_com_jiuyan_faiss_NativeClient_indexFlatL2_1train(
    JNIEnv* env, jclass cls, jlong lhandle, jint nb, jfloatArray j_array) {
  jfloat* pbuffer = env->GetFloatArrayElements(j_array, JNI_FALSE);
  IndexManager* pinstance = IndexManager::CreateInstance();
  faiss::IndexFlatL2* pindex = pinstance->GetMapKeyFlatL2(lhandle);
  if (pindex == nullptr) {
    return -1;
  }
  pindex->train(nb, pbuffer);
  env->ReleaseFloatArrayElements(j_array, pbuffer, 0);
  return 0;
}

JNIEXPORT jint JNICALL Java_com_jiuyan_faiss_NativeClient_indexFlatL2_1search(
    JNIEnv* env, jclass cls, jlong lhandle, jint inq, jfloatArray j_array,
    jint ilimit, jfloatArray j_result, jlongArray j_lindex) {
  jfloat* pxq = env->GetFloatArrayElements(j_array, JNI_FALSE);
  jfloat* pres = env->GetFloatArrayElements(j_result, JNI_FALSE);
  jlong* plindex = env->GetLongArrayElements(j_lindex, JNI_FALSE);

  IndexManager* pinstance = IndexManager::CreateInstance();
  faiss::IndexFlatL2* pindex = pinstance->GetMapKeyFlatL2(lhandle);
  if (pindex == nullptr) {
    return -1;
  }
  pindex->search(inq, pxq, ilimit, pres, plindex);
  env->ReleaseFloatArrayElements(j_array, pxq, 0);
  env->ReleaseFloatArrayElements(j_result, pres, 0);
  env->ReleaseLongArrayElements(j_lindex, plindex, 0);
  return 0;
}

JNIEXPORT jlong JNICALL Java_com_jiuyan_faiss_NativeClient_indexIVFFlat_1index(
    JNIEnv* env, jclass cls, jlong lhandle, jint idimension, jint ilist,
    jint imetric_type) {
  IndexManager* pinstance = IndexManager::CreateInstance();
  long long res =
      pinstance->SetMapKeyIVFFlat(lhandle, idimension, ilist, imetric_type);
  return res;
}

JNIEXPORT jint JNICALL Java_com_jiuyan_faiss_NativeClient_indexIVFFlat_1add(
    JNIEnv* env, jclass cls, jlong lhandle, jint nb, jfloatArray j_array) {
  jfloat* pbuffer = env->GetFloatArrayElements(j_array, JNI_FALSE);
  IndexManager* pinstance = IndexManager::CreateInstance();
  faiss::IndexIVFFlat* pindex = pinstance->GetMapKeyIVFFlat(lhandle);
  if (pindex == nullptr) {
    return -1;
  }
  pindex->add(nb, pbuffer);
  env->ReleaseFloatArrayElements(j_array, pbuffer, 0);
  return 0;
}

JNIEXPORT jint JNICALL Java_com_jiuyan_faiss_NativeClient_indexIVFFlat_1train(
    JNIEnv* env, jclass cls, jlong lhandle, jint nb, jfloatArray j_array) {
  jfloat* pbuffer = env->GetFloatArrayElements(j_array, JNI_FALSE);
  IndexManager* pinstance = IndexManager::CreateInstance();
  faiss::IndexIVFFlat* pindex = pinstance->GetMapKeyIVFFlat(lhandle);
  if (pindex == nullptr) {
    return -1;
  }
  pindex->train(nb, pbuffer);
  env->ReleaseFloatArrayElements(j_array, pbuffer, 0);
  return 0;
}

JNIEXPORT jint JNICALL Java_com_jiuyan_faiss_NativeClient_indexIVFFlat_1search(
    JNIEnv* env, jclass cls, jlong lhandle, jint inq, jfloatArray j_array,
    jint ilimit, jfloatArray j_result, jlongArray j_lindex) {
  jfloat* pxq = env->GetFloatArrayElements(j_array, JNI_FALSE);
  jfloat* pres = env->GetFloatArrayElements(j_result, JNI_FALSE);
  jlong* plindex = env->GetLongArrayElements(j_lindex, JNI_FALSE);

  IndexManager* pinstance = IndexManager::CreateInstance();
  faiss::IndexIVFFlat* pindex = pinstance->GetMapKeyIVFFlat(lhandle);
  if (pindex == nullptr) {
    return -1;
  }
  pindex->search(inq, pxq, ilimit, pres, plindex);
  env->ReleaseFloatArrayElements(j_array, pxq, 0);
  env->ReleaseFloatArrayElements(j_result, pres, 0);
  env->ReleaseLongArrayElements(j_lindex, plindex, 0);
  return 0;
}

JNIEXPORT jint JNICALL Java_com_jiuyan_faiss_NativeClient_setProbe(
    JNIEnv* env, jclass cls, jlong lhandle, jint probes) {
  IndexManager* pinstance = IndexManager::CreateInstance();
  faiss::IndexIVFFlat* pindex = pinstance->GetMapKeyIVFFlat(lhandle);
  if (pindex == nullptr) {
    return -1;
  }
  pindex->nprobe = probes;
  return 0;
}

JNIEXPORT jint JNICALL
Java_com_jiuyan_faiss_NativeClient_indexIVFFlat_1add_1with_1ids(
    JNIEnv* env, jclass cls, jlong lhandle, jint j_nb, jfloatArray j_x,
    jlongArray j_xids) {
  jfloat* x = env->GetFloatArrayElements(j_x, JNI_FALSE);
  jlong* xids = env->GetLongArrayElements(j_xids, JNI_FALSE);
  IndexManager* pinstance = IndexManager::CreateInstance();
  faiss::IndexIVFFlat* pindex = pinstance->GetMapKeyIVFFlat(lhandle);
  if (pindex == nullptr) {
    return -1;
  }
  pindex->add_with_ids(j_nb, x, xids);
  env->ReleaseFloatArrayElements(j_x, x, 0);
  env->ReleaseLongArrayElements(j_xids, xids, 0);
  return 0;
}

JNIEXPORT jlong JNICALL Java_com_jiuyan_faiss_NativeClient_indexIVFPQ_1index(
    JNIEnv* env, jclass cls, jlong lhandle, jint idimension, jint ilist, jint m,
    jint nbits) {
  IndexManager* pinstance = IndexManager::CreateInstance();
  if (pinstance == nullptr) {
    return -1;
  }
  long long res =
      pinstance->SetMapKeyIVFPQ(lhandle, idimension, ilist, m, nbits);
  return res;
}

JNIEXPORT jint JNICALL Java_com_jiuyan_faiss_NativeClient_indexIVFPQ_1add(
    JNIEnv* env, jclass cls, jlong lhandle, jint nb, jfloatArray j_array) {
  jfloat* pbuffer = env->GetFloatArrayElements(j_array, JNI_FALSE);
  IndexManager* pinstance = IndexManager::CreateInstance();
  faiss::IndexIVFPQ* pindex = pinstance->GetMapKeyIVFPQ(lhandle);
  if (pindex == nullptr) {
    return -1;
  }
  pindex->add(nb, pbuffer);
  env->ReleaseFloatArrayElements(j_array, pbuffer, 0);
  return 0;
}

JNIEXPORT jint JNICALL Java_com_jiuyan_faiss_NativeClient_indexIVFPQ_1train(
    JNIEnv* env, jclass cls, jlong lhandle, jint nb, jfloatArray j_array) {
  jfloat* pbuffer = env->GetFloatArrayElements(j_array, JNI_FALSE);
  IndexManager* pinstance = IndexManager::CreateInstance();
  faiss::IndexIVFPQ* pindex = pinstance->GetMapKeyIVFPQ(lhandle);
  if (pindex == nullptr) {
    return -1;
  }
  pindex->train(nb, pbuffer);
  env->ReleaseFloatArrayElements(j_array, pbuffer, 0);
  return 0;
}

JNIEXPORT jint JNICALL Java_com_jiuyan_faiss_NativeClient_indexIVFPQ_1search(
    JNIEnv* env, jclass cls, jlong lhandle, jint inq, jfloatArray j_array,
    jint ilimit, jfloatArray j_result, jlongArray j_lindex) {
  jfloat* pxq = env->GetFloatArrayElements(j_array, JNI_FALSE);
  jfloat* pres = env->GetFloatArrayElements(j_result, JNI_FALSE);
  jlong* plindex = env->GetLongArrayElements(j_lindex, JNI_FALSE);

  IndexManager* pinstance = IndexManager::CreateInstance();
  faiss::IndexIVFPQ* pindex = pinstance->GetMapKeyIVFPQ(lhandle);
  if (pindex == nullptr) {
    return -1;
  }
  pindex->search(inq, pxq, ilimit, pres, plindex);
  env->ReleaseFloatArrayElements(j_array, pxq, 0);
  env->ReleaseFloatArrayElements(j_result, pres, 0);
  env->ReleaseLongArrayElements(j_lindex, plindex, 0);
  return 0;
}

JNIEXPORT jint JNICALL Java_com_jiuyan_faiss_NativeClient_setPQProbe(
    JNIEnv* env, jclass cls, jlong lhandle, jint probes) {
  IndexManager* pinstance = IndexManager::CreateInstance();
  faiss::IndexIVFPQ* pindex = pinstance->GetMapKeyIVFPQ(lhandle);
  if (pindex == nullptr) {
    return -1;
  }
  pindex->nprobe = probes;
  return 0;
}

JNIEXPORT jlong JNICALL Java_com_jiuyan_faiss_NativeClient_StandardGpuResources(
    JNIEnv* env, jclass cls) {
  GpuManager* pinstance = GpuManager::CreateInstance();
  if (pinstance == nullptr) {
    return -1;
  }
  long long res = pinstance->SetMapKeyGpuResources();
  return res;
}

JNIEXPORT jlong JNICALL
Java_com_jiuyan_faiss_NativeClient_GpuIndexFlatConfig(JNIEnv* env, jclass cls) {
  GpuManager* pinstance = GpuManager::CreateInstance();
  if (pinstance == nullptr) {
    return -1;
  }
  long long res = pinstance->SetMapKeyGpuIndexFlatConfig();
  return res;
}

JNIEXPORT jlong JNICALL
Java_com_jiuyan_faiss_NativeClient_GpuIndexFlatL2_1index(JNIEnv* env,
                                                         jclass cls, jlong jres,
                                                         jint d, jlong jcfg) {
  GpuManager* pinstance = GpuManager::CreateInstance();
  if (pinstance == nullptr) {
    return -1;
  }
  long long res = pinstance->SetMapKeyGpuIndexFlatL2(jres, d, jcfg);
  return res;
}

JNIEXPORT jint JNICALL Java_com_jiuyan_faiss_NativeClient_GpuIndexFlatL2_1add(
    JNIEnv* env, jclass cls, jlong lhandle, jint xb, jfloatArray j_result) {
  GpuManager* pinstance = GpuManager::CreateInstance();
  if (pinstance == nullptr) {
    return -1;
  }
  faiss::gpu::GpuIndexFlatL2* pgpu_flatl2 = pinstance->GetMapKeyGpuIndexFlatL2(lhandle);
  if (pgpu_flatl2 == nullptr) {
    return -2;
  }
  jfloat* pres = env->GetFloatArrayElements(j_result, JNI_FALSE);
  pgpu_flatl2->add(xb, pres);
  env->ReleaseFloatArrayElements(j_result, pres, 0);
  return 0;
}

JNIEXPORT jint JNICALL
Java_com_jiuyan_faiss_NativeClient_GpuIndexFlatL2_1search(
    JNIEnv* env, jclass cls, jlong lhandle, jint query_num, jfloatArray xq,
    jint limit, jfloatArray result, jlongArray index) {
    GpuManager* pinstance = GpuManager::CreateInstance();
    if (pinstance == nullptr) {
      return -1;
    }
    faiss::gpu::GpuIndexFlatL2* pgpu_flatl2 = pinstance->GetMapKeyGpuIndexFlatL2(lhandle);
    if (pgpu_flatl2 == nullptr) {
      return -2;
    }
    jfloat* pxq = env->GetFloatArrayElements(xq, JNI_FALSE);
    jfloat* pres = env->GetFloatArrayElements(result, JNI_FALSE);
    jlong* plindex = env->GetLongArrayElements(index, JNI_FALSE);
  
    pgpu_flatl2->search(query_num, pxq, limit, pres, plindex);

    env->ReleaseFloatArrayElements(xq, pxq, 0);
    env->ReleaseFloatArrayElements(result, pres, 0);
    env->ReleaseLongArrayElements(index, plindex, 0);
    return 0;
}

JNIEXPORT jlong JNICALL
Java_com_jiuyan_faiss_NativeClient_GpuIndexIVFFlat_1index(
    JNIEnv* env, jclass cls, jlong res, jint dev, jlong gpu_index,
    jboolean useFloat16, jint d, jint nlist, jint indicesOptions,
    jint metricType) {
  GpuManager* pinstance = GpuManager::CreateInstance();
  if (pinstance == nullptr) {
    return -1;
  }

  long long result = pinstance->SetMapKeyGpuIndexIVFFlat(
      res, dev, gpu_index, useFloat16, d, nlist, indicesOptions, metricType);
  return result;
}

JNIEXPORT jint JNICALL Java_com_jiuyan_faiss_NativeClient_GpuIndexIVFFlat_1train
(JNIEnv* env, jclass cls, jlong lhandle, jint nb, jfloatArray xb){

  GpuManager* pinstance = GpuManager::CreateInstance();
  if (pinstance == nullptr) {
    return -1;
  }
  jfloat* pxq = env->GetFloatArrayElements(xb, JNI_FALSE);
  faiss::gpu::GpuIndexIVFFlat* pindex =
      pinstance->GetMapKeyGpuIndexIVFFlat(lhandle);
  if (pindex == nullptr) {
    return -2;
  }
  pindex->train(nb,pxq);
  env->ReleaseFloatArrayElements(xb, pxq, 0);
  
  return 0;
}

JNIEXPORT jint JNICALL Java_com_jiuyan_faiss_NativeClient_GpuIndexIVFFlat_1add
(JNIEnv* env, jclass cls, jlong lhandle, jint nb, jfloatArray xb){
  GpuManager* pinstance = GpuManager::CreateInstance();
  if (pinstance == nullptr) {
    return -1;
  }
  jfloat* pxq = env->GetFloatArrayElements(xb, JNI_FALSE);
  faiss::gpu::GpuIndexIVFFlat* pindex =
      pinstance->GetMapKeyGpuIndexIVFFlat(lhandle);
  if (pindex == nullptr) {
    return -2;
  }
  pindex->add(nb,pxq);
  env->ReleaseFloatArrayElements(xb, pxq, 0);
  return 0;
}

JNIEXPORT jint JNICALL
Java_com_jiuyan_faiss_NativeClient_GpuIndexIVFFlat_1search(
    JNIEnv* env, jclass cls, jlong lhandle, jint query_num, jfloatArray xq,
    jint limit, jfloatArray result, jlongArray index) {
  GpuManager* pinstance = GpuManager::CreateInstance();
  if (pinstance == nullptr) {
    return -1;
  }
  faiss::gpu::GpuIndexIVFFlat* pindex =
      pinstance->GetMapKeyGpuIndexIVFFlat(lhandle);
  if (pindex == nullptr) {
    return -2;
  }
  jfloat* pxq = env->GetFloatArrayElements(xq, JNI_FALSE);
  jfloat* pres = env->GetFloatArrayElements(result, JNI_FALSE);
  jlong* plindex = env->GetLongArrayElements(index, JNI_FALSE);
  pindex->search(query_num, pxq, limit, pres, plindex);
  env->ReleaseFloatArrayElements(xq, pxq, 0);
  env->ReleaseFloatArrayElements(result, pres, 0);
  env->ReleaseLongArrayElements(index, plindex, 0);
  return 0;
}

JNIEXPORT jint JNICALL Java_com_jiuyan_faiss_NativeClient_setGpuIVFProbe
(JNIEnv* env, jclass cls, jlong lhandle, jint probes){
  GpuManager* pinstance = GpuManager::CreateInstance();
  if (pinstance == nullptr) {
    return -1;
  }
  faiss::gpu::GpuIndexIVFFlat* pindex =
      pinstance->GetMapKeyGpuIndexIVFFlat(lhandle);
  if (pindex == nullptr) {
    return -2;
  }
  pindex->setNumProbes(probes);
  return 0;
}