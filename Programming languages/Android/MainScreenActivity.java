

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


public class MainScreenActivity extends Activity 	{
	
	private Button boton1;
	private Button boton2;
	private Button boton3;
	private LinearLayout rl;
	private Vibrator vibrator;
	
	
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState); 
        setContentView(R.layout.interfaz_grafica);
        
        boton1 = (Button) findViewById(R.id.boton1);
        boton3 = (Button) findViewById(R.id.button3);
        rl = (LinearLayout) findViewById(R.id.linearLayout1);
        
       AdView ad = new AdView(this, AdSize.BANNER,"a14f51f078a8500");
        AdView ad2 = new AdView(this, AdSize.BANNER,"a14f51f078a8500");
        rl.addView(ad);
        rl.addView(ad2);
        //ad.setVisibility(AdView.VISIBLE);
        ad.loadAd(new AdRequest());
        ad2.loadAd(new AdRequest());
        
        boton2 = (Button) findViewById(R.id.boton2);
        
        boton1.setOnClickListener(new View.OnClickListener() {
			
			public void onClick(View v2) {
				
				//CharSequence text = "Mostrando plano de metro";
				//Context context = getApplicationContext();
				//Toast.makeText(context, text, Toast.LENGTH_LONG).show();
				
				//vibrator = (Vibrator) (getSystemService(Service.VIBRATOR_SERVICE));
				//vibrator.vibrate(100);
				Intent myIntent = new Intent(MainScreenActivity.this,ImagenMetroActivity.class);
	        	startActivity(myIntent);
			
	        	
			}
        });
        
        boton2.setOnClickListener(new View.OnClickListener() {
			
			public void onClick(View v2) {
				
				//CharSequence text = "Mostrando plano de Cercanias";
				//Context context = getApplicationContext();
				//Toast.makeText(context, text, Toast.LENGTH_LONG).show();
				vibrator = (Vibrator) (getSystemService(Service.VIBRATOR_SERVICE));
				vibrator.vibrate(100);
				Intent myIntent = new Intent(MainScreenActivity.this,ImagenRenfeActivity.class);
	        	startActivity(myIntent);
			
	        	
			}
        });
        
        boton3.setOnClickListener(new View.OnClickListener() {
			
			public void onClick(View v2) {
				
				//CharSequence text = "Mostrando plano de Cercanias";
				//Context context = getApplicationContext();
				//Toast.makeText(context, text, Toast.LENGTH_LONG).show();
				vibrator = (Vibrator) (getSystemService(Service.VIBRATOR_SERVICE));
				vibrator.vibrate(100);
				Intent myIntent = new Intent(MainScreenActivity.this,ImagenMetroBuhoActivity.class);
	        	startActivity(myIntent);
			
	        	
			}
        });
		
	}
	
	

}
