package com.jiuyan.faiss;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;

public class LibUtil {

	private static final String libFaissName = "/libfaissjni.so";

	public static void main(String[] args) {
		
	}

	public static void loadFaissLib() {
		loadlibFromFile(libFaissName);
	}

	public static void loadlibFromFile(String name) {
		try {
			File temp = new File(System.getProperty("user.dir") + libFaissName);
			if (temp.exists())
				temp.delete();
			InputStream in = LibUtil.class.getResourceAsStream(name);
			byte[] buffer = new byte[1024];
			int read = -1;
			// File temp = File.createTempFile(name, "");
			FileOutputStream fos = new FileOutputStream(temp);
			while ((read = in.read(buffer)) != -1) {
				fos.write(buffer, 0, read);
			}
			fos.close();
			in.close();
			System.load(temp.getAbsolutePath());
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
