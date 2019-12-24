package com.example.isszym.alertdialog;

import android.content.Context;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TableLayout;
import android.widget.TextView;
import android.app.AlertDialog;
import android.widget.Toast;


public class MainActivity extends AppCompatActivity {
    TextView show;
    String[] items = new String[]{
            "数据科学与计算机学院",
            "数学学院",
            "物理学院",
            "化学学院",
            "生命科学学院"};
    private Context mContext;
    private boolean[] checkItems;

    private AlertDialog alertDialog = null;
    private AlertDialog.Builder dialogBuilder = null;
    private int pos = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        show = (TextView) findViewById(R.id.show);
        mContext = this;
    }



    public void simple(View source) {
        dialogBuilder = new AlertDialog.Builder(mContext);
        alertDialog = dialogBuilder.setIcon(R.mipmap.sysu)
                .setTitle("简单对话框：")
                .setMessage("这是一个普通AlertDialog,\n可以加入三个按钮：取消，中立和确定")
                .setNegativeButton("取消", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Toast.makeText(mContext, "你点击了取消按钮", Toast.LENGTH_SHORT).show();
                    }
                })
                .setPositiveButton("确定", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Toast.makeText(mContext, "你点击了确定按钮", Toast.LENGTH_SHORT).show();
                    }
                })
                .setNeutralButton("中立", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Toast.makeText(mContext, "你点击了中立按钮", Toast.LENGTH_SHORT).show();
                    }
                }).create();             // 创建AlertDialog对象
        alertDialog.show();             // 显示对话框
    }

    public void simpleList(View source) {
        dialogBuilder = new AlertDialog.Builder(mContext);
        alertDialog = dialogBuilder
                // 设置图标
                .setIcon(R.mipmap.sysu)
                // 设置对话框标题
                .setTitle("简单列表对话框")
                // 设置简单的列表项内容
                .setItems(items, new OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Toast.makeText(mContext, "选中了\"" + items[which] + "\"", Toast.LENGTH_SHORT).show();
                    }
                })
                .setNegativeButton("取消", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Toast.makeText(mContext, "点击了取消按钮", Toast.LENGTH_SHORT).show();
                    }
                })
                .setPositiveButton("确定", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Toast.makeText(mContext, "点击了确定按钮", Toast.LENGTH_SHORT).show();
                    }
                })
                .setNeutralButton("中立", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Toast.makeText(mContext, "点击了中立按钮", Toast.LENGTH_SHORT).show();
                    }
                }).create();             // 创建AlertDialog对象
        alertDialog.show();
    }

    public void singleChoice(View source) {
        dialogBuilder = new AlertDialog.Builder(mContext);
        alertDialog = dialogBuilder
                // 设置图标
                .setIcon(R.mipmap.sysu)
                // 设置对话框标题
                .setTitle("单项选择对话框")
                // 设置单选列表项，默认选中第二项（索引为1）
                .setSingleChoiceItems(items, 1, new OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Toast.makeText(mContext, "选中了\"" + items[which] + "\"", Toast.LENGTH_SHORT).show();
                    }
                })
                .setNegativeButton("取消", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Toast.makeText(mContext, "点击了取消按钮", Toast.LENGTH_SHORT).show();
                    }
                })
                .setPositiveButton("确定", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Toast.makeText(mContext, "点击了确定按钮", Toast.LENGTH_SHORT).show();
                    }
                })
                .setNeutralButton("中立", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Toast.makeText(mContext, "点击了中立按钮", Toast.LENGTH_SHORT).show();
                    }
                }).create();             // 创建AlertDialog对象
        alertDialog.show();
    }

    public void multiChoice(View source) {
        dialogBuilder = new AlertDialog.Builder(mContext);
        alertDialog = dialogBuilder
                // 设置图标
                .setIcon(R.mipmap.sysu)
                // 设置对话框标题
                .setTitle("多项选择对话框")
                // 设置单选列表项，默认选中第二项和第四项（索引为1和3）
                .setMultiChoiceItems(items, new boolean[]{false, true, false, true, false}, null)
                .setNegativeButton("取消", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Toast.makeText(mContext, "点击了取消按钮", Toast.LENGTH_SHORT).show();
                    }
                })
                .setPositiveButton("确定", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        ListView list = alertDialog.getListView();
                        Toast.makeText(mContext, "点击了确定按钮,选中了"
                                + list.getCheckedItemCount() + "个项目", Toast.LENGTH_SHORT).show();

                    }
                })
                .setNeutralButton("中立", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Toast.makeText(mContext, "点击了中立按钮", Toast.LENGTH_SHORT).show();
                    }
                }).create();             // 创建AlertDialog对象
        alertDialog.show();
    }

    public void customList(View source) {
        dialogBuilder = new AlertDialog.Builder(mContext);
        alertDialog = dialogBuilder
                // 设置图标
                .setIcon(R.mipmap.sysu)
                // 设置对话框标题
                .setTitle("自定义列表项对话框")
                .setAdapter(
                        new ArrayAdapter<String>(mContext,
                                R.layout.array_item, items),
                        new OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                pos = which;
                                ListView list = alertDialog.getListView();
                                Toast.makeText(mContext, "点击了第" + which + "个项目: " + list.getItemAtPosition(pos), Toast.LENGTH_SHORT).show();
                            }
                        }
                )
                .create();             // 创建AlertDialog对象
        alertDialog.show();
    }

    public void customView(View source) {
        TableLayout studentForm = (TableLayout) getLayoutInflater()
                .inflate(R.layout.student, null);
        dialogBuilder = new AlertDialog.Builder(mContext);
        alertDialog = dialogBuilder
                // 设置图标
                .setIcon(R.mipmap.sysu)
                // 设置对话框标题
                .setTitle("自定义View对话框")
                // 设置对话框显示的View对象
                .setView(studentForm)
                .setNegativeButton("取消", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Toast.makeText(mContext, "点击了取消按钮", Toast.LENGTH_SHORT).show();
                    }
                })
                .setPositiveButton("确定", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        EditText stuNum=(EditText)alertDialog.findViewById(R.id.stu_num);
                        Toast.makeText(mContext, "点击了确定按钮,学号为\""
                                + stuNum.getText() + "\"", Toast.LENGTH_SHORT).show();
                    }
                })
                .setNeutralButton("中立", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Toast.makeText(mContext, "点击了中立按钮", Toast.LENGTH_SHORT).show();
                    }
                })
                .create();             // 创建AlertDialog对象
        alertDialog.show();
    }
}
