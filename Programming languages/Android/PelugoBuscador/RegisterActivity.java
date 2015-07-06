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
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
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
	public Spinner spinnerTypeOfHairdresser;
	public EditText facebookHS;

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

		spinnerTypeOfHairdresser = (Spinner) findViewById(R.id.typeOfHairdresser_spinner);
		// Create an ArrayAdapter using the string array and a default spinner layout
		ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this,R.array.typeOfHairdresser_array,android.R.layout.simple_spinner_item);
		// Specify the layout to use when the list of choices appears
		adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		// Apply the adapter to the spinner
		spinnerTypeOfHairdresser.setAdapter(adapter);

		facebookHS = (EditText) findViewById(R.id.facebookWebsite);

		signUpHairdresser = (Button) findViewById(R.id.btnRegister);
		signUpHairdresser.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				new ConnectAsync().execute(nameHS.getText().toString(),
						addressHS.getText().toString(), cityHS.getText()
								.toString(), provinceHS.getText().toString(),
						timetableHS.getText().toString(), emailHS.getText()
								.toString(), phoneHS.getText().toString(),spinnerTypeOfHairdresser.getSelectedItem().toString(),facebookHS.getText().toString());
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
				postValues.add(new BasicNameValuePair("typeOfHairdresser",params[7]));
				postValues.add(new BasicNameValuePair("facebookPageHairdresser",params[8]));

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

	//@SuppressLint("SetJavaScriptEnabled")
	public void openMap() {
		//Intent intent = new Intent(getApplicationContext(), MapaWebView.class);
		//startActivity(intent);
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
	
	@SuppressLint("SetJavaScriptEnabled")
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
