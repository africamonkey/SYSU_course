package com.example.isszym.newpreferenceactivity;

import android.os.Bundle;
import android.preference.PreferenceManager;
import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

	private Button btnSetting,btnShow;
	private TextView tvCheckout,tvList,tvEditText;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		initView();
	}

	private void initView() {
		btnSetting = (Button)findViewById(R.id.btn_setting);
		btnShow = (Button)findViewById(R.id.btn_show);
		btnSetting.setOnClickListener(buttonListener);
		btnShow.setOnClickListener(buttonListener);
		
		tvCheckout = (TextView)findViewById(R.id.tv_checkout);
		tvList = (TextView)findViewById(R.id.tv_list);
		tvEditText = (TextView)findViewById(R.id.tv_edittext);
	}
	
	private OnClickListener buttonListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			switch(v.getId()) {
			case R.id.btn_setting:
				startActivity(new Intent(MainActivity.this,PreferenceActivity.class));
				break;
			case R.id.btn_show:
				showSettingInfo();
				break;
			}
			
		}
	};
	
	private void showSettingInfo() {
		SharedPreferences settings = PreferenceManager.getDefaultSharedPreferences(this);
		tvCheckout.setText(settings.getBoolean("checkbox_key", false)+"");
		tvEditText.setText(settings.getString("edittext_key", ""));
		tvList.setText(settings.getString("list_key", ""));
	}
}
