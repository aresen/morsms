package com.ec.morsms;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.CheckBox;
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
        
    }

    //what happens when the slider changes
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromTouch) {
       
    	int x;
    	//switch redundant now that there's only one bar...
        
        ((Global) this.getApplication()).setUnitSpeed(progress*4+100);
        x = ((Global) this.getApplication()).getUnitSpeed();
        mProgressText.setText("Unit vibration length: " + x + " ms");
            
    }
    
    //tickbox that enables/disables shake to replay last phrase
    public void tickBox(View view){
    	
    	CheckBox checkBox = (CheckBox) findViewById(R.id.checkBox1);
    	//get the global variable setting, if enabled or not
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
                // This is called when the Home (Up) button is pressed
                // in the Action Bar.
                Intent parentActivityIntent = new Intent(this, Default.class);
                parentActivityIntent.addFlags(
                        Intent.FLAG_ACTIVITY_CLEAR_TOP |
                        Intent.FLAG_ACTIVITY_NEW_TASK);
                startActivity(parentActivityIntent);
                finish();
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
