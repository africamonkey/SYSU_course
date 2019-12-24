package com.example.isszym.newfirstresolver;

import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.support.test.InstrumentationRegistry;
import android.support.test.runner.AndroidJUnit4;
import android.util.Log;
import android.view.View;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import static java.security.AccessController.getContext;
import static org.junit.Assert.assertEquals;

/**
 * Instrumentation test, which will execute on an Android device.
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
@RunWith(AndroidJUnit4.class)
public class ResolverTest {
    ContentResolver resolver;
    ContentValues cv = new ContentValues();
    Uri uri = Uri.parse("content://com.example.providers.firstprovider/");
    @Before
    public void useAppContext() throws Exception {
        // Context of the app under test.
        Context appContext = InstrumentationRegistry.getTargetContext();
        assertEquals("com.example.isszym.newfirstresolver", appContext.getPackageName());
        resolver = appContext.getContentResolver();
    }

    @Test
    public void query() {
        Cursor c = resolver.query(uri,new String[]{"num","name"}, "_id=?", new String[]{"6"}, null);
        if(c!=null && c.moveToNext()){
            Log.d("测试","num:"+c.getString(0)+" name:"+c.getString(1));
        }
    }

    @Test
    public void insert(){
        cv.clear();
        cv.put("num","170001");
        cv.put("name","张三");
        Uri newUri = resolver.insert(uri,cv);  // null--错误
    }
    @Test
    public void update() {
        cv.clear();
        cv.put("num","170002");
        cv.put("name","李四");
        int count = resolver.update(uri, cv, "_id=?", new String[]{"2"});// 影响的记录数
    }
    @Test
    public void delete() {
        int count = resolver.delete(uri, "_id=?", new String[]{"5"}); // 影响的记录数
    }

}
