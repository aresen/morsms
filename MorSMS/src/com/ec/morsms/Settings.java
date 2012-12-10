package com.ec.morsms;

import android.os.Bundle;
import android.app.Activity;
import android.support.v4.app.NavUtils;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.SeekBar;
import android.widget.TextView;
import com.ec.morsms.R;

public class Settings extends Activity implements SeekBar.OnSeekBarChangeListener {

	
	SeekBar mSeekBar;
    TextView mProgressText;
    TextView enable;
    String state;
    int check;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);
        getActionBar().setDisplayHomeAsUpEnabled(true);

        
        //get objects ready
        mSeekBar = (SeekBar)findViewById(R.id.unitSpeedBar);
        mSeekBar.setOnSeekBarChangeListener(this);
        mProgressText = (TextView)findViewById(R.id.unitBarText);
        enable = (TextView)findViewById(R.id.enableState);
        
        
        //text above seekBar for speed
        int x = ((Global) this.getApplication()).getUnitSpeed();
        
        //initialize text contents for speed
        mProgressText.setText("Unit vibration length: " + x + " ms");
        mSeekBar.setProgress((x-100)/4);	//sets the seekbar to correct position
        
        //General message saying current status of morSMS message receiver
        int y = ((Global) this.getApplication()).getEnableState();
        if (y==1) state = "enabled.";
        else state = "disabled. Press the red button on the home page to enable!";
        enable.setText("Morse code message vibration is currently " + state);
        
        //set check box based on global setting
        CheckBox checkBox = (CheckBox) findViewById(R.id.checkBox1);
        check = ((Global) this.getApplication()).getShake();
        if (check==1) checkBox.setChecked(true);
        else checkBox.setChecked(false);
        
        /*
        checkBox.setOnCheckedChangeListener(new OnCheckedChangeListener(){
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked){
                if (isChecked){
                	((Global) this.getApplication()).setShake(1);
                }else{
                	((Global) this.getApplication()).setShake(0);
                }  
            }
        });
        */
        
    }

    //what happens when the slider changes
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromTouch) {
       
    	int x;
    	//switch redundant now that there's only one bar...
        switch (seekBar.getId()) {
        case R.id.unitSpeedBar:
        	((Global) this.getApplication()).setUnitSpeed(progress*4+100);
            x = ((Global) this.getApplication()).getUnitSpeed();
            mProgressText.setText("Unit vibration length: " + x + " ms");
            break;
            
        }
    }
    
    
    public void tickBox(View view){
    	
    	CheckBox checkBox = (CheckBox) findViewById(R.id.checkBox1);
        check = ((Global) this.getApplication()).getShake();
        if (check==1) {
        	checkBox.setChecked(false);
        	((Global) this.getApplication()).setShake(0);
        }
        else {
        	checkBox.setChecked(true);
        	((Global) this.getApplication()).setShake(1);
        }
    	
    }
    
    //"implementation" for the slider
    public void onStartTrackingTouch(SeekBar seekBar) {   
    }
    public void onStopTrackingTouch(SeekBar seekBar) {    
    }

    
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                NavUtils.navigateUpFromSameTask(this);
                return true;
        }
        return super.onOptionsItemSelected(item);
    }
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_settings, menu);
        return true;
    }
    

}
