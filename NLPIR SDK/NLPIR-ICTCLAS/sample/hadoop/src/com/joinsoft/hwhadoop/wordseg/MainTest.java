package com.joinsoft.hwhadoop.wordseg;

import com.sun.jna.Native;

import java.io.IOException;

/**
 * User: xingsen
 * Date: 13-11-18
 * Time: 下午2:10
 */
public class MainTest {

    public static void main(String args[]) throws IOException {
        CLibrary cLibrary = (CLibrary) Native.loadLibrary("/work/nlpir/libNLPIR.so", CLibrary.class);
        cLibrary.NLPIR_Init("".getBytes(), 1, "0".getBytes());
        String sInput = "东方网12月4日消息：2009年10月21日,辽宁省阜新市委收到举报信,举报以付玉红为首吸毒、强奸、聚众淫乱,阜新市委政法委副书记于洋等参与吸毒、强奸、聚众淫乱等。对此,阜新市委高度重视,责成阜新市公安局立即成立调查组,抽调精干力量展开调查。　　调查期间,署名举报人上官宏祥又通过尹东方(女)向阜新市公安局刑警支队提供书面举报,举报于洋等参与吸毒、强奸、聚众淫乱。11月19日,正义网发表上官宏祥接受记者专访,再次实名举报于洋等参与吸毒、强奸、聚众淫乱,引起网民广泛关注。对此辽宁省政法委、省公安厅高度重视。当日,责成有关领导专程赴阜新听取案件调查情况。为加强对案件的督办和指导,省有关部门迅速成立工作组,赴阜新督办、指导案件调查工作,并将情况上报有关部门。　　经前一段调查证明,举报事实不存在,上官宏祥行为触犯《刑法》第243条,涉嫌诬告陷害罪。根据《刑事诉讼法》有关规定,阜新市公安局已于11月27日依法立案侦查。上官宏祥已于2009年12月1日到案,12月2日阜新市海州区人大常委会已依法停止其代表资格,阜新市公安局对其进行刑事拘留,并对同案人尹东方进行监视居住。现侦查工作正在进行中。";

        String nativeBytes = null;
        try {
            nativeBytes = cLibrary.NLPIR_ParagraphProcess(sInput, 3);
            System.out.println(nativeBytes);
        } catch (Exception ex) {
            ex.printStackTrace();
        }
        cLibrary.NLPIR_Exit();
         /*

        CLibrary instance = (CLibrary) Native.loadLibrary("/work/nlpir/libNLPIR.so", CLibrary.class);
        String argu = "";
        int charset_type = 1;

        int init_flag = instance.NLPIR_Init(argu.getBytes(), charset_type, "0".getBytes());
        if (init_flag == 0) {
            System.err.println("初始化失败！");
            return;
        }

        String sInput = "东方网12月4日消息：2009年10月21日,辽宁省阜新市委收到举报信,举报以付玉红为首吸毒、强奸、聚众淫乱,阜新市委政法委副书记于洋等参与吸毒、强奸、聚众淫乱等。对此,阜新市委高度重视,责成阜新市公安局立即成立调查组,抽调精干力量展开调查。　　调查期间,署名举报人上官宏祥又通过尹东方(女)向阜新市公安局刑警支队提供书面举报,举报于洋等参与吸毒、强奸、聚众淫乱。11月19日,正义网发表上官宏祥接受记者专访,再次实名举报于洋等参与吸毒、强奸、聚众淫乱,引起网民广泛关注。对此辽宁省政法委、省公安厅高度重视。当日,责成有关领导专程赴阜新听取案件调查情况。为加强对案件的督办和指导,省有关部门迅速成立工作组,赴阜新督办、指导案件调查工作,并将情况上报有关部门。　　经前一段调查证明,举报事实不存在,上官宏祥行为触犯《刑法》第243条,涉嫌诬告陷害罪。根据《刑事诉讼法》有关规定,阜新市公安局已于11月27日依法立案侦查。上官宏祥已于2009年12月1日到案,12月2日阜新市海州区人大常委会已依法停止其代表资格,阜新市公安局对其进行刑事拘留,并对同案人尹东方进行监视居住。现侦查工作正在进行中。";

        String nativeBytes = null;
        try {
            nativeBytes = instance.NLPIR_ParagraphProcess(sInput, 3);

            System.out.println("分词结果为： " + nativeBytes);

            int nCountKey = 0;
            String nativeByte = instance.NLPIR_GetKeyWords(sInput, 10,
                    false);

            System.out.print("关键词提取结果是：" + nativeByte);

            instance.NLPIR_Exit();
        } catch (Exception ex) {
            ex.printStackTrace();
        }*/
    }
}
