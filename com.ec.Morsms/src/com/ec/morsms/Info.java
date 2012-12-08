package com.ec.morsms;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.support.v4.app.NavUtils;
import com.ec.morsms.R;

public class Info extends Activity {

	
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_info);
        //getActionBar().setDisplayHomeAsUpEnabled(true);
        
        //Typeface.createFromAsset(getAssets(), "fonts/AmericanTypewritter.ttc");

        
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_info, menu);
        return true;
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
    
    public void toDefaultPress(View view) {
        
    	Intent intent = new Intent(this, Default.class);
        startActivity(intent);
    }
    
    public void toChartsPress(View view) {
        
    	Intent intent = new Intent(this, Charts.class);
        startActivity(intent);
    }

}
