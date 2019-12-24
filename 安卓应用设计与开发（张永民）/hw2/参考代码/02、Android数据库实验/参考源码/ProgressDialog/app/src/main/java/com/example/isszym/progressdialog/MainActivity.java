package com.example.isszym.progressdialog;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.app.ProgressDialog;
import android.os.Handler;
import android.os.Message;
import android.view.View;

public class MainActivity extends AppCompatActivity {
    final static int MAX_PROGRESS = 100;  // 该程序模拟填充长度为100的数组
    private int[] data = new int[50];
    int progressStatus = 0;  // 记录进度对话框的完成百分比
    int hasData = 0;
    ProgressDialog pd1,pd2;
    Handler handler = new Handler() {
        @Override
        public void handleMessage(Message msg) {  // 定义一个负责更新的进度的Handler
            if (msg.what == 0x123){  // 表明消息是由该程序发送的
                pd2.setProgress(progressStatus);
            }
        }
    };
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
    public void showSpinner(View source) {        // 调用静态方法显示环形进度条
        ProgressDialog.show(this, "任务执行中"
                , "任务执行中，请等待", false, true); // ①
    }
    public void showIndeterminate(View source) {
        pd1 = new ProgressDialog(MainActivity.this);
        pd1.setTitle("任务正在执行中");  // 设置对话框的标题
        pd1.setMessage("任务正在执行中，敬请等待..."); // 设置对话框显示的内容
        pd1.setCancelable(true);  // 设置对话框能用“取消”按钮关闭
        pd1.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);  // 设置对话框的进度条风格
        pd1.setIndeterminate(true);   // 设置对话框的进度条是否显示进度
        pd1.show(); // ②
    }
    public void showProgress(View source) {
        progressStatus = 0;   // 将进度条的完成进度重设为0
        hasData = 0;   // 重新开始填充数组
        pd2 = new ProgressDialog(MainActivity.this);
        pd2.setMax(MAX_PROGRESS);
        pd2.setTitle("任务完成百分比");   // 设置对话框的标题
        pd2.setMessage("耗时任务的完成百分比");  // 设置对话框显示的内容
        pd2.setCancelable(false);   // 设置对话框不能用“取消”按钮关闭
        pd2.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
        pd2.setIndeterminate(false);          // 设置对话框的进度条是否显示进度
        pd2.show(); // ③
        new Thread()   {
            public void run() {
                while (progressStatus < MAX_PROGRESS) {
                    progressStatus = MAX_PROGRESS  * doWork() / data.length;   // 获取耗时操作的完成百分比
                    handler.sendEmptyMessage(0x123); // 发送空消息到Handler
                }
                if (progressStatus >= MAX_PROGRESS) {  // 如果任务已经完成
                    pd2.dismiss();   // 关闭对话框
                }
            }
        }.start();
    }
    // 模拟一个耗时的操作
    public int doWork() {
        data[hasData++] = (int) (Math.random() * 100);
        try {
            Thread.sleep(100);
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
        return hasData;
    }
}
