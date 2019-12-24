package com.example.isszym.newfirstprovider;

import android.content.ContentProvider;
import android.content.ContentValues;
import android.database.Cursor;
import android.net.Uri;
import android.util.Log;

public class FirstProvider extends ContentProvider{
     @Override
    public boolean onCreate()  {
        System.out.println("===onCreate is called==="); return true;
    }

    @Override
    public String getType(Uri uri){    // 返回本ContentProvider所提供数据的MIME类型
        System.out.println("~~getType is called~~"+sh(uri)); return null;
    }

    @Override
    public Cursor query(Uri uri, String[] projection, String where,String[] whereArgs, String sortOrder) {
        System.out.println("===query is called==="+projection[0]+sh(uri)); return null;
    }
    @Override
    public Uri insert(Uri uri, ContentValues cv){
        System.out.println("===insert iscalled==="+cv.get("name")+sh(uri)); return uri;
    }

    @Override
    public int delete(Uri uri, String where, String[] whereArgs){
        System.out.println("===delete is called==="+sh(uri)); return 1;
    }
    @Override
    public int update(Uri uri, ContentValues cv, String where,String[] whereArgs){
        System.out.println("===update is called==="+sh(uri));
        getContext().getContentResolver().notifyChange(uri, null);
        return 2;
    }

    private String sh(Uri uri){
        return "\r\n-----"+uri+"-----\r\n";
    }
}