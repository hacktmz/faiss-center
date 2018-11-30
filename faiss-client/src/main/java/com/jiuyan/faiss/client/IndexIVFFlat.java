package com.jiuyan.faiss.client;

import com.jiuyan.faiss.NativeClient;

public class IndexIVFFlat extends Index {
	private long quantizer;

	public IndexIVFFlat(int d, int nlist) {
		super(d);
		quantizer = NativeClient.indexFlatL2_index(d);
		int metricType = 1;
		pointer = NativeClient.indexIVFFlat_index(quantizer, d, nlist, metricType);
	}

	@Override
	public int add(int num, float[][] data) {
		float[] xb = new float[num * dimension];
		for (int i = 0; i < num; i++) {
			System.arraycopy(data[i], 0, xb, i * dimension, dimension);
		}
		return NativeClient.indexIVFFlat_add(pointer, num, xb);

	}

	@Override
	public int train(int num, float[][] data) {
		float[] xb = new float[num * dimension];
		for (int i = 0; i < num; i++) {
			System.arraycopy(data[i], 0, xb, i * dimension, dimension);
		}
		return NativeClient.indexIVFFlat_train(pointer, num, xb);

	}

	public int setProbes(int probes) {
		return NativeClient.setProbe(pointer, probes);
	}

	@Override
	public SearchResponse search(int queryLimit, float[][] queryData, int rspLimit) {
		float[] xq = new float[queryLimit * dimension];
		for (int i = 0; i < queryLimit; i++) {
			System.arraycopy(queryData[i], 0, xq, i * dimension, dimension);
		}
		float[] result = new float[queryLimit * rspLimit];
		long[] index = new long[queryLimit * rspLimit];
		NativeClient.indexIVFFlat_search(pointer, queryLimit, xq, rspLimit, result, index);
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

	public int close() {
		NativeClient.close(quantizer);
		return NativeClient.close(pointer);
	}

}
