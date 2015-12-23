package com.joinsoft.hwhadoop.wordseg;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;


import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

public class WordSegmentationJob {
    public static void main(String args[]) throws IOException {
        Configuration conf = new Configuration();
        try {
        	System.err.println(conf + "\n");
            String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
            if (otherArgs.length != 2) {
                System.err.println("Usage: word-seg <in> <out>");
                System.exit(2);
            }
            Utils.putClassFile("jna-4.0.0.jar", conf);
            Utils.putFile(new URI("data.zip"), conf);
            //NLPIR.init();
            //NLPIR.getInstance().NLPIR_Init("/work/nlpir".getBytes(), 1, "0".getBytes());

            Job job = new Job(conf, "word-seg");
            job.setJarByClass(WordSegmentationJob.class);
            //job.setNumReduceTasks(6);//0.97*(core*nodes)
            job.setMapperClass(WordSegmentationMapper.class);
            job.setInputFormatClass(TextInputFormat.class);
            job.setReducerClass(WordSegmentationReduce.class);
            FileInputFormat.addInputPath(job, new Path(otherArgs[0]));
            FileOutputFormat.setOutputPath(job, new Path(otherArgs[1]));
            System.exit(job.waitForCompletion(true) ? 0 : 1);
        } catch (IOException e) {
            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
        } catch (InterruptedException e) {
            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
        } catch (ClassNotFoundException e) {
            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
        } catch (URISyntaxException e) {
            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
        }
    }
}
