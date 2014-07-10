package met.ref;

import com.google.ads.AdRequest;
import com.google.ads.AdSize;
import com.google.ads.AdView;

import android.app.Activity;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Vibrator;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.Toast;



public class MainScreenActivity extends Activity {

	private Button boton1;
	private Button boton2;
	private Button boton3;
	private LinearLayout rl;
	
	/* Google advertising */
	public void googleAdvertising() {
		rl = (LinearLayout) findViewById(R.id.linearLayout1);
		AdView ad = new AdView(this, AdSize.BANNER, "a14f51f078a8500");
		rl.addView(ad);
		ad.loadAd(new AdRequest());
	}
	
	/* Airpush advertising (Banner)*/ 
	// It is inicialized from .xml file

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.interfaz_grafica);

		// Assigning buttons to the layout elements
		boton1 = (Button) findViewById(R.id.boton1);
		boton2 = (Button) findViewById(R.id.boton2);
		boton3 = (Button) findViewById(R.id.button3);

		/* Initializate google advertising */
		googleAdvertising();

		boton1.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v2) {
				// CharSequence text = "Mostrando plano de metro";
				// Context context = getApplicationContext();
				// Toast.makeText(context, text, Toast.LENGTH_LONG).show();
				Intent myIntent = new Intent(MainScreenActivity.this,
						ImagenMetroActivity.class);
				startActivity(myIntent);
			}
		});

		boton2.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v2) {
				// CharSequence text = "Mostrando plano de Cercanias";
				// Context context = getApplicationContext();
				// Toast.makeText(context, text, Toast.LENGTH_LONG).show();
				Intent myIntent = new Intent(MainScreenActivity.this,
						ImagenRenfeActivity.class);
				startActivity(myIntent);
			}
		});

		boton3.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v2) {
				// CharSequence text = "Mostrando plano de Cercanias";
				// Context context = getApplicationContext();
				// Toast.makeText(context, text, Toast.LENGTH_LONG).show();
				Intent myIntent = new Intent(MainScreenActivity.this,
						ImagenMetroBuhoActivity.class);
				startActivity(myIntent);
			}
		});
	}
}
