package com.lingjoin.summary;


/**
 * 摘要生成组件的简单实用
 * 
 * @author lingjoin
 *
 */
public class SummaryTest {

	public static void main(String[] args) {
		// 初始化
		boolean flag = CLibraryDS.Instance.DS_Init("", 1, "0");
		if (flag == false) {// 如果初始化失败，就打印出失败原因
			System.out.println(CLibraryDS.Instance.DS_GetLastErrMsg());
		}
		
		// 文本内容
		// String content =
		// "10月27日，在山东省无棣县劳动就业处培训中心，部分创业人员正在辅导老师的指导下完善自己刚建的淘宝店铺。为激励青年创业的积极性，该县劳动就业处从今年6月份开始分期分批免费对初始创业人员进行电子商务创业培训，使其熟练掌握电子商务相关知识。截至目前，超过3000人完成技能培训，就业率达到95%。本报记者徐烨摄《 人民日报 》（ 2014年10月28日 10 版）";
		// String content = FileOperateUtils.getFileContent("sm1.txt");
		String content = "对于有的粉丝，我真的无语了！大家都为姚贝娜感到惋惜，都觉得太可惜了。但有歌迷的观点真的让人无语，说什么:吴奇隆在姚贝娜追悼会的时候结婚，这样好吗？首先吴刘跟姚的不幸有半毛钱关系啊;其次难道说姚的不幸，全中国有人结婚都得为这事让行？";
		System.out.println("原内容： " + content);
		System.out.println("原内容长度： " + content.length());
		String summary = CLibraryDS.Instance
				.DS_SingleDoc(content, 0, 100, true);
		System.out.println("摘要为： " + summary);
		System.out.println(summary.length());
		
		CLibraryDS.Instance.DS_Exit();
	}

}
