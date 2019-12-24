package com.example.isszym.newpreferenceactivity;

import android.content.SharedPreferences;
import android.content.SharedPreferences.OnSharedPreferenceChangeListener;
import android.os.Bundle;
import android.preference.CheckBoxPreference;
import android.preference.EditTextPreference;
import android.preference.ListPreference;
import android.preference.PreferenceFragment;
import android.util.Log;

public class SettingFragment extends PreferenceFragment implements OnSharedPreferenceChangeListener {
	
    private EditTextPreference mEtPreference;
    private ListPreference mListPreference;
    private CheckBoxPreference mCheckPreference;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        addPreferencesFromResource(R.xml.preferences);
        initPreferences();
        Bundle bundle=this.getArguments();
        String content = bundle.getString("data");
        Log.e("测试setting",content);
       // txt_content.setText(content);
    }
    
    private void initPreferences() {
    	mEtPreference = (EditTextPreference)findPreference("edittext_key");
    	mListPreference = (ListPreference)findPreference("list_key");
    	mCheckPreference = (CheckBoxPreference)findPreference("checkbox_key");
    }
    
    @Override
    public void onResume() {
        super.onResume();

        // Setup the initial values
        SharedPreferences sharedPreferences = getPreferenceScreen().getSharedPreferences();
        mListPreference.setSummary(sharedPreferences.getString("list_key", ""));
        mEtPreference.setSummary(sharedPreferences.getString("edittext_key", "linc"));
        
        // Set up a listener whenever a key changes
        sharedPreferences.registerOnSharedPreferenceChangeListener(this);
    }

    @Override
    public void onPause() {
        super.onPause();
        // Unregister the listener whenever a key changes
        getPreferenceScreen().getSharedPreferences().unregisterOnSharedPreferenceChangeListener(this);
    }    
    
	@Override
	public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String key) {
        if (key.equals("edittext_key")) {
        	mEtPreference.setSummary(
                    sharedPreferences.getString(key, "20"));
        } else if(key.equals("list_key")) {
        	mListPreference.setSummary(sharedPreferences.getString(key, ""));
        }
	}
}
