package com.ec.morsms;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.view.Menu;
import android.view.View;
import com.ec.morsms.R;

public class MainActivity extends Activity {
	private Handler mHandler = new Handler();
	
	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        
        //have it "pause" (non stalling) for 5 seconds on splash screen,
        //then run run(), which just starts the next "default" activity.
        mHandler.postDelayed(new Runnable() {
           public void run() {
               toDefault();
           }
        }, 1000);
    }
	
	
	
	/*
	protected void onResume(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        //have it "pause" (non stalling) for 5 seconds on splash screen,
        //then run run(), which just starts the next "default" activity.
        mHandler.postDelayed(new Runnable() {
           public void run() {
               toDefault();
           }
        }, 1000);
    }*/
	
	
	//start next activity
    public void toDefaultPress(View view) {
        
    	Intent intent = new Intent(this, Default.class);
        startActivity(intent);
    }
    
public void toDefault() {
        
    	Intent intent = new Intent(this, Default.class);
        startActivity(intent);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }
}
