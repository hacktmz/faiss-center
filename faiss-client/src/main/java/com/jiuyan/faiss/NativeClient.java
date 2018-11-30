package com.jiuyan.faiss;

public class NativeClient {

	public static native long test();
	public static native long setLogPath(byte[] path);
	public static native long switchLog(boolean open,int level);
	public static native long indexFlatL2_index(int d);
	public static native int indexFlatL2_add(long pointer,int nb,float[] xb);
	public static native int indexFlatL2_train(long pointer,int nb,float[] xb);
	public static native int indexFlatL2_search(long pointer,int query_num,float[] xq,int limit,float[] result,long[] index);
	public static native int close(long pointer);
		
	public static native long indexIVFFlat_index(long quantizer,int d,int nlist,int metricType);
	public static native int indexIVFFlat_train(long pointer,int nb,float[] xb);
	public static native int indexIVFFlat_add(long pointer,int nb,float[] xb);
	public static native int indexIVFFlat_add_with_ids(long pointer,int nb,float[] xb,long[] ids);
	public static native int setProbe(long pointer,int probes);
	public static native int indexIVFFlat_search(long pointer,int query_num,float[] xq,int limit,float[] result,long[] index);
	
	public static native long indexIVFPQ_index(long quantizer,int d,int nlist,int m,int nbits);
	public static native int indexIVFPQ_train(long pointer,int nb,float[] xb);
	public static native int indexIVFPQ_add(long pointer,int nb,float[] xb);
	public static native int setPQProbe(long pointer,int probes);
	public static native int indexIVFPQ_search(long pointer,int query_num,float[] xq,int limit,float[] result,long[] index);
	
	public static native long StandardGpuResources();
	public static native long GpuIndexFlatConfig();
	public static native long GpuIndexFlatL2_index(long res,int d,long config);
	public static native int GpuIndexFlatL2_add(long pointer,int nb,float[] xb);
	public static native int GpuIndexFlatL2_search(long pointer,int query_num,float[] xq,int limit,float[] result,long[] index);
	
	public static native long GpuIndexIVFFlat_index(long res,int dev,long gpu_index,boolean useFloat16,int d,int nlist,int indicesOptions,int metricType);
	public static native int GpuIndexIVFFlat_train(long pointer,int nb,float[] xb);
	public static native int GpuIndexIVFFlat_add(long pointer,int nb,float[] xb);
	public static native int GpuIndexIVFFlat_search(long pointer,int query_num,float[] xq,int limit,float[] result,long[] index);
	
	static {
		LibUtil.loadFaissLib();
	}
	
}
