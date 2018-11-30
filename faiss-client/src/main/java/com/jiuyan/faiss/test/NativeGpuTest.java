package com.jiuyan.faiss.test;

import java.util.Arrays;
import java.util.Random;

import com.jiuyan.faiss.NativeClient;

public class NativeGpuTest {

	private static int d = 64;
	private static int nb = 100000;
	private static int nq = 10000;
	private static float[] xb = new float[nb * d];
	private static float[] xq = new float[nq * d];

	public static void init() {
		Random random = new Random();
		for (int i = 0; i < nb * d; i++) {
			xb[i] = random.nextFloat();
		}
		for (int i = 0; i < nq * d; i++) {
			xq[i] = random.nextFloat();
		}
	}

	public static void main(String[] args) {
		System.out.println("start:");
		init();
		//testIndexL2();
		System.out.println("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
		testIndexIVF();
	}

	public static void testIndexL2() {
		long res = NativeClient.StandardGpuResources();
		System.out.println("res:" + res);
		long config = NativeClient.GpuIndexFlatConfig();
		System.out.println("config:" + config);
		long pointer = NativeClient.GpuIndexFlatL2_index(res, d, config);
		System.out.println("pointer:" + pointer);
		int rsp = NativeClient.GpuIndexFlatL2_add(pointer, nb, xb);
		System.out.println("add result:" + rsp);
		int queryNum = 5;
		int limit = 4;
		float[] result = new float[queryNum * limit];
		long[] index = new long[queryNum * limit];
		rsp = NativeClient.GpuIndexFlatL2_search(pointer, queryNum, xq, limit, result, index);
		System.out.println("search result:" + rsp);
		System.out.println(Arrays.toString(result));
		System.out.println(Arrays.toString(index));
		System.out.println("close:" + NativeClient.close(pointer));
		System.out.println("finish");
	}

	public static void testIndexIVF() {
		int dev_no = 0;
		long res = NativeClient.StandardGpuResources();
		System.out.println("res:" + res);
		int nlist = 100;
		int indicesOption = 3;
		int metricType = 0;
//		long quantizer = NativeClient.indexFlatL2_index(d);
//		System.out.println("quantizer:" + quantizer);
//		long ivfPointer = NativeClient.indexIVFFlat_index(quantizer, d, nlist, metricType);
//		System.out.println("ivf-pointer:" + ivfPointer);
		long ivfPointer=1;
		long pointer = 100;
		System.out.println("before pointer:" + pointer);
		pointer = NativeClient.GpuIndexIVFFlat_index(res, dev_no, ivfPointer, false, d, nlist, indicesOption, metricType);
		System.out.println("after pointer:" + pointer);
		int rsp = NativeClient.GpuIndexIVFFlat_train(pointer, nb, xb);
		System.out.println("train result:" + rsp);
		rsp = NativeClient.GpuIndexIVFFlat_add(pointer, nb, xb);
		System.out.println("add result:" + rsp);
		int queryNum = 5;
		int limit = 4;
		float[] result = new float[queryNum * limit];
		long[] index = new long[queryNum * limit];
		int probes = 10;
		rsp = NativeClient.setProbe(pointer, probes);
		System.out.println("probe result:" + rsp);
		rsp = NativeClient.GpuIndexIVFFlat_search(pointer, queryNum, xq, limit, result, index);
		System.out.println("search result:" + rsp);
		System.out.println(Arrays.toString(result));
		System.out.println(Arrays.toString(index));
		System.out.println("close:" + NativeClient.close(pointer));
		System.out.println("finish");
	}

}
