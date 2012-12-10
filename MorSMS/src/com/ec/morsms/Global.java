package com.ec.morsms;
import android.app.Application;

public class Global extends Application {
	
	
	// variables
    private int unitSpeed;		//the value of of vibration speed
    private int buttonState;	//whether message vibration is enabled or not
    private int runOnce;		//used to make the logo fadeout animation happen only once
    private String last;		//this stores the last message or phrase
    private int shake;			//setting for if shaking will re-vibrate last message
    
    //on create application, initialize things
    @Override
    public void onCreate() {
        unitSpeed = 200;
        buttonState = 0;
        last = "";	
        shake = 0;	
    }
    
    
    
    
  //global application variables gets/sets
    public void setShake(int n){
    	shake = n;
    }
    
    public int getShake(){
    	return shake;
    }
    
    public void setLast(String newStr){
    	last = newStr;
    }
    
    public String getLast(){
    	return last;
    }
    
    public void setRun(){
    	runOnce = 1;
    }
    
    public int getRun(){
    	return runOnce;
    }
    
    public int getEnableState() {
        return this.buttonState;
    }
    
    public void setEnableState(int set) {
        this.buttonState = set;
    }
	
    //vibration unit speed
    public int getUnitSpeed(){
    	return unitSpeed;
    }
	
    public void setUnitSpeed(int set) {
    	this.unitSpeed = set;
    }

}
