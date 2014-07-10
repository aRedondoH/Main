package paquete.sevilla;


import com.google.ads.*;
import android.view.*;
import com.google.ads.AdRequest;
import com.google.ads.AdSize;
import com.google.ads.AdView;

import com.google.ads.AdRequest;
import com.google.ads.AdSize;
import com.google.ads.AdView;


import android.app.Activity;
import android.app.Service;
import android.content.Intent;
import android.os.Bundle;
import android.os.Vibrator;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;

public class menu extends Activity{
	
	private Button boton1;
	private Button boton2;
	private Button boton3;
	
	private Vibrator vibrator;
	private RelativeLayout r2;
	
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState); 
        setContentView(R.layout.menuplans);
        
        boton1 = (Button) findViewById(R.id.buttonmetrosevilla);
        boton2 = (Button) findViewById(R.id.buttoncercaniassevilla);
        boton3 = (Button) findViewById(R.id.buttonbus);
        
        r2 = (RelativeLayout) findViewById(R.id.relativeLayoutpublicidadmenu2);
        
        AdView ad = new AdView(this, AdSize.BANNER,"a14f9490bb49ba1");
        AdView ad2 = new AdView(this, AdSize.BANNER,"a14f9490bb49ba1");
        r2.addView(ad);
        r2.addView(ad2);
        
        ad.loadAd(new AdRequest());
        ad2.loadAd(new AdRequest());
        
      
        boton1.setOnClickListener(new View.OnClickListener() {
			
			public void onClick(View v2) {
				
				//CharSequence text = "Mostrando plano de metro";
				//Context context = getApplicationContext();
				//Toast.makeText(context, text, Toast.LENGTH_LONG).show();
				
				vibrator = (Vibrator) (getSystemService(Service.VIBRATOR_SERVICE));
				vibrator.vibrate(100);
				Intent myIntent = new Intent(menu.this,zoommetrosevilla.class);
	        	startActivity(myIntent);
			
	        	
			}
        });
        
        boton2.setOnClickListener(new View.OnClickListener() {
			
			public void onClick(View v2) {
				
				//CharSequence text = "Mostrando plano de metro";
				//Context context = getApplicationContext();
				//Toast.makeText(context, text, Toast.LENGTH_LONG).show();
				
				vibrator = (Vibrator) (getSystemService(Service.VIBRATOR_SERVICE));
				vibrator.vibrate(100);
				Intent myIntent = new Intent(menu.this,zoomcercaniassevilla.class);
	        	startActivity(myIntent);
			
	        	
			}
        });
        
        boton3.setOnClickListener(new View.OnClickListener() {
			
			public void onClick(View v3) {
				vibrator = (Vibrator) (getSystemService(Service.VIBRATOR_SERVICE));
				vibrator.vibrate(100);
				Intent myIntent = new Intent(menu.this, gestionlineasbus.class);
				startActivity(myIntent);
			}
		});
        
       
		
	}
	
	

}
