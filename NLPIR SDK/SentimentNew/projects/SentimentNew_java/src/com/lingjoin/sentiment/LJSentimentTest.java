package com.lingjoin.sentiment;

public class LJSentimentTest {
    public static void main(String[] args) {
        System.out.println("初始化开始...");
        if (CLibrarySentiment.Instance.ST_Init("", 1, "") == 0) {
            System.out.println(CLibrarySentiment.Instance.ST_GetLastErrMsg());
            System.out.println("初始化失败");
            System.exit(1);
        } else {
            System.out.println("初始化成功");
        }

        int num = CLibrarySentiment.Instance.ST_ImportUserDict("sentilexicon.txt", 0);
        System.out.printf("添加用户单词%d个\n", num);

        String sTitle = "奥巴马与美防长商打击IS战略 称不会“速战速决”";
        String sContent = "据美媒报道，当地时间6日，美国总统奥巴马前往美国国防部，与国防部长卡特等商讨如何改善击败“伊斯兰国”武装分子的战略。奥巴马承认美国目前缺乏一个“完整战略”。并表示，打击“伊斯兰国”之战不会是“速战速决”据报道，美国领导的联军上周末对控制伊拉克西北部和叙利亚东部大片地区的激进分子进行了38次空袭，其中近一半的空袭目标锁定在“伊斯兰国”自行宣布的首都拉卡周围地区。美国领导的盟军去年8月和9月先后开始对伊拉克和叙利亚境内目标展开空袭。据美国国防部说，到目前为止，联军至少进行了4800次空袭，帮助伊拉克军队和叙利亚境内武装收复一些失地。奥巴马说，打击“伊斯兰国”极端分子的战斗将是长期而艰苦的，要想赢得胜利，需要的将不只是美国军事力量。奥巴马提到了持续的多边行动，包括联军部队从空中打击“伊斯兰国”，同时采取行动切断该组织的资金来源，并强化地方部队在伊拉克和其他地方展开地面行动。奥巴马指出，“伊斯兰国”主动接触包括在美国等遥远地方的潜在新兵，并表示击败“伊斯兰国”将不能只靠军事力量。据悉，联军去年八月在伊拉克展开空袭，一个月后扩展到叙利亚。根据白宫的数据，目前总的空袭次数已经超过5000次，官员们说空袭行动帮助了伊拉克部队和叙利亚战斗人员从激进分子手中收复了一些失地。报道称，但是进展一直是有限的，伊拉克军队仍然无法在夺取北部和西部城市的地面战斗中赢得大规模胜利。伊拉克部队在诸如争夺安巴尔省的战斗等行动中得到了伊朗支持的民兵和库尔德武装人员的帮助。到目前为止，奥巴马一直拒绝向伊拉克派遣美国地面部队的要求，而是派遣了顾问和培训人员来训练和加强伊拉克部队。";

        System.out.println(CLibrarySentiment.Instance.ST_GetOneObjectResult(sTitle, sContent, "奥巴马"));
        System.out.println(CLibrarySentiment.Instance.ST_GetMultiObjectResult(sTitle, sContent, "stConduct.xml"));
        System.out.println(CLibrarySentiment.Instance.ST_GetSentencePoint(sContent));

        CLibrarySentiment.Instance.ST_Exit();

        System.exit(0);

    }
}
