package mi.paquete.valencia;




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
import android.widget.RelativeLayout;
import android.widget.Toast;

public class menu extends Activity{
	
	private Button boton1;
	private Button boton2;
	private Button boton3;
	private Vibrator vibrator;
	private RelativeLayout r2;
	
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState); 
        setContentView(R.layout.menu);
        
        boton1 = (Button) findViewById(R.id.button1);
        boton2 = (Button) findViewById(R.id.button2);
        boton3 = (Button) findViewById(R.id.buttonbus);
        
        r2 = (RelativeLayout) findViewById(R.id.relativeLayoutpublicidadmenu);
        
        AdView ad = new AdView(this, AdSize.BANNER,"a14fef1844e4f1a");
        AdView ad2 = new AdView(this, AdSize.BANNER,"a14fef1844e4f1a");
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
				Intent myIntent = new Intent(menu.this,zoommetrovalencia.class);
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
				Intent myIntent = new Intent(menu.this,zoomrenfevalencia.class);
	        	startActivity(myIntent);
			
	        	
			}
        });
        
        boton3.setOnClickListener(new View.OnClickListener() {
			
			public void onClick(View v) {
				vibrator = (Vibrator) (getSystemService(Service.VIBRATOR_SERVICE));
				vibrator.vibrate(100);
				/*CharSequence text = "Soon";
				Context context = getApplicationContext();
				Toast.makeText(context, text, Toast.LENGTH_LONG).show();*/
				Intent myIntent = new Intent(menu.this,gestionlineasbus.class);
	        	startActivity(myIntent);
				
				
			}
		});
	}    

}
