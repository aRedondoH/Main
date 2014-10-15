package com.box.pelugobuscador;

import android.annotation.SuppressLint;
import android.app.Activity;



import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.widget.Toast;




public class PeluGoMain extends Activity {
	


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

			@SuppressLint("SetJavaScriptEnabled")
			@Override
			public void onFinish() {
			
				WebView webView;
				setContentView(R.layout.actividad_principal);
				webView = (WebView)findViewById(R.id.webview);
				webView.getSettings().setJavaScriptEnabled(true);
				webView.loadUrl("http://batchgeo.com/map/8083b5087fe5cd6b78f485e7b834e34e");
		        
		        
			}
		}.start();
	}
	
	@SuppressLint("SetJavaScriptEnabled")
	public void openMap() {
		WebView webView;
		setContentView(R.layout.actividad_principal);
		webView = (WebView)findViewById(R.id.webview);
		webView.getSettings().setJavaScriptEnabled(true);
		webView.loadUrl("http://batchgeo.com/map/8083b5087fe5cd6b78f485e7b834e34e");
		
		 

	}

	public void openSignUp() {
		//PeluGoMain.this.setContentView(R.layout.actividad_principal);
		WebView myWebView = (WebView) findViewById(R.id.webview);
		myWebView.loadUrl("http://www.pelugo.es/index.php/8-administration/4-registrate-gratis");

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
