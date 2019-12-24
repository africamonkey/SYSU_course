package com.example.isszym.sqlitecv;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.support.test.InstrumentationRegistry;
import android.support.test.runner.AndroidJUnit4;
import android.util.Log;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.assertEquals;

/**
 * Instrumentation test, which will execute on an Android device.
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
@RunWith(AndroidJUnit4.class)
public class StuCvSQLTest {
    static long ind = 0;
    private static final String TAG = "测试";   // 准备好TAG标识用于LOG输出
    StuCvSQL stuCvSQL;
    Uri uri;
    @Before
    public void createUri() throws Throwable {
        uri= Uri.parse("content://com.example.provider/");
    }

    @Before
    public void createDatabse() throws Throwable {
        Context appContext = InstrumentationRegistry.getTargetContext();
        assertEquals("com.example.isszym.sqlitecv", appContext.getPackageName());
        stuCvSQL = new StuCvSQL(appContext);
        ind = stuCvSQL.getCount();
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
        ContentValues cv = new ContentValues();
        ind++;
        cv.put("num", 170000+ind);
        cv.put("name", "学生"+ind);
        stuCvSQL.insert(uri,cv);
        Log.d(TAG, "插入成功：" + 170000+ind);
    }

    @Test
    public void testUpdate() throws Throwable {
        ContentValues cv = new ContentValues();
        cv.put("name", "张三");
        int cnt=stuCvSQL.update(uri,cv,"num=?",new  String[]{"170002"});
        Log.d(TAG, "成功修改"+cnt+"个记录");
    }

    @Test
    public void testDelete() throws Throwable {
        // stuCvSQL.delete(uri,"num=?", new String[]{"170004"});
        int cnt=stuCvSQL.delete(uri, null,null); //delete All
        Log.d(TAG, "成功删除"+cnt+"个记录");
    }
    @Test
    public void testGetCount() throws Throwable {
        long count =stuCvSQL.getCount();
        Log.d(TAG, "总记录数："+count);
    }

    @Test
    public void testQuery() throws Throwable {
        // String cond="1";
        // String where="num like ? or name like ?";
        // String[] whereArgs=new String[]{"%"+cond+"%","%"+cond+"%"};
        // String sortOrder = "num";
        // Cursor cursor = stuCvSQL.query(uri,projection,where,whereArgs,sortOrder);
        String[] projection=new String[]{"_id","num","name"};
        Cursor cursor = stuCvSQL.query(uri,projection,null,null,null); //query all
        while (cursor.moveToNext()) {
            Log.d(TAG,""+cursor.getInt(cursor.getColumnIndex("_id"))
                    +" "+cursor.getString(cursor.getColumnIndex("name"))
                    +" "+cursor.getString(cursor.getColumnIndex("num")));
        }
        cursor.close();
    }
}
