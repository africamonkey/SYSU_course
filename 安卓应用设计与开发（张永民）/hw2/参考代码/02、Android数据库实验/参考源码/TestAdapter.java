package com.example.isszym.grandwordremember;

import android.content.Context;
import android.graphics.Color;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CompoundButton;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.SimpleAdapter;
import android.widget.TextView;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by isszym on 2018/7/16.
 * https://blog.csdn.net/Sunjianhua360/article/details/51394488
 */

public class TestAdapter extends SimpleAdapter {
    private List<? extends Map<String, ?>> list;
    private Context mContext;
    LayoutInflater inflater;
    String[] from;
    int[] to;
    boolean showAnswer;
    private HashMap<Integer, String> userAnswerMap = null;
    static private HashMap<Integer,Integer> selectMap = new HashMap<Integer,Integer>();
    int wordColor;

    public TestAdapter1(Context context, List<? extends Map<String, ?>> list, int resource,
                        String[] from, int[] to, HashMap<Integer, String> userAnswerMap, int wordColor, boolean showAnswer) {
        super(context, list,  resource, from, to);
        this.list = list;
        this.from = from;
        this.to = to;
        this.mContext = context;
        inflater = LayoutInflater.from(mContext);
        this.showAnswer = showAnswer;
        this.userAnswerMap = userAnswerMap;
        this.wordColor=wordColor;
    }

    public HashMap<Integer, String> getUserAnswerMap(){
        return userAnswerMap;
    }

    @Override
    public int getCount() {
        // TODO Auto-generated method stub
        return list.size();
    }
    @Override
    public Object getItem(int position) {
        // TODO Auto-generated method stub
        return list.get(position);
    }

    @Override
    public long getItemId(int position) {
        // TODO Auto-generated method stub
        return position;
    }

    @Override
    public View getView(final int position, View convertView, ViewGroup parent) {
        // TODO Auto-generated method stub
        final ViewHolder holder;
        if(convertView == null){
            convertView = inflater.inflate(R.layout.list_item, null);
            holder = new ViewHolder();
            holder.rg = (RadioGroup) convertView.findViewById(R.id.radiogroup1);
            holder.word = (TextView) convertView.findViewById(to[0]);
            holder.pos = (TextView) convertView.findViewById(R.id.pos);
            for(int i=0;i<4;i++) {
                holder.rb[i] = (RadioButton) convertView.findViewById(to[i+1]);
                holder.rb[i].setChecked(true);
            }
            convertView.setTag(holder);
        }else{
            holder = (ViewHolder) convertView.getTag();
        }
        holder.word.setText(list.get(position).get(from[0]).toString());
        holder.word.setTextColor(wordColor);
        holder.pos.setText(""+position);

        for(int i=0;i<4;i++) {
           if(showAnswer && list.get(position).get("answer").toString().equals(from[i+1])){
                holder.rb[i].setBackgroundColor(0xFFF0F0F0);
            }
            else{
                holder.rb[i].setBackgroundColor(Color.WHITE);
            }
            holder.rb[i].setClickable(!showAnswer);
            holder.rb[i].setText(list.get(position).get(from[i+1]).toString());
            holder.rb[i].setOnCheckedChangeListener(new RadioButton.OnCheckedChangeListener() {
                    @Override
                    public void onCheckedChanged(CompoundButton btn, boolean checked) {
                        if(checked){
                            userAnswerMap.put(Integer.parseInt(holder.pos.getText().toString()),btn.getText().toString());
                        }
                        Log.e("测试",  holder.word.getText()+" pos: " +holder.pos.getText() + " checked: " + checked + "  sel:" + btn.getText());

                    }
                });
        }

        refreshSelection(holder,position);
        return convertView;
    }



    void refreshSelection(final ViewHolder h1, final int position){
        //---RadioGroup 的处理开始------------------------------
        //1.先取消对其监听
        h1.rg.setOnCheckedChangeListener(null);
        //2.先清空所有选项
        h1.rg.clearCheck();
        //3.根据选择情况显示选择答案
        int ind=0;
        if(selectMap.get(position)!=null){
            ind = selectMap.get(position);
        }
        switch (ind) {
            case 1:
                h1.rg.check(R.id.sel0);
                break;
            case 2:
                h1.rg.check(R.id.sel1);
                break;
            case 3:
                h1.rg.check(R.id.sel2);
                break;
            case 4:
                h1.rg.check(R.id.sel3);
                break;
            default:
                break;
        }

        //4.重新注册监听
        h1.rg.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                int p=0;
                switch (checkedId){
                    case R.id.sel0:
                        p=1;
                        break;
                    case R.id.sel1:
                        p=2;
                        break;
                    case R.id.sel2:
                        p=3;
                        break;
                    case R.id.sel3:
                        p=4;
                        break;
                }
                //把选择了的答案记录回到ListView的集合中，以便滑动时给对应的RadioGroup赋值
                selectMap.put(position,p);
            }
        });
        //--------RadioGroup 的处理结束--------------

    }
    public void reset(){
        selectMap.clear();
    }

    public class ViewHolder{
        RadioGroup rg;
        RadioButton[] rb=new RadioButton[4];
        TextView word;
        TextView pos;
    }

}