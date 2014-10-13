package com.box.pelugobuscador;



import android.app.ActionBar;
import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;

public class PeluGoMain extends ActionBarActivity{
	
	
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
	    // Inflate the menu items for use in the action bar
	    MenuInflater inflater = getMenuInflater();
	    inflater.inflate(R.menu.main_activity_actions, menu);
	    return super.onCreateOptionsMenu(menu);
	}
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.logo);
		
		//display the logo during 5 secondes,
	    new CountDownTimer(5000,1000){
	        @Override
	        public void onTick(long millisUntilFinished){} 

	        @Override
	        public void onFinish(){
	               //set the new Content of your activity
	               PeluGoMain.this.setContentView(R.layout.actividad_principal2);
	        }
	   }.start();
	}
	
	public void openMap(){
		Intent browserIntent = new Intent(Intent.ACTION_VIEW, Uri.parse("http://batchgeo.com/map/8083b5087fe5cd6b78f485e7b834e34e"));
		startActivity(browserIntent);
		
		
	}
	
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
	    // Handle presses on the action bar items
	    switch (item.getItemId()) {
	        case R.id.action_search:
	            openMap();
	            return true;
	        case R.id.action_compose:
	            //composeMessage();
	            return true;
	        default:
	            return super.onOptionsItemSelected(item);
	    }
	}

}
