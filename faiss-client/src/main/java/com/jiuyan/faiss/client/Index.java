package com.jiuyan.faiss.client;

import com.jiuyan.faiss.NativeClient;

public abstract class Index {
	protected int dimension;
	protected long pointer;

	public Index(int d) {
		this.dimension = d;
	}

	public abstract int add(int num, float[][] data);

	public abstract int train(int num, float[][] data);

	public abstract SearchResponse search(int queryLimit, float[][] queryData, int rspLimit);

	public int close() {
		return NativeClient.close(pointer);
	}
	
	public long getPointer(){
		return pointer;
	}
}
