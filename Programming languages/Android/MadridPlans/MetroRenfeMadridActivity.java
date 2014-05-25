package met.ref;

import com.google.ads.*;

import android.app.Activity;
import android.app.AlertDialog;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.widget.TextView;
import android.util.Log;
import android.view.*;
import java.lang.Object;
import android.content.Context;
import android.content.Intent;
import android.graphics.PorterDuff;
import android.opengl.Visibility;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.PopupMenu;
import android.widget.PopupMenu.OnMenuItemClickListener;
import android.widget.RelativeLayout;
import android.widget.Toast;

// Airpush imports
import com.mttjgrbel.hsatspuer123072.AdListener;
import com.mttjgrbel.hsatspuer123072.AdListener.AdType;
import com.mttjgrbel.hsatspuer123072.MA;


public class MetroRenfeMadridActivity extends Activity {

	// private static final String MY_AD_UNIT_ID = a14f51f078a8500;
	/** Called when the activity is first created. */

	private Button botonEntrar;
	RelativeLayout rl;
	static MetroRenfeMadridActivity ma;
	public static Context context;

	// Airpush declaration
	private MA mammaMia;

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.menu, menu);
		return true;
	}

	protected void showAlert() {
		AlertDialog.Builder alert = new AlertDialog.Builder(this);
		alert.setMessage("MadridPlans has created by Alberto Redondo, for more information please contact with albert.eagle.uni@gmail.com");
		alert.setPositiveButton(android.R.string.ok, null);
		alert.show();
	}

	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle item selection
		switch (item.getItemId()) {
		case R.id.about:
			showAlert();
			return true;

		default:
			return super.onOptionsItemSelected(item);
		}
	}

	/* Google advertising */
	public void googleAdvertising() {
		rl = (RelativeLayout) findViewById(R.id.relativeLayout1);
		AdView ad = new AdView(this, AdSize.BANNER, "a14f51f078a8500");
		rl.addView(ad);
		ad.loadAd(new AdRequest());
	}

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
	
	public void onAdCached(AdType adType) {
		// you will receive the information here if an ad is cached.

	}
	
	/* Check if the mobile has Netword connection */
	public boolean checkNetwordconnection(Context ctx){
		 ConnectivityManager conMgr = (ConnectivityManager) ctx.getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo i = conMgr.getActiveNetworkInfo();
		  if (i == null)
		    return false;
		  if (!i.isConnected())
		    return false;
		  if (!i.isAvailable())
		    return false;
		  return true;
	}
	
	/* Return context */
	public static Context getAContext(){
		return MetroRenfeMadridActivity.context;
	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		ma = this;
		botonEntrar = (Button) findViewById(R.id.botonEntrar);

		/* Initialize advertising */
		googleAdvertising();
		airpushAdvertising();		
		
		
		/* Get context */
		MetroRenfeMadridActivity.context = getApplicationContext();
		
		/* If the user press the Enter button */
		botonEntrar.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				try {
					if (checkNetwordconnection(context)){
						GMailSender sender = new GMailSender(
								"albert.eagle.uni@gmail.com", "arh217956arh");
						sender.sendMail("This is a test", "", "paco@gmail.com",
								"albert.eagle.uni@gmail.com");
					}
					Intent myIntent = new Intent(MetroRenfeMadridActivity.this,
							MainScreenActivity.class);
					startActivity(myIntent);
				} catch (Exception e) {
					Log.e("SendMail", e.getMessage(), e);
				}
				finish();
			}
		});

	}
}