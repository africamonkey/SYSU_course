package com.example.isszym.myapplication;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class SecondActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);
        Intent intent = getIntent();
        String parm= intent.getStringExtra("parm");
        TextView tv = (TextView) findViewById(R.id.textView);
        tv.setText(parm);
    }

    public void clickHandler(View source) {
        finish();
    }
}
