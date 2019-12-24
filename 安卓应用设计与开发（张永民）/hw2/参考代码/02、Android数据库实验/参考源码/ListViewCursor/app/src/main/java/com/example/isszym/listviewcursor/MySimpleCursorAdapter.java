package com.example.isszym.listviewcursor;

import android.content.Context;
import android.database.Cursor;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.SimpleCursorAdapter;
import android.widget.TextView;

import java.lang.reflect.Field;

/**
 * Created by isszym on 2018/4/8.
 */

class MySimpleCursorAdapter extends SimpleCursorAdapter {

    private LayoutInflater mInflater;
    private Context mContext;
    Cursor cur;
    int layout;

    public MySimpleCursorAdapter(Context context, int layout, Cursor c, String[] from, int[] to, int flags) {
        super(context, layout, c, from, to, flags);
        this.layout = layout;
        mContext = context;
        mInflater = LayoutInflater.from(context);
        cur = c;
        // TODO Auto-generated constructor stub
    }

    @Override
    public void bindView(View view, Context context, Cursor cursor) {
        //TextView notePhoto = (TextView) view.findViewById(R.id.photo);
        ImageView notePhoto = (ImageView) view.findViewById(R.id.photo);
        TextView noteNum = (TextView) view.findViewById(R.id.num);
        TextView noteName = (TextView) view.findViewById(R.id.name);

        Log.d("xxxx", "cur=" + cursor.getCount() + ",c_count=" + cursor.getColumnCount());
        //notePhoto.setImageResource(getResource(cur.getString(1)));
        notePhoto.setImageResource(getResourceByReflect(cur.getString(1)));
        noteNum.setText("" + cur.getLong(2));
        noteName.setText("" + cur.getString(3));

        //super.bindView(view, context, cursor);
    }

    int getResource(String imageName) {
        //Context ctx = getBaseContext();
        int resId = mContext.getResources().getIdentifier(imageName, "drawable", mContext.getPackageName());
        return resId;
    }

    public int getResourceByReflect(String imageName) {
        Class drawable = R.drawable.class;
        Field field = null;
        int r_id;
        try {
            field = drawable.getField(imageName);
            r_id = field.getInt(field.getName());
        } catch (Exception e) {
            r_id = R.drawable.cwt;
            Log.e("ERROR", "PICTURE NOT　FOUND！");
        }
        return r_id;
    }

    @Override
    public View newView(Context arg0, Cursor arg1, ViewGroup arg2) {
        return mInflater.inflate(layout, arg2, false);
    }
}

