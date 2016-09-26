package com.cliente.pelugo;


import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;



public class menuPrincipal extends Activity{
	
	private Button botonPedirCita;
	private Button botonMisCitas;
	private Button botonInfoPelu;
	String user;
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState); 
        setContentView(R.layout.actividad_menuclientev2);
        
        Bundle extras = getIntent().getExtras();
        //Obtenemos datos enviados en el intent.
        if (extras != null) {
     	   user  = extras.getString("user");//usuario
        }else{
     	   user="error";
     	   }
        
        botonPedirCita= (Button) findViewById(R.id.pedirCitaButton);
        
        botonPedirCita.setOnClickListener(new View.OnClickListener() {
			
			public void onClick(View v) {
				Intent iv2=new Intent(menuPrincipal.this, PedirCita.class);
				iv2.putExtra("user",user);				
				startActivity(iv2);
				
			}
		});
        
        botonMisCitas = (Button) findViewById(R.id.verMisCitasButton);
        
        botonMisCitas.setOnClickListener(new View.OnClickListener() {
			
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent iv3=new Intent(menuPrincipal.this, MisCitas.class);
				iv3.putExtra("user",user);				
				startActivity(iv3);
			}
		});
        
        botonInfoPelu=(Button) findViewById(R.id.infoOfertasButton);
        
        botonInfoPelu.setOnClickListener (new View.OnClickListener(){
        	
        	public void onClick ( View v){
        		String url = "http://www.pelugo.es/index.php/peluquerias-inscritas";
        		Intent i = new Intent(Intent.ACTION_VIEW);
        		i.setData(Uri.parse(url));
        		startActivity(i);
        		
        	}
        	
        });
        
       /* botonCortarPelo = (Button) findViewById(R.id.CutHairbutton);
        
        botonCortarPelo.setOnClickListener(new View.OnClickListener() {
        	
            public void onClick(View v) {
            	
            	//Toast toast1 = Toast.makeText(getApplicationContext(),"Usuario: "+user, Toast.LENGTH_SHORT);
         	    //toast1.show();
    							
            	Intent myIntent = new Intent(menuPrincipal.this,CortarPelo.class);
            	myIntent.putExtra("user",user);
            	startActivity(myIntent);
    		
            	finish();
    			}
    		});*/
        
        
	
	}

}
