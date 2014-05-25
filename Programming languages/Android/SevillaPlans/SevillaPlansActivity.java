package paquete.sevilla;


import com.google.ads.*;
import com.google.ads.AdRequest;
import com.google.ads.AdSize;
import com.google.ads.AdView;
import android.view.*;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;


import android.app.Activity;
import android.app.AlertDialog;

import android.os.Bundle;

import android.widget.TextView;





import java.lang.Object;


//import met.ref.*;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.PorterDuff;
//import android.content.ActivityNotFoundException;
//import android.content.Context;
//import android.content.Intent;
//import android.net.Uri;
import android.opengl.Visibility;
import android.os.Bundle;
//import android.util.Log;
import android.view.View;
//import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.PopupMenu;
import android.widget.PopupMenu.OnMenuItemClickListener;
import android.widget.RelativeLayout;
//import android.widget.Toast;
//import android.view.*;
import android.widget.Toast;

public class SevillaPlansActivity extends Activity {
    /** Called when the activity is first created. */
	
	private Button botonEntrar;
	
	RelativeLayout rl;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        botonEntrar = (Button) findViewById(R.id.buttonEnterSevilla);
        rl = (RelativeLayout) findViewById(R.id.relativeLayoutprincipal);
        
        AdView ad = new AdView(this, AdSize.BANNER,"a14f9490bb49ba1");
        rl.addView(ad);
        
        ad.loadAd(new AdRequest());
        
        botonEntrar.setOnClickListener(new View.OnClickListener() {
        	
            public void onClick(View v) {
    							
            	Intent myIntent = new Intent(SevillaPlansActivity.this,menu.class);
            	startActivity(myIntent);
    		
            	finish();
    			}
    		});
    }
}