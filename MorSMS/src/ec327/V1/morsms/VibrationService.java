package ec327.V1.morsms;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.IBinder;
import android.os.Vibrator;
import android.widget.Toast;

public class VibrationService extends Service {
	
	static {
		System.loadLibrary("morse");
	}
	
	public native String trans(String message_in, int unit_in);
	
	@Override
    public IBinder onBind(Intent arg0) {
          return null;
    }
    @Override
    public void onCreate() {
          super.onCreate();
          //int x = ((Global) this.getApplication()).getEnableState();
          //Toast.makeText(this,"Service started ..."+x, Toast.LENGTH_SHORT).show();
    }
    
    @Override
    public void onDestroy() {
          super.onDestroy();
          //Toast.makeText(this, "Service destroyed ...", Toast.LENGTH_LONG).show();
    }
    
    
    
    @Override
    public void onStart(Intent intent, int startId){
        
    	//get sms from broadcast intent
    	String sms=intent.getStringExtra("sms");
        
    	// get global variables maximum character and unit speed
        int unit = ((Global) this.getApplication()).getUnitSpeed();
        int maxChar = ((Global) this.getApplication()).getMaxChar();
        
        //for debugging, show message
        Toast.makeText(this,  sms + unit + ", max " + maxChar, Toast.LENGTH_LONG).show();
        
        //do the string conversion etc stuff
        //BACK END STUFF HERE
        //String backend_str = "100\n100\n300\n100\n100\n300\n100\n500\n100";
        
        String backend_str = trans(sms,unit);
        
        
        int newMax;
        if (backend_str.length() > maxChar)
        	newMax = maxChar;
        else newMax = backend_str.length();
        
        //convert input string to array of integers
        String[] backArray = backend_str.split("\\r?\\n");
        long[] backArrayLong = new long [newMax];
        for (int i=0; i< newMax; i++){
        	backArrayLong[i] = Long.valueOf(backArray[i]).longValue();
        }

        //truncate to proper number of characters if too long
       // for (int i=maxChar; i < backArrayLong.length; i++)
       // 	backArrayLong[i] = 0;	//can we pass in zero values to vibrator?
        
        
        //vibrate this pattern once.
        Vibrator vibe = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);
        vibe.vibrate(backArrayLong,-1);	//-1 is for no repeats
        
        
    }
}