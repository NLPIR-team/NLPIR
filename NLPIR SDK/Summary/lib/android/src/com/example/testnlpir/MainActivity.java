package com.example.testnlpir;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.TextView;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView v = (TextView)findViewById(R.id.helloText);
        String sInput="中新网北京5月12日电 (记者 蒋涛) 李克强总理12日出席全国推进简政放权放管结合职能转变工作电视电话会议时说，人民群众对审批之弊感受最深，对改什么、如何改最有发言权。要开门搞改革，从政府部门“端菜”变为人民群众“点菜”，以群众需求为导向，从反映突出问题入手。		　　李克强总理引《礼记》《论语》详解政府工作报告中“大道至简，有权不可任性”的表述。总理说，纵观中国历史，凡盛世往往都“居敬行简”、轻徭薄赋，政府施政要义，在于以敬民之心行简政之道。		　　李克强总理提出，今年简政放权重点工作是：再砍掉一批审批事项，再砍掉一批审批中介事项，再砍掉一批审批过程中的繁文缛节，再砍掉一批企业登记注册和办事的关卡，再砍掉一批不合法不合规不合理的收费。		　　李克强总理说，新时期的深化行政体制改革、转变政府职能要简政放权、放管结合、优化服务同时推进，加快建设法治政府、创新政府、廉洁政府、服务型政府，逐步实现政府治理能力现代化。";
        v.setText(TestSummary.test("/sdcard", sInput));
        //Data文件夹存储在手机的根目录下，记得保证有可读权限。
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
}


