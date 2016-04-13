#搜索调用
功能：对索引接口调用的封装


##方法列表：
```
search_all();查询所有数据
search_and(String,String..) 逻辑 且
...详见方法注释
```

##调用步骤：
    引入jar包
    新建LJSearch对象
    调用对象的成员函数，运行set_*与search_*方法，进行功能设置
	运行run()方法，执行搜索，返回值类型为List<Map<String,String>>
##示例： 
		LJSearch a = new LJSearch();
		a.search_all();
		a.set_unique("id");
		List<Map<String,String>> res = a.run();
		System.out.println(res);