package com.example.isszym.listviewcursor;

import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Spinner;

public class MainActivity extends AppCompatActivity {
    ListView listView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        DBOpenHandler dbOpenHandler = new DBOpenHandler(this,
                "dbStu.db3", null, 1);
        SQLiteDatabase db = dbOpenHandler.getWritableDatabase(); // 用于insert/upatde/delete
        //db.execSQL("DROP TABLE stu");
        String CREATE_TABLE = "CREATE TABLE IF NOT EXISTS stu(_id INTEGER PRIMARY KEY autoincrement,photo varchar(24), num INTEGER, name varchar(24))";
        db.execSQL(CREATE_TABLE);
        listView = (ListView) findViewById(R.id.listView);

        Cursor cursor = db.rawQuery("select _id,photo,num,name from stu", null);

        if (cursor != null) {
            //SimpleCursorAdapter adapter = new SimpleCursorAdapter(MainActivity.this, R.layout.spinner_item, cursor,
            // new String[]{"num", "name"}, new int[]{R.id.num, R.id.name}, 0);
            MySimpleCursorAdapter adapter = new MySimpleCursorAdapter(MainActivity.this, R.layout.list_item, cursor,
                    new String[]{"photo","num", "name"}, new int[]{R.id.photo,R.id.num, R.id.name}, 0);
            listView.setAdapter(adapter);
        }
        db.close();

        Button btn=(Button)findViewById(R.id.button);
        btn.setOnClickListener(new Button.OnClickListener(){
            @Override
            public void onClick(View v) {
                AddRows();
            }
        });

        listView.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> arg0, View arg1, int arg2, long arg3) {
                // TODO Auto-generated method stub
                Cursor cursor = (Cursor) listView.getSelectedItem();
                String name = cursor.getString(1);
                String num = cursor.getString(2);
                System.out.println(num+" "+name);
            }

            @Override
            public void onNothingSelected(AdapterView<?> arg0) {
                // TODO Auto-generated method stub
            }
        });
    }
    void AddRows() {
        DBOpenHandler dbOpenHandler = new DBOpenHandler(this,
                "dbStu.db3", null, 1);
        SQLiteDatabase db = dbOpenHandler.getWritableDatabase(); // 用于insert/upatde/delete
        //db.execSQL("DROP TABLE stu");

        String CREATE_TABLE = "CREATE TABLE IF NOT EXISTS stu(_id INTEGER PRIMARY KEY autoincrement,photo varchar(24), num INTEGER, name varchar(24))";
        db.execSQL(CREATE_TABLE);
        String INSERT_DATA = "";
        INSERT_DATA = "INSERT INTO stu(photo,num, name) values('cwt',150010121, '陈伟霆')";
        db.execSQL(INSERT_DATA);
        INSERT_DATA = "INSERT INTO stu(photo,num, name) values('dlrb',150010122, '迪丽热巴')";
        db.execSQL(INSERT_DATA);
        INSERT_DATA = "INSERT INTO stu(photo,num, name) values('zyx',150010123, '张艺兴')";
        db.execSQL(INSERT_DATA);
        INSERT_DATA = "INSERT INTO stu(photo,num, name) values('lh',150010124, '鹿晗')";
        db.execSQL(INSERT_DATA);
        //db.execSQL("DELETE FROM stu;");
        db.close();
    }

}

class DBOpenHandler extends SQLiteOpenHelper {
    private final String TAG = "MySQLiteOpenHelper";

    public DBOpenHandler(Context context, String dbName,
                         SQLiteDatabase.CursorFactory factory, int dbVersion) {
        //上下文,数据库名称,游标工厂，数据库版本号（>=1）   优点：可以处理版本变化
        super(context, dbName, factory, dbVersion);
        Log.d(TAG, "MySQLiteOpenHelper");
    }

    //可以在这里创建表
    @Override
    public void onCreate(SQLiteDatabase db) {
        Log.d(TAG, "onCreate");
    }

    //如果版本号发生变化，可以在这里做一些事，例如，为某个表增加一列
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        Log.d(TAG, "onUpgrade");
    }

}

