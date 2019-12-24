package com.example.isszym.sqlitecv;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.net.Uri;

/**
 * Created by isszym on 2018/6/26.
 */

public class StuCvSQL {
    private DBOpenHandler dbOpenHandler;
    public StuCvSQL(Context context) {
        this.dbOpenHandler = new DBOpenHandler(context, "dbStu.db3", null, 1);
    }

    public Uri insert(Uri uri,ContentValues cv) {
        SQLiteDatabase db = dbOpenHandler.getWritableDatabase();
        db.insert("stu", null, cv);
        db.close();
        return uri;
    }

    public int delete(Uri uri, String where, String[] whereArgs) {
        SQLiteDatabase db = dbOpenHandler.getWritableDatabase();
        int ret = db.delete("stu", where, whereArgs);
        db.close();
        return ret;//影响的记录数
    }

    public int update(Uri uri, ContentValues cv, String where, String[] whereArgs) {
        SQLiteDatabase db = dbOpenHandler.getWritableDatabase();
        int ret = db.update("stu", cv, where, whereArgs);
        db.close();
        return ret; //影响的记录数
    }

    public Cursor query(Uri uri, String[] projection, String where,
                                     String[] whereArgs, String sortOrder){
        SQLiteDatabase db = dbOpenHandler.getWritableDatabase();
        Cursor cursor = db.query("stu", projection, where, whereArgs,null,null,sortOrder,null);
        // db.close();
        return cursor;
    }

    public long getCount() {//得到记录总数
        SQLiteDatabase db = dbOpenHandler.getReadableDatabase();
        Cursor cursor = db.rawQuery("select count(*) from stu", null);
        cursor.moveToFirst();
        db.close();
        return cursor.getLong(0);
    }
}
