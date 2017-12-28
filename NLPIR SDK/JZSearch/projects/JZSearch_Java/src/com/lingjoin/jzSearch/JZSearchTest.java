package com.lingjoin.jzSearch;

import java.util.List;
import java.util.Map;
import java.util.Set;

import org.junit.Test;

import com.lingjoin.constant.Constant;
import com.lingjoin.fileutil.ReadConfigUtil;
import com.lingjoin.fileutil.XMLUtil;

public class JZSearchTest {


	private static final String dataDirPath = ReadConfigUtil.getValue("dataDirPath");
	private static final String fieldFilePath = ReadConfigUtil.getValue("fieldFilePath");
	private static final String indexFilePath = ReadConfigUtil.getValue("indexFilePath");
	
	/**
	 * 向字段文件中添加字段
	 */
	@Test
	public void addField() {
		int flag = CLibraryJZSearch.Instance.JZIndexer_Init(dataDirPath, "", 1);
		if (flag != 0) {
			System.out.println("JZSearch初始化成功");
		} else {
			System.out.println("JZSearch初始化失败!!!!!!!!!!!!!!");
			System.exit(-1);
		}
		CLibraryJZSearch.Instance.JZIndexer_FieldAdd("ID", null,2, true, true, true, true);
		CLibraryJZSearch.Instance.JZIndexer_FieldAdd("value", null,1, true, true, true, true);
		//保存字段信息
		boolean saveSuccess = CLibraryJZSearch.Instance.JZIndexer_FieldSave(fieldFilePath);
		
		if ( saveSuccess ) {
			System.out.println("JZSearch添加字段成功。。。");
		} else {
			System.out.println("JZSearch添加字段失败。。。");
		}
		CLibraryJZSearch.Instance.JZIndexer_Exit();
	}
	
	@Test
	/**
	 * 添加索引
	 */
	public void index() {
		int flag = CLibraryJZSearch.Instance.JZIndexer_Init(dataDirPath, fieldFilePath, 1);
		if (flag != 0) {
			System.out.println("JZSearch初始化成功");
		} else {
			System.out.println("JZSearch初始化失败!!!!!!!!!!!!!!");
			System.exit(-1);
		}
		
		int handle = CLibraryJZSearch.Instance.JZIndexer_NewInstance(indexFilePath, 512000000);
		if ( handle <= -1 ) {
			System.out.println("添加索引---NewInstance失败！");
			System.exit(-1);
		} 
		
		System.out.println("添加索引---NewInstance成功！");
		String[] names = {"张亚鹏", "王生", "精卫", "哪吒", "柳传志", "胡歌", "聂小倩", "宁采臣", "令狐冲", "任盈盈", "张无忌", "赵敏", "周芷若", "张三丰", "蔺相如", "曹操", "西门庆", "潘金莲", "武松", "吴刚", "李寻欢"};
		
		for ( int i = 0; i < names.length; i++ ) {
			CLibraryJZSearch.Instance.JZIndexer_IntIndexing(handle, i, "ID");
			CLibraryJZSearch.Instance.JZIndexer_MemIndexing(handle, names[i], "value", 0);		
			System.out.println(" 索引内容 id："+i+"value"+names[i]);
			if ( CLibraryJZSearch.Instance.JZIndexer_AddDoc(handle) < 1 ) {
				System.out.println(" : 索引添加失败！");
				System.exit(-1);
			} else {
				System.out.println(" : 索引添加成功！");
			}
		}
		
		CLibraryJZSearch.Instance.JZIndexer_Save(handle);
		CLibraryJZSearch.Instance.JZIndexer_DeleteInstance(handle);
		CLibraryJZSearch.Instance.JZIndexer_Exit();
		System.out.println("索引建立完成");
	}

	@Test
	/**
	 * 搜索
	 */
	public void testFinerSegment() throws Exception {
		int searcher_handle = CLibraryJZSearch.Instance.JZSearch_Init(indexFilePath, dataDirPath, fieldFilePath, 512000000, 1, 0, false, 1, "");
		if (searcher_handle != -1) {
			System.out.println("jzsearch初始化成功");
		} else {
			System.out.println("jzsearch初始化失败!!!!!!!!!!!!!!");
			System.exit(-1);
		}
		
		int handle = CLibraryJZSearch.Instance.JZSearcher_NewInstance(1, searcher_handle);
		String query_line = "[FIELD] contentall [AND] 人工服务 [FIELD] date [RANG] 1 123431234";
		//-1 表示搜索全部
		String xml = CLibraryJZSearch.Instance.JZSearcher_Search(handle, query_line, 0, 10);
		System.out.println(xml);
//		List<Map<String, String>> docInfos = XMLUtil.parseDBXML(xml);
//		for ( Map<String, String> docInfo : docInfos ) {
//			System.out.println("===================================================================================");
//			Set<String> keySet = docInfo.keySet();
//			for ( String key : keySet ) {
//				System.out.println(key + ": " + docInfo.get(key));
//			}
//		}
	}
	
	@Test
	/**
	 * 导出词频
	 */
	public void testExportTF() throws Exception {
		int searcher_handle = CLibraryJZSearch.Instance.JZSearch_Init(indexFilePath, dataDirPath, fieldFilePath, 512000000, 1, 0, false, 1, "");
		if (searcher_handle != -1) {
			System.out.println("jzsearch初始化成功");
		} else {
			System.out.println("jzsearch初始化失败!!!!!!!!!!!!!!");
			System.exit(-1);
		}
		
		int result = CLibraryJZSearch.Instance.JZSearch_ExportTF("dasdfd", searcher_handle);
		if (result > -1) {
			System.out.println("导出成功");
		} else {
			System.out.println("导出失败!!!!!!!!!!!!!!");
			System.exit(-1);
		}
	}

}
