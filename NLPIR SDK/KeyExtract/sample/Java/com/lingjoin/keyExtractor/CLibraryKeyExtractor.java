package com.lingjoin.keyExtractor;

import com.lingjoin.fileutil.OSinfo;
import com.sun.jna.Library;
import com.sun.jna.Native;

/**
 * 关键词提取组件
 * @author tsg
 *
 */
public interface CLibraryKeyExtractor extends Library {

	public CLibraryKeyExtractor instance = (CLibraryKeyExtractor) Native.loadLibrary(OSinfo.getSysAndBit("KeyExtract"), CLibraryKeyExtractor.class);
	
	public boolean KeyExtract_Init( String sDataPath, int encode, String sLicenceCode);
	
	public boolean KeyExtract_Exit();

	public String KeyExtract_GetKeyWords(String sLine, int nMaxKeyLimit, boolean bWeightOut);
	
	public String KeyExtract_GetFileKeyWords(String sFilename, int nMaxKeyLimit, boolean bWeightOut);

}
