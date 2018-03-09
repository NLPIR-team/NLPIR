package com.pantek.test;

import com.pantek.word2vec.CLibraryWord2vec;

public class Word2vec {

	public static void main(String[] args){
		int i=CLibraryWord2vec.Instance.InitWord2vec("Data/","");
		System.out.println(i);
		CLibraryWord2vec.Instance.InitPara(200, "corpus.txt", "words-all.txt", 1, Float.parseFloat("0.025"), "vectors.txt", 8, Float.parseFloat("1e-4"), 1, 25, 1, 15, 1);
		CLibraryWord2vec.Instance.Train();
		CLibraryWord2vec.Instance.LoadModel("vectors.txt");
		String result=CLibraryWord2vec.Instance.CalculateWord("中国",10);
		String result1=CLibraryWord2vec.Instance.CalculateWord("秘鲁",10);
		System.out.println(result);
		System.out.println(result1);
	}
}