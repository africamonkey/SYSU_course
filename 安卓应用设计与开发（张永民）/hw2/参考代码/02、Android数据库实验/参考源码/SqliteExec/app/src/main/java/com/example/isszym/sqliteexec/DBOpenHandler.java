package com.example.isszym.sqliteexec;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

/**
 * Created by isszym on 2018/6/26.
 */

class DBOpenHandler extends SQLiteOpenHelper {
    int version;
    public DBOpenHandler(Context context, String name,
                         SQLiteDatabase.CursorFactory factory, int version) {
        super(context, name, factory, version);
        this.version = version;
    }

    @Override
    public void onCreate(SQLiteDatabase db) {// 当数据库创建时就用SQL命令创建一个表
        // 创建一个stu（学生）表：_id--主键（自动增长)，name(姓名),num（学号）和age（年龄）;
         db.execSQL("CREATE TABLE stu(_id integer primary key autoincrement, name varchar(24),num varchar(24),age int)");
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        // TODO Auto-generated method stub
        if (oldVersion < 2){
            try {
                db.execSQL("ALTER TABLE stu ADD COLUMN age int");
            }catch(Exception ex){

            }
        }

    }
}
