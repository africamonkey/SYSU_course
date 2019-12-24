package com.example.isszym.myapplication;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.content.Intent;
import android.widget.TextView;

public class ThirdActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_third);
        Intent intent = getIntent();
        String parm= intent.getStringExtra("parm");
        TextView tv = (TextView) findViewById(R.id.textView);
        tv.setText(parm);
        Button bn3 = (Button) findViewById(R.id.btn1);
        bn3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View source) {
                Intent intent = getIntent();
                EditText et = (EditText) findViewById(R.id.editText);
                intent.putExtra("res",et.getText().toString());
                setResult(2,intent);  //response Code
                finish();
            }
        });
    }
}
