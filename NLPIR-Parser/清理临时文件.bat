del /Q *.log
del /Q /s output\机器学习分类结果\*.* output\专家规则分类结果\*.*  output\去重结果\*.* output\聚类结果\*.*
rmdir /Q /s output\机器学习分类结果 output\专家规则分类结果 output\去重结果 output\聚类结果
del /Q output\搜索结果\JZSearch*.* output\搜索结果\field*.*
del /Q output\*.*
del /Q /s output\seg\*.*
rmdir /q /s seg
del /Q  /s output\GBK\*.*
del /Q /s output\UTF8\*.*
del /Q /s output\scan\*.*
rmdir /Q /s output\GBK output\UTF8 output\scan
del output\关键词分析\Key2D.html output\关键词分析\Key3D.html  output\关键词分析\Keylist.txt  output\关键词分析\NewTermlist.txt output\关键词分析\Key_Message.xml 
del /Q log.html
del /Q RR_Data.txt
del /Q MatchWord.txt
del /Q DataFile\data.txt
del /Q DataFile\data.topic.txt
del /Q DataFile\RunLog.txt
del /Q Data\*.log
del /Q Data\*.err
del /Q Data\Data\*.log
del /Q Data\Data\*.err
del /Q *.log
del /Q *.err
del /Q *.pdb
del /Q *.ilk
