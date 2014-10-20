package com.box.pelugobuscador;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.lang.Character.UnicodeBlock;
import java.net.URI;
import java.util.ArrayList;
import java.util.List;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.HttpResponseException;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.client.utils.URLEncodedUtils;
import org.apache.http.impl.client.BasicResponseHandler;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.json.JSONException;
import org.json.JSONObject;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.StrictMode;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class RegisterActivity extends Activity {

	public Button signUpHairdresser;
	public EditText nameHS;
	public EditText addressHS;
	public EditText cityHS;
	public EditText provinceHS;
	public EditText timetableHS;
	public EditText emailHS;
	public EditText phoneHS;

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// Set View to register.xml
		setContentView(R.layout.register);
		nameHS = (EditText) findViewById(R.id.hairdresserName);
		addressHS = (EditText) findViewById(R.id.hairdresserAdress);
		cityHS = (EditText) findViewById(R.id.hairdresserCity);
		provinceHS = (EditText) findViewById(R.id.hairdresserProvince);
		timetableHS = (EditText) findViewById(R.id.hairdresserTimetable);
		emailHS = (EditText) findViewById(R.id.hairdresserEmail);
		phoneHS = (EditText) findViewById(R.id.hairdresserPhoneNumber);

		signUpHairdresser = (Button) findViewById(R.id.btnRegister);
		signUpHairdresser.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				new ConnectAsync().execute(nameHS.getText().toString(),
						addressHS.getText().toString(), cityHS.getText()
								.toString(), provinceHS.getText().toString(),
						timetableHS.getText().toString(), emailHS.getText()
								.toString(), phoneHS.getText().toString());
			}
		});

	}

	public class ConnectAsync extends AsyncTask<String, Void, Boolean> {

		// Server information
		String respuestaServidor;
		String responseString;
		InputStream is = null;
		String result = "paquito el chocolatero";
		String json = "";

		public Boolean doInBackground(String... params) {

			String url = "http://pelugo.es/php_pelugo/android/signUP.php";
			// HttpClient client = new DefaultHttpClient();
			// HttpPost post = new HttpPost(url);

			try {

				/* Get parameters and insert into the arrayList */
				List<NameValuePair> postValues = new ArrayList<NameValuePair>();
				postValues.add(new BasicNameValuePair("nameHairdresser",
						params[0]));

				postValues.add(new BasicNameValuePair("addressHairdresser",
						params[1]));
				postValues.add(new BasicNameValuePair("cityHairdresser",
						params[2]));
				postValues.add(new BasicNameValuePair("provinceHairdresser",
						params[3]));
				postValues.add(new BasicNameValuePair("timetableHairdresser",
						params[4]));
				postValues.add(new BasicNameValuePair("emailHairdresser",
						params[5]));
				postValues.add(new BasicNameValuePair("phoneHairdresser",
						params[6]));

				// request method is GET
				DefaultHttpClient httpClient = new DefaultHttpClient();
				String paramString = URLEncodedUtils
						.format(postValues, "utf-8");
				url += "?" + paramString;
				HttpGet httpGet = new HttpGet(url);

				HttpResponse httpResponse = httpClient.execute(httpGet);
				HttpEntity httpEntity = httpResponse.getEntity();
				is = httpEntity.getContent();

			} catch (UnsupportedEncodingException e) {
				e.printStackTrace();
			} catch (ClientProtocolException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}

			try {
				BufferedReader reader = new BufferedReader(
						new InputStreamReader(is, "iso-8859-1"), 8);
				StringBuilder sb = new StringBuilder();
				String line = null;
				while ((line = reader.readLine()) != null) {
					sb.append(line + "\n");
				}
				is.close();
				json = sb.toString();
			} catch (Exception e) {
				Log.e("Buffer Error", "Error converting result " + e.toString());
			}
			return true;

		}

		public void onPostExecute(Boolean success) {
			if (success) {
				Toast.makeText(getApplicationContext(),
						"Peluquería registrada", Toast.LENGTH_LONG).show();
			} else {
				Toast.makeText(getApplicationContext(), "Ha ocurrido un error",
						Toast.LENGTH_LONG).show();
			}
		}

	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu items for use in the action bar
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.main_activity_actions, menu);
		return super.onCreateOptionsMenu(menu);
	}

	@SuppressLint("SetJavaScriptEnabled")
	public void openMap() {
		WebView webView;
		setContentView(R.layout.actividad_principal);
		webView = (WebView) findViewById(R.id.webview);
		webView.getSettings().setJavaScriptEnabled(true);
		webView.loadUrl("http://batchgeo.com/map/8083b5087fe5cd6b78f485e7b834e34e");

	}

	public void openSignUp() {
		// Switching to Register screen
		Intent i = new Intent(getApplicationContext(), RegisterActivity.class);
		startActivity(i);

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
