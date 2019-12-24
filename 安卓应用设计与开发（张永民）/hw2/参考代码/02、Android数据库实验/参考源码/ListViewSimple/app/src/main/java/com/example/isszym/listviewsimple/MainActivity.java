package com.example.isszym.listviewsimple;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class MainActivity extends AppCompatActivity {
    private ListView listView;
    ArrayList<Map<String, Object>> list;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        listView = (ListView) findViewById(R.id.listView);
        int[] images = { R.drawable.cwt, R.drawable.dlrb,
                R.drawable.lh, R.drawable.wjk, R.drawable.ym,
                R.drawable.zly, R.drawable.zyx};
        String[] names = { "陈伟霆", "迪丽热巴", "鹿晗",
                "王俊凯", "杨幂", "赵丽颖", "张艺兴" };
        int[] ages = { 18, 21, 22, 32, 31, 18, 20, 25 };
        list= new ArrayList<Map<String, Object>>();
        for (int i = 0; i < names.length; i++) {
            Map<String, Object> map = new HashMap<String, Object>();
            map.put("icon", images[i]);
            map.put("name", names[i]);
            map.put("age", ages[i]);
            list.add(map);
        }
        /** 参数：context(上下文对象), datasource(数据源), itemlayout(每个Item的布局页面),
         *         from String[] 数据源中key的数组, to int[] 布局页面中id的数组  **/
        SimpleAdapter adapter = new SimpleAdapter(this, list,
                R.layout.list_item, new String[] { "icon", "name", "age" },
                new int[] { R.id.icon, R.id.name, R.id.age });

        listView.setAdapter(adapter);
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Toast.makeText(MainActivity.this,"Short Click: "+list.get(position).get("name").toString()+" "+id,Toast.LENGTH_SHORT).show();
             }
        });
        listView.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            @Override
            public boolean onItemLongClick(AdapterView<?> parent, View view, int position, long id) {
                Toast.makeText(MainActivity.this,"Long Click: "+list.get(position).get("name").toString(),Toast.LENGTH_SHORT).show();
                return true;  //true: 只执行长按事件(ShortClick事件失效)
            }
        });
    }
}
