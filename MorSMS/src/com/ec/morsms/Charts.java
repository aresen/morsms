package com.ec.morsms;

import android.os.Bundle;
import android.os.Vibrator;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.support.v4.app.NavUtils;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.Toast;
import android.widget.AdapterView.OnItemClickListener;
import com.ec.morsms.R;

public class Charts extends Activity {
	
	static {
		System.loadLibrary("morse");
	}
	
	public native String trans(String message_in, int unit_in, int delay_in);
	
	//locally store global varaibles, can't access otherwise in adapter view
	int unitSpeed;
		
		
	    @Override
	    public void onCreate(Bundle savedInstanceState) {
	        super.onCreate(savedInstanceState);
	        setContentView(R.layout.activity_charts);
	        getActionBar().setDisplayHomeAsUpEnabled(true);
	        
	        
	        GridView gridview = (GridView) findViewById(R.id.gridview);
	        gridview.setAdapter(new ImageAdapter(this));
	        
	        //setup the global variables, speed and maxchar
	        unitSpeed = ((Global) this.getApplication()).getUnitSpeed();
	        
            
	        //this listens for a tap of one of the button/icons in grid
	        gridview.setOnItemClickListener(new OnItemClickListener() {
	        	
	            public void onItemClick(AdapterView<?> parent, View v, int position, long id) {
	                
	                //setup the vibrator
	            	Vibrator vibe = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);
	                boolean check = vibe.hasVibrator ();	//check to see if there is a vibrator
	                if (!check)
	                	Toast.makeText(getBaseContext(), "No vibrator on this device", Toast.LENGTH_SHORT).show();
	                
	                
	                //based on clicked index, get which character; two ranges, letters and numbers.
	                char letter;
	                if (position <= 25)
	                	letter = (char)(65+position);
	                else if (position == 35) letter = '0';
	                else
	                	letter = (char)(position+23);


	                String backend_input = Character.toString(letter);
	                
	                /* Old: pass letter input to vibrationservice.java
	                Context context = getBaseContext();
	  	    	  	Intent newIntent=new Intent(context,VibrationService.class);
	  	    	  	newIntent.putExtra("sms",backend_input);
	  	    	  	context.startService(newIntent);
	                */
	                
	                String backend_str = trans(backend_input,unitSpeed,200);
	                
	                
	                
	                //newMax = backend_str.length();
	                //convert input string to array of integers
	                String[] backArray = backend_str.split("\\t?\\n");
	                //String[] lengthInput = backend_str.split("\t");
	                
	                long[] backArrayLong = new long [backArray.length]; 
	                
	                //for (int i=0; i< newMax; i++){
	                for (int i=0; i< backArray.length; i++){ //-TS
	                	backArrayLong[i] = Long.valueOf(backArray[i]).longValue();
	                }
	                
	                
	                //vibrate this pattern once.
	                //Vibrator vibe1 = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);
	                vibe.vibrate(backArrayLong,-1);	//-1 is for no repeats
	                
	                
	                
	                /*
	                //normally truncate string based on maxChar; no need here though, as only 1 letter!
	                
	                /////
	                //send in string to c++, get it back as array.. pass in unitSpeed and maxChar..
	                /////
	                
	                //back_end(String messg, int unitTime);
	                
	                //currently for testing purposes..
	                String backend_str = "100\n100\n300\n100\n100\n300\n0\n0\n0";
	                
	                //convert input string to array of integers
	                String[] backArray = backend_str.split("\\r?\\n");
	                
	                
	                long[] backArrayLong = new long [backArray.length];
	                
	                
	                for (int i=0; i< backArray.length; i++){
	                	backArrayLong[i] = Long.valueOf(backArray[i]).longValue();
	                }
	                
	                //vibrate this pattern once.
	                vibe.vibrate(backArrayLong,-1);	//-1 is for no repeats
	                */
	            }
	        });
	    }
	    
	    // most of this is jsut for setting up grid view.
	    public class ImageAdapter extends BaseAdapter {
	        private Context mContext;

	        public ImageAdapter(Context c) {
	            mContext = c;
	        }

	        public int getCount() {
	            return mThumbIds.length;
	        }

	        public Object getItem(int position) {
	            return null;
	        }

	        public long getItemId(int position) {
	            return 0;
	        }

	        // create a new ImageView for each item referenced by the Adapter
	        public View getView(int position, View convertView, ViewGroup parent) {
	            ImageView imageView;
	            if (convertView == null) {  // if it's not recycled, initialize some attributes
	                imageView = new ImageView(mContext);
	                imageView.setLayoutParams(new GridView.LayoutParams(75, 75));
	                imageView.setScaleType(ImageView.ScaleType.CENTER_CROP);
	                imageView.setPadding(4, 4, 4, 4);
	            } else {
	                imageView = (ImageView) convertView;
	            }

	            imageView.setImageResource(mThumbIds[position]);
	            return imageView;
	        }

	        // references to our images, they will appear in this order on screen.
	        private Integer[] mThumbIds = {
	                R.drawable.alph01,	R.drawable.alph02,
	                R.drawable.alph03,	R.drawable.alph04,
	                R.drawable.alph05,	R.drawable.alph06,
	                R.drawable.alph07,	R.drawable.alph08,
	                R.drawable.alph09,	R.drawable.alph10,
	                R.drawable.alph11,	R.drawable.alph12,
	                R.drawable.alph13,	R.drawable.alph14,
	                R.drawable.alph15,	R.drawable.alph16,
	                R.drawable.alph17,	R.drawable.alph18,
	                R.drawable.alph19,	R.drawable.alph20,
	                R.drawable.alph21,	R.drawable.alph22,
	                R.drawable.alph23,	R.drawable.alph24,
	                R.drawable.alph25,	R.drawable.alph26,
	                R.drawable.alph27,	R.drawable.alph28,
	                R.drawable.alph29,	R.drawable.alph30,
	                R.drawable.alph31,	R.drawable.alph32,
	                R.drawable.alph33,	R.drawable.alph34,
	                R.drawable.alph35,	R.drawable.alph36
	        };
	    }
	    
	    // sets home activity
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
	        getMenuInflater().inflate(R.menu.activity_main, menu);
	        return true;
	    }
	    

	    
	    
	}
