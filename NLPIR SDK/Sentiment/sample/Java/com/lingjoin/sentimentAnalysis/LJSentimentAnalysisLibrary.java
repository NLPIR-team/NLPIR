package com.lingjoin.sentimentAnalysis;

import com.lingjoin.fileutil.OSinfo;
import com.sun.jna.Library;
import com.sun.jna.Native;

public class LJSentimentAnalysisLibrary {
	/**
	 * 加载Summary的库文件
	 * @author LiYan
	 *
	 */
	public interface CLibrarySentimentAnalysis extends Library {

	CLibrarySentimentAnalysis Instance = (CLibrarySentimentAnalysis) Native.loadLibrary(
				OSinfo.getSysAndBit("LJSentimentAnalysis"), CLibrarySentimentAnalysis.class);
		
	
	 public int LJST_Inits(String path, int encode, String sLicenceCode);
	 public int LJST_ImportUserDict(String dicPath, boolean overwriter);
	 public boolean LJST_GetFileSent(String lpszFilename, byte[] szRes);
	 public boolean  LJST_GetParagraphSent(String lpszParagraph,byte[] szRes);
	 public void LJST_Exits();
	 

	}
}
