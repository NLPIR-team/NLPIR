package com.lingjoin.fileutil;

public class OSinfo {
	private static String OS_NAME = System.getProperty("os.name").toLowerCase();
	private static String OS_ARCH = System.getProperty("os.arch").toLowerCase();

	/**
	 * 根据jdk的版本获得对应的组件路径
	 * @param moduleName 组件名(不带扩展名)
	 * @return 形式如下：linux64/组件名.扩展名、win32/组件名.扩展名
	 */
	public static String getSysAndBit(String moduleName) {
		String SysAndBit = "";//文件夹的名字
		String extension = ".dll";//扩展名
		OS_NAME = OS_NAME.toLowerCase();
		if (OS_NAME.contains("win")) {
			if (OS_ARCH.contains("86")) {
				SysAndBit = "win32/";
			} else {
				SysAndBit = "win64/";
			}
		} else {
			extension = ".so";
			System.out.println(OS_NAME);
			if (OS_ARCH.contains("86")) {
				SysAndBit = "linux32/";
			} else {
				SysAndBit = "linux64/";
			}
		}
		System.out.println(OS_NAME);
		System.out.println(OS_ARCH);
		
		return SysAndBit + moduleName + extension;
	}

}
