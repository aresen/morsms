package com.ec.morsms;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.View;
import android.widget.SeekBar;
import android.widget.TextView;
import com.ec.morsms.R;

public class Settings extends Activity implements SeekBar.OnSeekBarChangeListener {

	
	SeekBar mSeekBar;
	SeekBar charMax;
    TextView mProgressText;
    TextView enable;
    TextView messageLength;
    String state;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);
        
        //getActionBar().setDisplayHomeAsUpEnabled(true);

        
        //get objects ready
        mSeekBar = (SeekBar)findViewById(R.id.unitSpeedBar);
        charMax = (SeekBar)findViewById(R.id.charMax);
        mSeekBar.setOnSeekBarChangeListener(this);
        charMax.setOnSeekBarChangeListener(this);
        mProgressText = (TextView)findViewById(R.id.unitBarText);
        enable = (TextView)findViewById(R.id.enableState);
        messageLength = (TextView)findViewById(R.id.messageLengthBar);
        
        
        //text above seekBar for speed
        int x = ((Global) this.getApplication()).getUnitSpeed();
        
        //initialize text contents for speed
        mProgressText.setText("Unit vibration length: " + x + " ms");
        mSeekBar.setProgress((x-100)/4);	//sets the seekbar to correct position
        
        //text for macChar seekbar
        int mc = ((Global) this.getApplication()).getMaxChar();
        messageLength.setText("Maximum character input: " + mc + " characters\n(zero is no limit)");
        charMax.setProgress(mc);
        
        //General message saying current status of morSMS message receiver
        int y = ((Global) this.getApplication()).getEnableState();
        if (y==1) state = "enabled.";
        else state = "disabled. Press the red button on the home page to enable!";
        enable.setText("Morse code message vibration is currently " + state);
    }

    //what happens when the slider changes
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromTouch) {
       
    	int x;
    	//Log.v("", "" + seekBar);

        switch (seekBar.getId()) {
        
        case R.id.unitSpeedBar:
        	((Global) this.getApplication()).setUnitSpeed(progress*4+100);
            x = ((Global) this.getApplication()).getUnitSpeed();
            mProgressText.setText("Unit vibration length: " + x + " ms");
            break;
            
        case R.id.charMax:
        	((Global) this.getApplication()).setMaxChar(progress);
        	x = ((Global) this.getApplication()).getMaxChar();
            messageLength.setText("Maximum character input: " + x + " characters\n(zero is no limit)");
            break;
            
        }
    }
    
    //"implementation" for the slider
    public void onStartTrackingTouch(SeekBar seekBar) {   
    }
    public void onStopTrackingTouch(SeekBar seekBar) {    
    }

    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_settings, menu);
        return true;
    }
    
    
    
    
    public void toDefaultPress(View view) {
        
    	Intent intent = new Intent(this, Default.class);
        startActivity(intent);
    }
    
    public void toChartsPress(View view) {
        
    	Intent intent = new Intent(this, Charts.class);
        startActivity(intent);
    }

}
