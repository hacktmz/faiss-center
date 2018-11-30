package com.jiuyan.faiss.test;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import com.jiuyan.faiss.NativeClient;

public class TestObj {

	public static void main(String[] args) {
		work();

	}

	public static void work() {
		createGoodTest();
	}

	private static String feature = "-0.166455,0.0406419,0.0402817,-0.0602767,-0.135213,-0.0246784,0.0652787,-0.0194206,0.142492,-0.0861569,-0.0250113,0.0547447,0.0377376,-0.0477866,-0.0242939,0.0234228,-0.0863714,-0.0172724,0.0177033,0.019603,-0.050257,-0.111406,-0.0635887,-0.0470894,0.0688086,-0.0311973,-0.0761647,0.131747,0.0228038,-0.00666597,0.0871386,0.115635,-0.0878481,0.0486074,0.052911,0.0735497,-0.017541,0.0928399,-0.0750821,-0.00565579,-0.0998317,-0.00614963,-0.110776,-0.0284818,0.0859847,-0.176474,-0.17809,-0.0504785,-0.0666749,0.163489,0.0293375,0.0108829,-0.00578756,0.106355,-0.19552,0.0840736,0.091905,-0.011478,0.013916,-0.119816,0.0348594,0.059892,-0.101814,-0.0272222,0.0554259,-0.15945,0.0929911,0.113808,-0.0744665,0.0542037,0.00783362,-0.0241434,-0.0849241,0.034896,0.065025,-0.0629758,0.0255089,-0.076136,-0.17022,0.10423,0.0499146,0.0259636,-0.0534917,0.0278168,0.0984355,-0.0959714,0.0287385,0.108817,0.0971581,0.0806672,0.128403,-0.0880719,-0.0748668,0.195457,0.122448,0.164391,-0.159745,-0.122322,0.0276164,-0.161425,0.0348159,0.104112,-0.0446866,0.122242,-0.137913,0.0288988,0.075046,-0.0163142,-0.0824408,0.0241588,-0.119762,-0.126139,-0.0503873,0.0135842,-0.0916408,0.203199,-0.005178,0.0428602,0.107876,-5.76252E-5,0.0157971,0.112836,0.113701,-0.0549851,-0.0709477,-0.123236,0.0773444,-0.0419137";
	private static String dirName = "/home/xiaohua/data/faissdata/";
	private static long pointerGoodObject;
	private static int highProbe = 50;
	private static int d = 128;

	private static void createGoodTest() {
		try {
			BufferedReader reader = new BufferedReader(
					new InputStreamReader(new FileInputStream(dirName + "feature_good.txt"), Charset.forName("utf-8")));
			int nlist = 200;
			int metricType = 1;
			int goodObjectNum = 0;
			long quantizerGoodObject = NativeClient.indexFlatL2_index(d);
			pointerGoodObject = NativeClient.indexIVFFlat_index(quantizerGoodObject, d, nlist, metricType);
			int rspProbe = NativeClient.setProbe(pointerGoodObject, highProbe);
			System.out.println("faiss pointerGoodObject:" + pointerGoodObject + ";rsp probe:" + rspProbe);
			List<Float> objectList = new ArrayList<Float>();
			int objectId = 0;
			List<String> urlList = new ArrayList<String>();
			while (reader.ready()) {
				String line = reader.readLine();
				if (line.equals(""))
					continue;
				String[] ss = line.split(" ");
				String info = ss[1];
				if (ss.length > 4) {
					for (int i = 4; i < ss.length; i = i + 2) {
						// object_position object_hash
						String objectHash = ss[i + 1];
						String objectFeature = objectHash.substring(12, objectHash.length());
						String[] objArr = objectFeature.split(",");
						for (int j = 0; j < objArr.length; j++) {
							float f = Float.parseFloat(objArr[j]);
							objectList.add(f);
						}
						String[] us = info.split("\"url\":\"");
						String url = us[1];
						int end = url.indexOf(".jpg");
						url = url.substring(0, end + 4);
						urlList.add(url);
						objectId++;
						goodObjectNum++;
					}
				}
			}
			if (goodObjectNum > 0)
				addIndex(pointerGoodObject, objectList, goodObjectNum);
			reader.close();
			// query
			float[] xq = new float[d];
			String[] ss = feature.split(",");
			for (int i = 0; i < d; i++)
				xq[i] = Float.parseFloat(ss[i]);
			int queryNum = 1;
			int limit = 4;
			float[] result = new float[queryNum * limit];
			long[] index = new long[queryNum * limit];
			NativeClient.indexIVFFlat_search(pointerGoodObject, queryNum, xq, limit, result, index);
			System.out.println(Arrays.toString(result));
			System.out.println(Arrays.toString(index));
			for (int i = 0; i < index.length; i++) {
				System.out.println(urlList.get((int) index[i]));
			}
			System.out.println("close:" + NativeClient.close(pointerGoodObject));
			System.out.println("finish");
		} catch (Exception e) {
			e.printStackTrace();
		}

	}

	private static void addIndex(long pointer, List<Float> imageList, int num) {
		float[] imageArr = new float[imageList.size()];
		for (int i = 0; i < imageList.size(); i++)
			imageArr[i] = imageList.get(i);
		int trainRsp = NativeClient.indexIVFFlat_train(pointer, num, imageArr);
		int addRsp = NativeClient.indexIVFFlat_add(pointer, num, imageArr);
		System.out.println("pointer:" + pointer + ";train rsp:" + trainRsp + ";add rsp:" + addRsp);
		imageList.clear();
	}
}
