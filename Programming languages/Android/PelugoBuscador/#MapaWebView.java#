package com.box.pelugobuscador;
import java.util.Timer;
import java.util.TimerTask;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnTouchListener;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;

import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;

public class MapaWebView extends Activity{

	public WebView myWebView;
	public static boolean flag = false;
	final String baseUrl = "http://www.easymapmaker.com/map/dc04a04f6274ac349447fbc5803d0765";

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.actividad_principal);

		/* Google Admob advertising */
		AdView mAdView = (AdView)findViewById(R.id.adView);
		AdRequest adRequest = new AdRequest.Builder().build();
		mAdView.loadAd(adRequest);

		myWebView = (WebView) findViewById(R.id.webview);

	            myWebView.post(new Runnable(){
	        	@Override
	            public void run() {

					myWebView.getSettings().setJavaScriptEnabled(true);
					myWebView.getSettings().setBuiltInZoomControls(true);
					myWebView.getSettings().setSupportZoom(true);
					myWebView.getSettings().setSupportMultipleWindows(true);
					myWebView.getSettings().setLoadWithOverviewMode(true);
					myWebView.getSettings().setJavaScriptCanOpenWindowsAutomatically(true);
					myWebView.getSettings().setDomStorageEnabled(true);
					myWebView.getSettings().setDatabaseEnabled(true);
					WebSettings settings = myWebView.getSettings();
					settings.setJavaScriptEnabled(true);
					String newUa = "Foo/";
					String newUA= "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9.0.4) Gecko/20100101 Firefox/4.0";
					myWebView.getSettings().setUserAgentString(newUA);
					myWebView.loadUrl(baseUrl);
	            }
	            });
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu items for use in the action bar
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.main_activity_actions, menu);
		return super.onCreateOptionsMenu(menu);
	}

	public void openSignUp() {
		// Switching to Register screen
		Intent i = new Intent(getApplicationContext(), RegisterActivity.class);
		startActivity(i);
	}

	public void openMap() {
		Intent intent = new Intent(getApplicationContext(), MapaWebView.class);
		startActivity(intent);
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
