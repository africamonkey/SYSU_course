package com.example.isszym.myapplication;

import android.content.ComponentName;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.content.Intent;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
    public void clickHandler1(View source) {
        Intent intent = new Intent(this,SecondActivity.class);
        intent.putExtra("parm","*Hello From Activity 1!");
        startActivity(intent);
    }
    public void clickHandler2(View source) {
        Intent intent = new Intent();
        intent.putExtra("parm","**Hello From Activity 1!");
        intent.setAction("com.example.startact.SECONDACT");
        startActivity(intent);
    }
    public void clickHandler3(View source) {
        Intent intent = new Intent("com.example.startact.THIRDACT");
        intent.putExtra("parm","***Hello From Activity 1!");
        startActivityForResult(intent,1);
    }
    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent intent){
        if(requestCode==1 && resultCode==2){
            TextView tv = (TextView) findViewById(R.id.infoView);
            tv.setText(intent.getStringExtra("res"));
            finishActivity(1); //结束以启动码启动的Activity
        }
    }
    public void clickHandler4(View source) {
        Intent intent  = new Intent("com.example.startedact.MAIN");   // 参数：Action
        intent.putExtra("parm","****Hello From Activity 1!");
        startActivity(intent);
    }
    public void clickHandler5(View source) {
       Intent intent = new Intent();
       intent.setClassName("com.example.isszym.newstartedactivity", "com.example.isszym.newstartedactivity.MainActivity");
       intent.putExtra("parm","*****Hello From Activity 1!");
       startActivity(intent);
    }
}



