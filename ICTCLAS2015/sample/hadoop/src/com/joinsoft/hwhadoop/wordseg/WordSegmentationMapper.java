package com.joinsoft.hwhadoop.wordseg;

import com.sun.jna.Native;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

import java.io.File;
import java.io.IOException;

public class WordSegmentationMapper extends Mapper<LongWritable, Text, LongWritable, Text> {
    private CLibrary cLibrary;

    @Override
    protected void setup(Context context) throws IOException, InterruptedException {
    	System.err.println(new File(Utils.getPath("data", context.getConfiguration()).toString()));
        Utils.unzipArchive(new File(Utils.getPath("data", context.getConfiguration()).toString()));
        System.err.println(Utils.getRootPath() + "/libNLPIR.so");
        cLibrary = (CLibrary) Native.loadLibrary(Utils.getRootPath() + "/libNLPIR.so", CLibrary.class);
        cLibrary.NLPIR_Init("/work/nlpir".getBytes(), 1, "0".getBytes());
    }

    @Override
    protected void cleanup(Context context) throws IOException, InterruptedException {
        super.cleanup(context);
        cLibrary.NLPIR_Exit();
        Utils.cleanFile();
    }

    @Override
    protected void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
        try {
            String nativeBytes = NLPIR.getInstance().NLPIR_ParagraphProcess(value.toString(), 3);
            context.write(key, new Text(nativeBytes));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
