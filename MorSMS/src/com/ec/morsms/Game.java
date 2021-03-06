package com.ec.morsms;

import android.os.Bundle;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.view.Gravity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.widget.EditText;
import android.widget.Toast;

public class Game extends Activity {

	
	//locally store global variables, can't access otherwise in adapter view
	String word;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game);
        getActionBar().setDisplayHomeAsUpEnabled(true);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_game, menu);
        return true;
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
    
    
    //if you press show
    public void onGetPhrase(View view){
    	//just reveal the phrase
    	
    	//get what the last phrase was
    	word = ((Global) this.getApplication()).getLast();
    	
    	//display this phrase onscreen for a moment
    	Toast toast = Toast.makeText(getBaseContext(), "Last phrase: " + word, Toast.LENGTH_LONG); //TS
		toast.setGravity(Gravity.TOP|Gravity.CENTER, 0, 70); 	//display toast at top, down from bar
		toast.show();
    	
    	
    	//send it to the vibration service to also vibrate the phrase again.
    	Context context = getBaseContext();
    	Intent newIntent=new Intent(context,VibrationService.class);
        newIntent.putExtra("sms",word);
        context.startService(newIntent);
    }
    
    //pressing set phrase, take user input then vibrates/stores it
    public void onSetPhrase(View view){
    	
    	//get the current input.
    	EditText editText = (EditText) findViewById(R.id.new_phrase);
    	editText.setInputType(EditorInfo.TYPE_NULL);
    	word = editText.getText().toString();
    	
    	//send it to the vibration service.
    	Context context = getBaseContext();
    	Intent newIntent=new Intent(context,VibrationService.class);
        newIntent.putExtra("sms",word);
        context.startService(newIntent);
    	
    }
    
    //button pressed to generate new word
    public void onNewWord(View view){
    	

    	//declare the random array of words
    	int rand_phrase_size = 10;	//set to proper number of words there
    	String[] rand_array = {"Hello","Cat","Dog","Random","morSMS","Android","SOS", "Phone", "Hat",
    							"Shakespeare"};
    	
    	//generate random integer
    	int index = (int)(Math.random() * ((rand_phrase_size-1) + 1));
    	
    	//select random word
    	word = rand_array[index];

    	
    	//send it to the vibration service.
    	Context context = getBaseContext();
    	Intent newIntent=new Intent(context,VibrationService.class);
        newIntent.putExtra("sms",word);
        context.startService(newIntent);
    	
    	
    	
    }

}
