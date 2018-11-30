package com.jiuyan.faiss.test;

import java.util.Arrays;
import java.util.Random;

import com.jiuyan.faiss.client.IndexFlatL2;
import com.jiuyan.faiss.client.IndexIVFFlat;
import com.jiuyan.faiss.client.SearchResponse;

public class IndexTest {

	public static void main(String[] args) {
		testIndexL2();
		testIndexIVF();
	}

	public static void testIndexL2() {
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
		for (int i = 0; i < d; i++) {
			for (int j = 0; j < d; j++)
				xq[i][j] = random.nextFloat();
		}
		IndexFlatL2 l2 = new IndexFlatL2(d);
		int ret = l2.add(nb, xb);
		System.out.println("pointer:" + l2.getPointer());
		System.out.println("add result:" + ret);
		int queryNum = 5;
		int limit = 4;
		SearchResponse rsp = l2.search(queryNum, xq, limit);
		float[][] rspData = rsp.getRspData();
		long[][] rspIndex = rsp.getRspIndex();
		for (int i = 0; i < queryNum; i++) {
			System.out.println(Arrays.toString(rspData[i]));
			System.out.println(Arrays.toString(rspIndex[i]));
		}
		System.out.println("close:" + l2.close());
		System.out.println("finish");
	}

	public static void testIndexIVF() {
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
		for (int i = 0; i < d; i++) {
			for (int j = 0; j < d; j++)
				xq[i][j] = random.nextFloat();
		}
		int nlist = 100;
		IndexIVFFlat ivf = new IndexIVFFlat(d, nlist);
		int trainRet = ivf.train(nb, xb);
		int addRet = ivf.add(nb, xb);
		System.out.println("pointer:" + ivf.getPointer());
		System.out.println("train result:" + trainRet);
		System.out.println("add result:" + addRet);
		int queryNum = 5;
		int limit = 4;
		int probes = 10;
		ivf.setProbes(probes);
		SearchResponse rsp = ivf.search(queryNum, xq, limit);
		float[][] rspData = rsp.getRspData();
		long[][] rspIndex = rsp.getRspIndex();
		for (int i = 0; i < queryNum; i++) {
			System.out.println(Arrays.toString(rspData[i]));
			System.out.println(Arrays.toString(rspIndex[i]));
		}
		System.out.println("close:" + ivf.close());
		System.out.println("finish");
	}

}
