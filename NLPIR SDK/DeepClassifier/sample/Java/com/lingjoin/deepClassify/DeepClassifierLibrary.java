package com.lingjoin.deepClassify;


import com.lingjoin.fileutil.OSinfo;
import com.sun.jna.Library;  
import com.sun.jna.Native;

public interface DeepClassifierLibrary extends Library{

		DeepClassifierLibrary Instance  = 
				(DeepClassifierLibrary)Native.loadLibrary(OSinfo.getSysAndBit("DeepClassifier"), DeepClassifierLibrary.class);

	    /**
	     * @param sDataPath
	     * @param encode
	     * @param nFeatureCount 特征词，默认是800
	     * @param sLicenceCode
	     * @return
	     */
	    public boolean DC_Init(String sDataPath,int encode,int nFeatureCount,String sLicenceCode);
	    public boolean DC_Exit();
	    
	    public boolean  DC_AddTrain(String sClassName,String sText);
	    public boolean DC_AddTrainFile(String sClassName,String sFilePath);
	    
        public boolean  DC_Train();
        public boolean  DC_LoadTrainResult();
        
        public String DC_Classify(String sText);
        public String DC_ClassifyFile(String sFilename);
        public String DC_GetLastErrorMsg();
        
        
        public static final int ENCODING_GBK = 0;
        public static final int ENCODING_UTF8 = 1;
}
