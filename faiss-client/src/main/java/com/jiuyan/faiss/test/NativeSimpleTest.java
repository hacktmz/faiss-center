package com.jiuyan.faiss.test;

import java.util.Arrays;
import java.util.Random;

import com.jiuyan.faiss.NativeClient;

public class NativeSimpleTest {

	public static void main(String[] args) {
		testIndexIVF();
		System.out.println("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
		testIndexIVFPQ();
	}

	public static void testIndexL2() {
		int d = 64;
		int nb = 100000;
		int nq = 10000;
		float[] xb = new float[nb * d];
		float[] xq = new float[nq * d];

		Random random = new Random();
		for (int i = 0; i < nb * d; i++) {
			xb[i] = random.nextFloat();
		}
		for (int i = 0; i < nq * d; i++) {
			xq[i] = random.nextFloat();
		}
		long pointer = NativeClient.indexFlatL2_index(d);
		System.out.println("pointer:" + pointer);
		int res = NativeClient.indexFlatL2_add(pointer, nb, xb);
		System.out.println("add result:" + res);
		// NativeClient.indexFlatL2_train(pointer, nb, xb);

		int queryNum = 5;
		int limit = 4;
		float[] result = new float[queryNum * limit];
		long[] index = new long[queryNum * limit];
		NativeClient.indexFlatL2_search(pointer, queryNum, xq, limit, result, index);
		System.out.println(Arrays.toString(result));
		System.out.println(Arrays.toString(index));
		System.out.println("close:" + NativeClient.close(pointer));
		System.out.println("finish");
	}

	public static void testIndexIVF() {
		int d = 64;
		int nb = 100000;
		int nq = 10000;
		float[] xb = new float[nb * d];
		float[] xq = new float[nq * d];

		Random random = new Random();
		for (int i = 0; i < nb * d; i++) {
			xb[i] = random.nextFloat();
		}
		for (int i = 0; i < nq * d; i++) {
			xq[i] = random.nextFloat();
		}
		long quantizer = NativeClient.indexFlatL2_index(d);
		int nlist = 100;
		int metricType = 1;
		System.out.println("quantizer:" + quantizer);
		long pointer = NativeClient.indexIVFFlat_index(quantizer, d, nlist, metricType);
		System.out.println("pointer:" + pointer);
		int res = NativeClient.indexIVFFlat_train(pointer, nb, xb);
		System.out.println("train result:" + res);
		res = NativeClient.indexIVFFlat_add(pointer, nb, xb);
		System.out.println("add result:" + res);
		int queryNum = 5;
		int limit = 4;
		float[] result = new float[queryNum * limit];
		long[] index = new long[queryNum * limit];
		int probes = 10;
		res = NativeClient.setProbe(pointer, probes);
		System.out.println("probe result:" + res);
		NativeClient.indexIVFFlat_search(pointer, queryNum, xq, limit, result, index);
		System.out.println(Arrays.toString(result));
		System.out.println(Arrays.toString(index));
		System.out.println("close:" + NativeClient.close(pointer));
		System.out.println("finish");
	}

	public static void testIndexIVFPQ() {
		int d = 64;
		int nb = 100000;
		int nq = 10000;
		float[] xb = new float[nb * d];
		float[] xq = new float[nq * d];

		Random random = new Random();
		for (int i = 0; i < nb * d; i++) {
			xb[i] = random.nextFloat();
		}
		for (int i = 0; i < nq * d; i++) {
			xq[i] = random.nextFloat();
		}
		long quantizer = NativeClient.indexFlatL2_index(d);
		int nlist = 100;
		System.out.println("quantizer:" + quantizer);
		int m = 8;
		int nbits = 8;
		long pointer = NativeClient.indexIVFPQ_index(quantizer, d, nlist, m, nbits);
		System.out.println("pointer:" + pointer);
		int res = NativeClient.indexIVFPQ_train(pointer, nb, xb);
		System.out.println("train result:" + res);
		res = NativeClient.indexIVFPQ_add(pointer, nb, xb);
		System.out.println("add result:" + res);
		int queryNum = 5;
		int limit = 4;
		float[] result = new float[queryNum * limit];
		long[] index = new long[queryNum * limit];
		int probes = 10;
		res = NativeClient.setPQProbe(pointer, probes);
		System.out.println("probe result:" + res);
		NativeClient.indexIVFPQ_search(pointer, queryNum, xq, limit, result, index);
		System.out.println(Arrays.toString(result));
		System.out.println(Arrays.toString(index));
		System.out.println("close:" + NativeClient.close(pointer));
		System.out.println("finish");
	}

	public static void init() {
		int d = 64;
		int nb = 100000;
		int nq = 10000;
		float[][] xb = new float[nb][d];
		float[][] xq = new float[nq][d];

		Random random = new Random();
		for (int i = 0; i < nb; i++) {
			for (int j = 0; j < d; j++)
				xb[i][j] = random.nextFloat();
		}
		for (int i = 0; i < nq; i++) {
			for (int j = 0; j < d; j++)
				xq[i][j] = random.nextFloat();
		}
	}

}
