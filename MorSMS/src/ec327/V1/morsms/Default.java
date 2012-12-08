package ec327.V1.morsms;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Handler;
import android.view.Menu;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import com.ec.morsms.R;

public class Default extends Activity{
	
	//for splash screen
	private Handler mHandler = new Handler();
	
    @Override
    public void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_default);
        
        
        //to ensure the splash screen happens only once.
        int runOnce = ((Global) this.getApplication()).getRun();
        if (runOnce == 0){
	        mHandler.postDelayed(new Runnable() {
	            public void run() {
	                fadeSplash();
	            }
	         }, 1000);
	        ((Global) this.getApplication()).setRun();
        }
        else removeSplash();
        
        
        //set the correct image for the button.
        setButtonState();
        //ensure this activity stays vertical
        setOrientation();
        
    }
    
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_default, menu);
        return true;
    }
    
    
    public void fadeSplash() {
    	
    	//do only the first time somehow... This si the splash screen, just fades out firs time.
        RelativeLayout introLayout = (RelativeLayout) findViewById(R.id.splashLayout);
        Animation fadeOutAnim = AnimationUtils.loadAnimation(Default.this, android.R.anim.fade_out);
        introLayout.startAnimation(fadeOutAnim);
        introLayout.setVisibility(View.GONE);
    }
    public void removeSplash() {
    	RelativeLayout introLayout = (RelativeLayout) findViewById(R.id.splashLayout);
        introLayout.setVisibility(View.GONE);
    	
    }
    
    
    //lock the orientation onto vertical.
    protected void setOrientation() {
        int current = getRequestedOrientation();
        // only switch the orientation if not in portrait
        if ( current != ActivityInfo.SCREEN_ORIENTATION_PORTRAIT ) {
            setRequestedOrientation( ActivityInfo.SCREEN_ORIENTATION_PORTRAIT );
        }
    }
    
    //Set the button/enable the broadcast everytime Home screen (default) is reached)
    public void setButtonState(){
    	
    	//relevant to first time, checking
    	PackageManager pm  = Default.this.getPackageManager();
        ComponentName componentName = new ComponentName(Default.this, smsreceiver.class);
        
    	ImageView img = (ImageView)findViewById(R.id.imageView1);
    	int x = ((Global) this.getApplication()).getEnableState();
    	if (x == 1){
    		//enable the broadcaster
    		img.setImageResource(R.drawable.enabled);
    		pm.setComponentEnabledSetting(componentName,PackageManager.COMPONENT_ENABLED_STATE_ENABLED,
                    PackageManager.DONT_KILL_APP);
    	}
    	else {
    		//disable the broadcaster
    		img.setImageResource(R.drawable.disabled);
    		pm.setComponentEnabledSetting(componentName,PackageManager.COMPONENT_ENABLED_STATE_DISABLED,
                    PackageManager.DONT_KILL_APP);
    	}
    	
    }
    	
    //what pressing the image button will do, toggle the state of morSMS message vibration
    public void buttonPress(View view) {
    	
    	//used for preparing to enable/disable the receiver class extension
    	PackageManager pm  = Default.this.getPackageManager();
        ComponentName componentName = new ComponentName(Default.this, smsreceiver.class);
    	
    	//used to setting the new image/setting the global variable state.
    	ImageView img = (ImageView)findViewById(R.id.imageView1);
    	int x = ((Global) this.getApplication()).getEnableState();
    	
    	
    	if (x == 1) {
    		//set the image to the red, button up
    		img.setImageResource(R.drawable.disabled);
    		//set the global, app-wide setting of enable to 0.
    		((Global) this.getApplication()).setEnableState(0);
    		
    		//disable the broadcaster, smsreceiver.
            pm.setComponentEnabledSetting(componentName,PackageManager.COMPONENT_ENABLED_STATE_DISABLED,
                            PackageManager.DONT_KILL_APP);

    	}
    	else {
    		//set the image to the green, button down
    		img.setImageResource(R.drawable.enabled);
    		
    		//enable the broadcaster, smsreceiver.
    		pm.setComponentEnabledSetting(componentName,PackageManager.COMPONENT_ENABLED_STATE_ENABLED,
                    PackageManager.DONT_KILL_APP);
    		
    		//set the global, app-wide setting of enable to 1.
    		((Global) this.getApplication()).setEnableState(1);
    	}
    	
    }
    
    
    
    
    //what pressing the charts button will do, open the charts activity
    public void toCharts(View view) {
        
    	Intent intent = new Intent(this, Charts.class);
        startActivity(intent);
    	
    }
    
    //what pressing the settings button will do, open settings activity
    public void toSettings(View view) {
        //change to settings.class
    	Intent intent = new Intent(this, Settings.class);
        startActivity(intent);
    }
    
    //what pressing the "Info" button will do, open info activity
    public void toInfo(View view) {
        //change to settings.class
    	Intent intent = new Intent(this, Info.class);
        startActivity(intent);
    }
    
  //what pressing the "Info" button will do, open info activity
    public void toGame(View view) {
        //change to settings.class
    	Intent intent = new Intent(this, Info.class);
        startActivity(intent);
    }
    
}