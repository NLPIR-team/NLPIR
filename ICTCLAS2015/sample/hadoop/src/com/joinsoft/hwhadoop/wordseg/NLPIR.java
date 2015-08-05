package com.joinsoft.hwhadoop.wordseg;

import com.sun.jna.Library;
import com.sun.jna.Native;

/**
 * User: xingsen
 * Date: 13-11-19
 * Time: 下午2:23
 */

public class NLPIR {
    private static CLibrary instance;

    public static void init(){
        instance = (CLibrary) Native.loadLibrary("/work/nlpir/libNLPIR.so", CLibrary.class);
    }

    public static CLibrary getInstance() {
        return instance;
    }

    public abstract interface CLibrary extends Library {
        public abstract int NLPIR_Init(byte[] paramArrayOfByte1, int paramInt, byte[] paramArrayOfByte2);

        public abstract String NLPIR_ParagraphProcess(String paramString, int paramInt);

        public abstract String NLPIR_GetKeyWords(String paramString, int paramInt, boolean paramBoolean);

        public abstract void NLPIR_Exit();
    }

}