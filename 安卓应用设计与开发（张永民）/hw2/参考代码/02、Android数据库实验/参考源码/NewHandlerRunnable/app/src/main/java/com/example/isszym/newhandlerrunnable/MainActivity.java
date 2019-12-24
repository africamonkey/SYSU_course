package com.example.isszym.newhandlerrunnable;

import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    TextView mText;  int count= 0;
    Handler mHandler = new Handler(){
        @Override
        public void handleMessage(Message msg) { // 处理消息
            if (msg.what == 0x123)
                mText.setText("Hi!  -- From Sub Looper");
        }
    };
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mText = (TextView) findViewById(R.id.text0);//一个TextView
    }
    public void click1(View vw) {
        mHandler.postDelayed(r,3000);  //3秒后把r加入循环队列
    };
    public void click2(View vw) {
        mHandler.removeCallbacks(r);  //停止线程
        mText.setText("Stoped！");
    }
    Runnable r = new Runnable() {
        @Override
        public void run() {
            Message msg = mHandler.obtainMessage();
            msg.what = 0x123;
            mHandler.sendMessage(msg);
        }
    };
}
