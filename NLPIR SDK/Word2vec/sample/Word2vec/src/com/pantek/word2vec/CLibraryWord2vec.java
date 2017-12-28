package com.pantek.word2vec;

import com.sun.jna.Library;
import com.sun.jna.Native;

public interface CLibraryWord2vec extends Library{

	CLibraryWord2vec Instance=(CLibraryWord2vec) Native.loadLibrary("Word2vec", CLibraryWord2vec.class);

	public int InitWord2vec(String data,String license);
	//-train $1 -entity $2 -output vectors.bin -cbow 0 -size 200 -window 8 -negative 25 -hs 0 -sample 1e-4 -threads 20 -binary 0 -iter 15
	public int InitPara(int size,String train,String entity,int model,float alp,String outfile,int win,float sam,int h,int neg,int threads, int it,int mincount);
	
	public int Train();
	
	public int LoadModel(String model);
	
	public String CalculateWord(String word,int N);
}
