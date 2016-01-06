package com.joinsoft.hwhadoop.wordseg;

import com.sun.jna.Library;

public abstract interface CLibrary extends Library {
    public abstract int NLPIR_Init(byte[] paramArrayOfByte1, int paramInt, byte[] paramArrayOfByte2);

    public abstract String NLPIR_ParagraphProcess(String paramString, int paramInt);

    public abstract String NLPIR_GetKeyWords(String paramString, int paramInt, boolean paramBoolean);

    public abstract void NLPIR_Exit();
}
