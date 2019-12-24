package com.example.isszym.spinnercustom;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private String [] cities;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Spinner spinner=(Spinner) findViewById(R.id.spinner);
        cities=getResources().getStringArray(R.array.city);
        ArrayAdapter<String> arrayAdapter = new MyArrayAdapter(MainActivity.this,cities);
        //arrayAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);  //下拉风格，可以不写
        spinner.setAdapter(arrayAdapter);
        spinner.setOnItemSelectedListener(new ItemSelListener());
    }
    private class ItemSelListener implements AdapterView.OnItemSelectedListener {
        @Override
        public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
            Toast.makeText(MainActivity.this,"选中了"+cities[position],Toast.LENGTH_SHORT).show();
        }
        @Override
        public void onNothingSelected(AdapterView<?> parent) {}
    }
}
