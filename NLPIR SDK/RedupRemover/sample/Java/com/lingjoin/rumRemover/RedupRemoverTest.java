package com.lingjoin.rumRemover;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import com.lingjoin.fileutil.FileOperateUtils;

public class RedupRemoverTest {

	public static void main(String[] args) {
		// 1、初始化
		boolean initSuccess = RedupRemoverLibrary.Instance.RR_Init("history/myHistory.txt", "",
				false, "", RedupRemoverLibrary.ENCODE_UTF8);
		if (!initSuccess) {
			System.out.println("[RedupRemover]初始化失败");
			System.out.println(RedupRemoverLibrary.Instance.RR_GetLastErrMsg());
			System.exit(-1);
		}

		System.out.println("[RedupRemover]初始化成功");

		// 2、从数据源获得数据
//				List<Text> texts = getTextsFromOther();
		List<Text> texts = getTextsFromFile("TestFiles");
		
		
		//3、开始遍历数据，查找重复的文本
		for (int i = 0; i < texts.size(); i++) {
			System.out.println("处理到第---->" + (i+1) + "/" + texts.size());
			Text text = texts.get(i);
			
			int flag = RedupRemoverLibrary.Instance.RR_FileProcess(text.getContent(), text.getTitle());
			
			/*(可选操作)3.1\返回累计已经发现的和当前文件重复的文件
			byte[] pcFindAll = new byte[65535];
			if (flag == 1) {
				RedupRemoverLibrary.Instance.RR_FindRepeat(pcFindAll, false);
				System.out.println("返回累计已经发现的和当前文件重复的文件： " + new String(pcFindAll));
			}
			*/

		}
		
		//4、输出重复结果
		String resultPath = "去重处理结果.txt";
		RedupRemoverLibrary.Instance.RR_Output(resultPath);
		
		System.out.println("查重以完成，请打开\"" + resultPath + "\"观看结果");
		
		/*(可选操作)4.1、保存查重历史数据，可用于下次加载
		  RedupRemoverLibrary.Instance.RR_SaveHistoryData("history/myHistory.txt");
		 */
		
		//5、退出
		RedupRemoverLibrary.Instance.RR_Exit();
	}

	
	private static List<Text> getTextsFromFile(String fileParentDirPath) {
		ArrayList<String> allFilesPath = FileOperateUtils.getAllFilesPath(new File(fileParentDirPath));
		List<Text> texts = new ArrayList<Text>();
		
		for ( String filePath : allFilesPath ) {
			String content = FileOperateUtils.getFileContent(filePath, "utf-8");
			String title = FileOperateUtils.getFileName(filePath);
			Text text = new Text(title, content);
			texts.add(text);
		}
		
		return texts;
	}

	// 从其他数据源获取文本，比如从数据库，这里采用模拟的方式来获取数据源
	private static List<Text> getTextsFromOther() {
		List<Text> texts = new ArrayList<Text>();
		for (int i = 0; i < 18; i++) {
			Text t = new Text();
			t.setId(i);
			t.setTitle("标题" + i);
			if (i < 5) {
				t.setContent("梨花");
			} else if (i < 10) {
				t.setContent("大众新速腾车主不接受召回方案 在美受损车辆国考最热职位竞争比达1300:1 有700余职位零报冯仑隐退江湖还是投身理想城 实惠走进校园免费送福利科技 |[第一线]苍井空做内衣电商：半数买家为男性苹果发布iOS 8.1 升级指南 iPad销量连续三个季度下滑丛林偶遇世界最大蜘蛛似幼犬 英一家人养145只动物同住时尚 | 抢镜必备“一抹蚊子血” 高圆圆周迅新婚娇美热点 | 听军事家解析时局热点 体育赛事一网打尽关注 | 协力找马航失联客机 昌平苹果甜蜜的选择");
			} else {
				t.setContent("周公恐惧流言日，王莽谦恭下士时");
			}
			System.out.println(t.getContent());
			texts.add(t);
		}
		return texts;
	}
}
