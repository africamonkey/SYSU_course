package com.example.isszym.dynamicview;

import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.LinearLayout;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        LinearLayout ll =(LinearLayout)findViewById(R.id.activity_main);

        for(int i=0;i<30;i++) {
            TextView myTextView = new TextView(MainActivity.this);
            myTextView.setText("第"+i+"行, Hello World!");
            myTextView.setTextSize(30);
            myTextView.setBackgroundColor(Color.argb(255,200,200,255));
            LinearLayout.LayoutParams textViewLP = new LinearLayout.LayoutParams(
                    LinearLayout.LayoutParams.WRAP_CONTENT,
                    LinearLayout.LayoutParams.WRAP_CONTENT);
            textViewLP.setMargins(0,20,0,0);
            ll.addView(myTextView, textViewLP);
        }
    }
}
