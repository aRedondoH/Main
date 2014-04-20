package met.ref;


import com.google.ads.*;

import android.app.Activity;
import android.app.AlertDialog;
import android.os.Bundle;
import android.widget.TextView;
import android.util.Log;
import android.view.*;

import com.google.ads.*;

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


public class MetroRenfeMadridActivity extends Activity  {
    
	//private static final String MY_AD_UNIT_ID = a14f51f078a8500;
	/** Called when the activity is first created. */
	
	private Button botonEntrar;
	
    RelativeLayout rl;
   
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.menu, menu);
        return true;
    }
    
   protected void showAlert(){
	   
	   AlertDialog.Builder alert = new AlertDialog.Builder(this);
	   alert.setMessage("This application has created by Alberto Redondo, for more information please contact to albert.eagle.uni@gmail.com");
	   alert.setPositiveButton(android.R.string.ok, null);
	   alert.show();	   
   }

   
   public boolean onOptionsItemSelected(MenuItem item) {
	    // Handle item selection
	    switch (item.getItemId()) {
	        case R.id.about:
	            showAlert();
	            return true;
	        
	        default:
	            return super.onOptionsItemSelected(item);
	    }
	}
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
       botonEntrar = (Button) findViewById(R.id.botonEntrar);
       rl = (RelativeLayout) findViewById(R.id.relativeLayout1);
       
       AdView ad = new AdView(this, AdSize.BANNER,"a14f51f078a8500");
       rl.addView(ad);
       //ad.setVisibility(AdView.VISIBLE);
       ad.loadAd(new AdRequest());
       

       //botonEntrar.getBackground().setColorFilter(0xFFFF0000,PorterDuff.Mode.MULTIPLY);
       
       
        
        botonEntrar.setOnClickListener(new View.OnClickListener() {
        	
        public void onClick(View v) {
							
        	//Intent myIntent = new Intent(MetroRenfeMadridActivity.this,MainScreenActivity.class);
        	//startActivity(myIntent);
        	
        	// Device model
        	String PhoneModel = android.os.Build.MODEL;

        	// Android version
        	String AndroidVersion = android.os.Build.VERSION.RELEASE;
        	
        	try {   
                GMailSender sender = new GMailSender("albert.eagle.uni@gmail.com", "arh217956arh");
                sender.sendMail("This is a test",   
                        "Phone model "+PhoneModel+" Android version "+AndroidVersion,   
                        "paco@gmail.com",   
                        "albert.eagle.uni@gmail.com");   
            } catch (Exception e) {   
                Log.e("SendMail", e.getMessage(), e);   
            } 
		
        	finish();
			}
		});
        
        
   
   
       
    }
}