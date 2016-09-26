package com.cliente.pelugo;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class menuPeluquero extends Activity{
	
	private Button botonVercitas;
	private Button botonConfirmarCitas;
	private Button botonAnularCita;
	
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState); 
        setContentView(R.layout.actividad_menupeluquero);
        
        botonVercitas = (Button) findViewById(R.id.buttonVerCitas);
        botonConfirmarCitas = (Button) findViewById(R.id.buttonConfirmarCitas);
        botonAnularCita = (Button) findViewById(R.id.buttonAnularCita);
        
        botonVercitas.setOnClickListener(new View.OnClickListener() {
        	
            public void onClick(View v) {
            	
                							
            	Intent myIntent = new Intent(menuPeluquero.this,VerCitasPeluquero.class);
            	
            	startActivity(myIntent);
    		
            	//finish();
    			}
    		});
        
        botonConfirmarCitas.setOnClickListener(new View.OnClickListener() {
        	
            public void onClick(View v) {
            	
                							
            	Intent myIntent = new Intent(menuPeluquero.this,ConfirmarCitasPeluquero.class);
            	
            	startActivity(myIntent);
    		
            	//finish();
    			}
    		});
        
        botonAnularCita.setOnClickListener(new View.OnClickListener() {
        	
            public void onClick(View v) {
            	
                							
            	Intent myIntent = new Intent(menuPeluquero.this, anularCitaPeluquero.class);
            	
            	startActivity(myIntent);
    		
            	//finish();
    			}
    		});
        
        
	}

}
