package com.ec.morsms;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.IBinder;
import android.os.Vibrator;
import android.widget.Toast;
import com.ec.morsms.R;

public class VibrationService extends Service {
	
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
          Toast.makeText(this, "Service destroyed ...", Toast.LENGTH_LONG).show();
    }
    
    
    @Override
    public void onStart(Intent intent, int startId){
        String data=intent.getStringExtra("sms");
        
        int x = ((Global) this.getApplication()).getUnitSpeed();
        Toast.makeText(this,  data + ", from Broadcast, unitSpeed:" + x, Toast.LENGTH_LONG).show();
        
        /// AaAAaAaaaAAAWWWWYEEAAAAAAHAHAHAHAHH
        
        //do the string conversion etc stuff
        Vibrator vibe = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);
        String backend_str = "100\n100\n300\n100\n100\n300\n100\n500\n100";
        
        //convert input string to array of integers
        String[] backArray = backend_str.split("\\r?\\n");
        long[] backArrayLong = new long [backArray.length];
        for (int i=0; i< backArray.length; i++){
        	backArrayLong[i] = Long.valueOf(backArray[i]).longValue();
        }
        
        //vibrate this pattern once.
        vibe.vibrate(backArrayLong,-1);	//-1 is for no repeats
        
        
    }
}