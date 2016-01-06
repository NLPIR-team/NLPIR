采用附件的小工具，可以实现脱机导入用户词典；具体步骤如下：
1.与分词Data文件夹同级建立 bin目录，下面建立二级目录ICTCLAS2014;
2.将附件的内容解压缩后放在ICTCLAS2014下面；
3.编辑bin/ICTCLAS2014下面的userdic.txt，这里放置用户词典与标注；
4.执行bin/ICTCLAS2014的批处理文件。即可导入用户词典到Data目录下的field.pdat field.pos。
5.30万词条会划分更多的时间，可能需要2小时左右。
