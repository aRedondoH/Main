package com.box.pelugobuscador;

//import android.annotation.SuppressLint;
import android.app.Activity;

import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Toast;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;

//@SuppressLint("SetJavaScriptEnabled")
public class PeluGoMain extends Activity {

	public static Context context;
	static PeluGoMain ma;
	
	WebView webView;

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
		// display the logo during 5 secondes,
		new CountDownTimer(5000, 1000) {
			@Override
			public void onTick(long millisUntilFinished) {
			}

			@Override
		public void onFinish() {
				/* Google Admob advertising */
				AdView mAdView = (AdView)findViewById(R.id.adView);
				AdRequest adRequest = new AdRequest.Builder().build();
				mAdView.loadAd(adRequest);
			}
		}.start();
	}

	protected boolean allowRegisterForTouch(){
		return false;

	}
	
	//@SuppressLint("SetJavaScriptEnabled")
	public void openMap() {
		Uri uri = Uri.parse("http://www.easymapmaker.com/map/dc04a04f6274ac349447fbc5803d0765");
		Intent intent = new Intent(Intent.ACTION_VIEW, uri);
		startActivity(intent);

		// Close activity when it is changed
		this.finish();
	}

	public void openSignUp() {
		// Switching to Register screen
		Intent i = new Intent(getApplicationContext(), RegisterActivity.class);
		startActivity(i);
		// Close activity when it is changed
		this.finish();
	}
	
	@SuppressWarnings("unused")
	private class MyWebViewClient extends WebViewClient {
	    @Override
	    public boolean shouldOverrideUrlLoading(WebView view, String url) {
	        view.loadUrl(url);
	        return true;
	    }
	}
	
	//@SuppressLint("SetJavaScriptEnabled")
	public void openForum() {
		WebView webView;
		setContentView(R.layout.actividad_principal);
		webView = (WebView) findViewById(R.id.webview);
		webView.getSettings().setJavaScriptEnabled(true);
		webView.loadUrl("http://www.pelugo.es/index.php/foro");
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle presses on the action bar items
		switch (item.getItemId()) {
		case R.id.action_search:
			openMap();
			return true;
		case R.id.action_compose:
			openSignUp();
			return true;
		default:
			return super.onOptionsItemSelected(item);
		}
	}

}
