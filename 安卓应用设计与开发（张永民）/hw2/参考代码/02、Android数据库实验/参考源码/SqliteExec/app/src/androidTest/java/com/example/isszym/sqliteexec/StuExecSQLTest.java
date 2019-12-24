package com.example.isszym.sqliteexec;

import android.content.Context;
import android.database.Cursor;
import android.support.test.InstrumentationRegistry;
import android.support.test.runner.AndroidJUnit4;
import android.util.Log;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import java.util.List;

import static org.junit.Assert.assertEquals;

/**
 * Instrumentation test, which will execute on an Android device.
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
@RunWith(AndroidJUnit4.class)
public class StuExecSQLTest {
    private static final String TAG = "测试";   // 准备好TAG标识用于LOG输出
    StuExecSQL db;
    long ind = 0;
    @Test
    public void useAppContext() throws Exception {
        Context appContext = InstrumentationRegistry.getTargetContext();
        assertEquals("com.example.isszym.sqliteexec", appContext.getPackageName());
    }

    @Before
    public void createDatabse() throws Throwable {
        Context appContext = InstrumentationRegistry.getTargetContext();
        assertEquals("com.example.isszym.sqliteexec", appContext.getPackageName());
        db = new StuExecSQL(appContext);
        ind = db.getCount();;
        Log.d(TAG, "建数据库成功");
    }

    @Test
    public void testInserts() throws Throwable {
        int count = 10;
        for(int i= 0;i<count;i++){
            testInsert();
        }
    }

    @Test
    public void testInsert() throws Throwable {
        ind++;
        db.insert("17000"+ind,"学生"+ind);
        Log.d(TAG, "插入成功");
    }
    @Test
    public void testUpdate() throws Throwable {
        db.update(3,"170005", "张三");
        Log.d(TAG, "修改成功");
    }
    @Test
    public void testDelete() throws Throwable {
        db.delete(-1);
        Log.d(TAG, "删除成功");
    }
    @Test
    public void testGetCount() throws Throwable {
        Log.d(TAG, "总记录数："+db.getCount());
        //assertEquals(db.getCount(), 10);
    }
    @Test
    public void testQueryAll() throws Throwable {
        Cursor cursor = db.query("");
        while (cursor.moveToNext()) {
            Log.d(TAG, cursor.getLong(0)+" "+cursor.getString(1)+" "+cursor.getString(2));
        }
        cursor.close();
    }
}
