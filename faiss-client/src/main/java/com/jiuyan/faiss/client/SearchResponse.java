package com.jiuyan.faiss.client;

public class SearchResponse {
	private float[][] rspData;
	private long[][] rspIndex;

	public float[][] getRspData() {
		return rspData;
	}

	public void setRspData(float[][] rspData) {
		this.rspData = rspData;
	}

	public long[][] getRspIndex() {
		return rspIndex;
	}

	public void setRspIndex(long[][] rspIndex) {
		this.rspIndex = rspIndex;
	}

}
