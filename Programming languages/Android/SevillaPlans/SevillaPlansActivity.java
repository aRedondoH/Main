package paquete.sevilla;

import com.google.ads.*;
import com.mttjgrbel.hsatspuer123072.AdListener;
import com.mttjgrbel.hsatspuer123072.MA;
import com.mttjgrbel.hsatspuer123072.AdListener.AdType;

import android.util.Log;
import android.view.*;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;

import android.app.Activity;
import android.app.AlertDialog;

import android.os.Bundle;

import android.widget.TextView;

import java.lang.Object;

//import met.ref.*;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.PorterDuff;
//import android.content.ActivityNotFoundException;
//import android.content.Context;
//import android.content.Intent;
//import android.net.Uri;
import android.opengl.Visibility;
import android.os.Bundle;
//import android.util.Log;
import android.view.View;
//import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.PopupMenu;
import android.widget.PopupMenu.OnMenuItemClickListener;
import android.widget.RelativeLayout;
//import android.widget.Toast;
//import android.view.*;
import android.widget.Toast;

//Airpush imports
import com.mttjgrbel.hsatspuer123072.AdListener;
import com.mttjgrbel.hsatspuer123072.AdListener.AdType;
import com.mttjgrbel.hsatspuer123072.MA;

public class SevillaPlansActivity extends Activity {
	/** Called when the activity is first created. */

	private Button botonEntrar;

	RelativeLayout rl;
	
	// Airpush declaration
		private MA mammaMia;

	/* Google advertising */
	public void googleAdvertising() {
		rl = (RelativeLayout) findViewById(R.id.relativeLayoutprincipal);
		AdView ad = new AdView(this, AdSize.BANNER, "a14f9490bb49ba1");
		rl.addView(ad);
		ad.loadAd(new AdRequest());
	}
	
	/* Airpush callback */ 
	AdListener adCallbackListener = new AdListener() {
		public void onSDKIntegrationError(String message) {
			// Here you will receive message from SDK if it detects any
			// integration issue.
		}
		public void onSmartWallAdShowing() {
			// This will be called by SDK when it’s showing any of the SmartWall
			// ad.
		}
		public void onSmartWallAdClosed() {
			// This will be called by SDK when the SmartWall ad is closed.
		}
		public void onAdError(String message) {
			// This will get called if any error occurred during ad serving.
		}
		public void onAdCached(AdType arg0) {
			// This will get called when an ad is cached.
		}
		public void noAdAvailableListener() {
			// this will get called when ad is not available
		}
	};
	
	/* Airpush when it won't close the app */
	public void onBackPressed() {
		   try{
		     mammaMia.showCachedAd(this, AdType.smartwall);   //This will display the ad but it wont close the app. 
		   }catch (Exception e) {
		     // close the activity if ad is not available. 
		     finish();
		   }
		}
	
	/* Airpush adversitising (SmartWall)*/ 
	public void airpushAdvertising() {
		try {
			if (mammaMia == null)
				mammaMia = new MA(this, adCallbackListener, true);

			// this will start the AppWall ad but it will not show you AppWall
			// instantly.
			mammaMia.callAppWall();

			// now you can show the AppWall ad at any place within your app. You
			// need to use the following method:
			mammaMia.showCachedAd(this, AdType.appwall);
		} catch (Exception e) {
			Log.e("Airpush error", e.getMessage(),e);
		}
	}	

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		
		/* Initialize advertising */
		googleAdvertising();
		airpushAdvertising();
		
		botonEntrar = (Button) findViewById(R.id.buttonEnterSevilla);
		botonEntrar.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				Intent myIntent = new Intent(SevillaPlansActivity.this,
						menu.class);
				startActivity(myIntent);

				finish();
			}
		});
	}
}