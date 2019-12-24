package com.example.isszym.newfirstresolver;

import android.content.ContentResolver;
import android.content.ContentValues;
import android.database.Cursor;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    ContentResolver resolver;
    ContentValues cv=new ContentValues();
    Uri uri = Uri.parse("content://com.example.providers.firstprovider/");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Uri uri = Uri.parse("content://com.example.providers.firstprovider/");
        resolver = getContentResolver();
    }
    public void query(View vw) {
        Cursor c = resolver.query(uri,new String[]{"num","name"}, "_id=?", new String[]{"6"}, null);
        if(c!=null && c.moveToNext()){
            Log.d("测试","num:"+c.getString(0)+" name:"+c.getString(1));
        }
    }
    public void insert(View vw){
        cv.clear();
        cv.put("num","170001");
        cv.put("name","张三");
        Uri newUri = resolver.insert(uri,cv);  // null--错误
    }
    public void update(View vw) {
        cv.clear();
        cv.put("num","170002");
        cv.put("name","李四");
        int count = resolver.update(uri, cv, "_id=?", new String[]{"2"});// 影响的记录数
    }
    public void delete(View vw) {
        int count = resolver.delete(uri, "_id=?", new String[]{"5"}); // 影响的记录数
    }
}
