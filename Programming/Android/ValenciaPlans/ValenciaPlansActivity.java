package mi.paquete.valencia;


import com.google.ads.*;
import com.google.ads.AdRequest;
import com.google.ads.AdSize;
import com.google.ads.AdView;
import android.view.*;


import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;

public class ValenciaPlansActivity extends Activity {
    /** Called when the activity is first created. */
	
	private Button botonEntrar;
	RelativeLayout rl;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        botonEntrar = (Button) findViewById(R.id.buttonEntrar);
        rl = (RelativeLayout) findViewById(R.id.relativeLayoutprincipal);
        
        AdView ad = new AdView(this, AdSize.BANNER,"a14fef1844e4f1a");
        rl.addView(ad);
        
        ad.loadAd(new AdRequest());
        
        botonEntrar.setOnClickListener(new View.OnClickListener() {
        	
            public void onClick(View v) {
    							
            	Intent myIntent = new Intent(ValenciaPlansActivity.this,menu.class);
            	startActivity(myIntent);
    		
            	finish();
    			}
    		});
    }
}