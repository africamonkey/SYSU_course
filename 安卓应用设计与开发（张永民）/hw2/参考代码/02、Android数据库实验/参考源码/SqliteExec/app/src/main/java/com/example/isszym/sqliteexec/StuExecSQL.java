package com.example.isszym.sqliteexec;

import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by isszym on 2018/6/26.
 */

public class StuExecSQL {
    private DBOpenHandler dbOpenHandler;
    public StuExecSQL(Context context) {
        this.dbOpenHandler = new DBOpenHandler(context, "dbStu.db3", null, 2);
    }
    public void insert(String num,String name) {
        SQLiteDatabase db = dbOpenHandler.getWritableDatabase();
        db.execSQL("INSERT INTO stu(num,name) values(?,?)",
                new Object[]{num, name});
        db.close();// 记得关闭数据库操作
    }

    public void delete(Integer id) {
        SQLiteDatabase db = dbOpenHandler.getWritableDatabase();
        if(id<0)
            db.execSQL("DELETE FROM stu");
        else
            db.execSQL("DELETE FROM stu WHERE _id=?", new Object[]{id.toString()});
        db.close();
    }

    public void update(int id, String num,String name) {
        SQLiteDatabase db = dbOpenHandler.getWritableDatabase();
        db.execSQL("UPDATE stu SET num=?,name=? WHERE" + " _id=?",
                new Object[]{num, name, id});
        db.close();
    }

    public Cursor query(String cond) {
        SQLiteDatabase db = dbOpenHandler.getReadableDatabase();
        Cursor cursor = (cond.isEmpty())?
                db.rawQuery("select * from stu",null):
                db.rawQuery("select * from stu where num like ? or name like ?",
                         new String[]{"%"+cond+"%","%"+cond+"%"},null);
        return cursor;
    }

    public long getCount() {//得到记录总数
        SQLiteDatabase db = dbOpenHandler.getReadableDatabase();
        Cursor cursor = db.rawQuery("select count(*) from stu", null);
        cursor.moveToFirst();
        long count = cursor.getLong(0);
        db.close();
        return count;
    }
}
