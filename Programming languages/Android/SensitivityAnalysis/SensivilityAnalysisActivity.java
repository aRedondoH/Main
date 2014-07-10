package cube.analysis;

import com.google.ads.*;
import com.google.ads.AdRequest;
import com.google.ads.AdSize;
import com.google.ads.AdView;

import cube.analysis.*;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;

public class SensivilityAnalysisActivity extends Activity {
    /** Called when the activity is first created. */
	
	private Button buttonEnter;
	private LinearLayout r1;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        r1= (LinearLayout) findViewById(R.id.LinearLayout2);
        
        AdView ad = new AdView(this, AdSize.BANNER,"a14f6da417b92ac");
        r1.addView(ad);
        //ad.setVisibility(AdView.VISIBLE);
        ad.loadAd(new AdRequest());
        ad.loadAd(new AdRequest());
        
        buttonEnter = (Button) findViewById(R.id.button1);
        
        buttonEnter.setOnClickListener(new View.OnClickListener() {
        	
            public void onClick(View v) {
    							
            	Intent myIntent = new Intent(SensivilityAnalysisActivity.this,Menu.class);
            	startActivity(myIntent);
    		
            	finish();
    			}
    		});
    }
}