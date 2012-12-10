package com.ec.morsms;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.telephony.SmsMessage;
import android.widget.Toast;
import com.ec.morsms.R;

//this extends the broadcaster to pass on received text messages
public class smsreceiver extends BroadcastReceiver {

	//where message is temporarily stored
	String str = "";
	
	@Override
	public void onReceive(Context context, Intent intent) {
		Bundle bundle = intent.getExtras();        
        SmsMessage[] msgs = null;
        
        
        
        
        if (bundle != null)	//receiver crashes here... since other non null attributes??
        {
            //retrieve the SMS message
            Object[] pdus = (Object[]) bundle.get("pdus");
            try{
            	msgs = new SmsMessage[pdus.length]; 
            }
            //in case something goes wrong, display toast
            catch(Exception e){
            	Toast.makeText(context, "morSMS: receiving error", Toast.LENGTH_SHORT).show();
            	return;
            }	
            
            for (int i=0; i<msgs.length; i++){
                msgs[i] = SmsMessage.createFromPdu((byte[])pdus[i]);
                str += msgs[i].getMessageBody().toString();        
            }
            
            //now pass this data to the service..
            Intent newIntent=new Intent(context,VibrationService.class);
            newIntent.putExtra("sms",str);
            context.startService(newIntent);	//starts another service

        }
	}
}



