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
        String sInput="����������5��12�յ� (���� ����) ���ǿ����12�ճ�ϯȫ���ƽ�������Ȩ�Źܽ��ְ��ת�乤�����ӵ绰����ʱ˵������Ⱥ�ڶ�����֮�׸�������Ը�ʲô����θ����з���Ȩ��Ҫ���Ÿ�ĸ���������š��˲ˡ���Ϊ����Ⱥ�ڡ���ˡ�����Ⱥ������Ϊ���򣬴ӷ�ӳͻ���������֡�		�������ǿ����������ǡ����������������������С����������Ȩ�������ԡ��ı���������˵���ݹ��й���ʷ����ʢ�����������Ӿ��м򡱡����污��������ʩ��Ҫ�壬�����Ծ���֮���м���֮����		�������ǿ������������������Ȩ�ص㹤���ǣ��ٿ���һ����������ٿ���һ�������н�����ٿ���һ�����������еķ����Ƚڣ��ٿ���һ����ҵ�Ǽ�ע��Ͱ��µĹؿ����ٿ���һ�����Ϸ����Ϲ治������շѡ�		�������ǿ����˵����ʱ�ڵ���������Ƹĸת������ְ��Ҫ������Ȩ���Źܽ�ϡ��Ż�����ͬʱ�ƽ����ӿ콨�跨������������������������������������������ʵ���������������ִ�����";
        v.setText(TestSummary.test("/sdcard", sInput));
        //Data�ļ��д洢���ֻ��ĸ�Ŀ¼�£��ǵñ�֤�пɶ�Ȩ�ޡ�
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
}


