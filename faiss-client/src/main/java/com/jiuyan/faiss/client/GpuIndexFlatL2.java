package com.jiuyan.faiss.client;

import com.jiuyan.faiss.NativeClient;

public class GpuIndexFlatL2 extends Index {

	public GpuIndexFlatL2(int d) {
		super(d);
		int dev_no = 0;
		long res = NativeClient.StandardGpuResources();
		long config = NativeClient.GpuIndexFlatConfig();
		pointer = NativeClient.GpuIndexFlatL2_index(res, dev_no, config);
	}

	@Override
	public int add(int num, float[][] data) {
		float[] xb = new float[num * dimension];
		for (int i = 0; i < num; i++) {
			System.arraycopy(data[i], 0, xb, i * dimension, dimension);
		}
		return NativeClient.GpuIndexFlatL2_add(pointer, num, xb);
	}

	@Override
	public int train(int num, float[][] data) {
		return 0;
	}

	@Override
	public SearchResponse search(int queryLimit, float[][] queryData, int rspLimit) {
		float[] xq = new float[queryLimit * dimension];
		for (int i = 0; i < queryLimit; i++) {
			System.arraycopy(queryData[i], 0, xq, i * dimension, dimension);
		}
		float[] result = new float[queryLimit * rspLimit];
		long[] index = new long[queryLimit * rspLimit];
		NativeClient.GpuIndexFlatL2_search(pointer, queryLimit, xq, rspLimit, result, index);
		float[][] rspData = new float[queryLimit][rspLimit];
		long[][] rspIndex = new long[queryLimit][rspLimit];
		for (int i = 0; i < queryLimit; i++) {
			System.arraycopy(result, 0 * rspLimit, rspData[i], 0, rspLimit);
			System.arraycopy(index, 0 * rspLimit, rspIndex[i], 0, rspLimit);
		}
		SearchResponse rsp = new SearchResponse();
		rsp.setRspData(rspData);
		rsp.setRspIndex(rspIndex);
		return rsp;
	}

}
