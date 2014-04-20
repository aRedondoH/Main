package com.cliente.pelugo;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;


import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class CortarPelo extends Activity{
	
	private Button botonPedirCita;
	private Button botonMisCitas;
	private Button botonInfo;
	String user;
	//String IP_Server="192.168.1.134";//IP DE NUESTRO PC casa
	//String IP_Server="192.168.0.198";//IP DE NUESTRO PC 
	
	// Datos en servidor
    String IP_Server="pelugo.atwebpages.com";//IP DE NUESTRO PC
	//String IP_Server="192.168.0.198";//IP DE NUESTRO PC 
    String URL_connect="http://"+IP_Server+"/droidlogin/acces.php";//ruta en donde estan nuestros archivos
    
    
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState); 
        setContentView(R.layout.actividad_cortarpelo);
        
        Bundle extras = getIntent().getExtras();
        //Obtenemos datos enviados en el intent.
        if (extras != null) {
     	   user  = extras.getString("user");//usuario
        }else{
     	   user="error";
     	   }
        
        botonPedirCita = (Button) findViewById(R.id.appointmentbutton);
        botonMisCitas = (Button) findViewById(R.id.MisCitas);
        botonInfo = (Button) findViewById(R.id.Info);
        
        botonPedirCita.setOnClickListener(new View.OnClickListener() {
        	
            public void onClick(View v) {
            	
            	Intent myIntent = new Intent(CortarPelo.this,PedirCita.class);
            	myIntent.putExtra("user",user);
            	startActivity(myIntent);
    		
            	//finish();
            	//Intent myIntent = new Intent(CortarPelo.this,PedirCita.class);
            	//startActivity(myIntent);
            	//Abre el navegador al formulario adduser.html
            	
            	/*String url = "http://"+IP_Server+"/droidlogin/pedirCita.html";
        		Intent i = new Intent(Intent.ACTION_VIEW);      		
        		i.setData(Uri.parse(url));
        		//i.putExtra("user",user);
        		startActivity(i);		*/			
            	
        	
    	   
            	
            /*	//Utilizamos la clase Httpclient para conectar
                HttpClient httpclient = new DefaultHttpClient();   
                //Utilizamos la HttpPost para enviar lso datos
                //A la url donde se encuentre nuestro archivo receptor
                HttpPost httppost = new HttpPost("http://"+IP_Server+"/droidlogin/pedirCita2.php");      
                try {         
                //Añadimos los datos a enviar en este caso solo uno
                //que le llamamos de nombre 'a'
                //La segunda linea podría repetirse tantas veces como queramos
                //siempre cambiando el nombre ('a')
                List<NameValuePair> postValues = new ArrayList<NameValuePair>(2);         
                postValues.add(new BasicNameValuePair("user", "Alberto"));
                postValues.add(new BasicNameValuePair("dia_cita", "20121203"));
                postValues.add(new BasicNameValuePair("hora_cita", "18:30"));
                postValues.add(new BasicNameValuePair("confirmacion", "si"));
                
                //Encapsulamos
                httppost.setEntity(new UrlEncodedFormEntity(postValues));          
                //Lanzamos la petición
                HttpResponse respuesta = httpclient.execute(httppost);
                //Conectamos para recibir datos de respuesta
                HttpEntity entity = respuesta.getEntity();
                
            }catch (IOException e) {         
                //TODO Auto-generated catch block     
             } 
            
    	   	 
    	    */
    			}
    		});
        
        botonInfo.setOnClickListener(new View.OnClickListener() {
        	
            public void onClick(View v) {
    							
            	Intent myIntent = new Intent(CortarPelo.this,Precios.class);
            	startActivity(myIntent);
    		
            	//finish();
    			}
    		});
        
        
        botonMisCitas.setOnClickListener(new View.OnClickListener() {
        	
            public void onClick(View v) {
            	
            	Intent myIntent = new Intent(CortarPelo.this, MisCitas.class);
            	myIntent.putExtra("user",user);
            	startActivity(myIntent);
    							
            	//Toast toast2 = Toast.makeText(getApplicationContext(),"Próximamente", Toast.LENGTH_SHORT);
         	    //toast2.show(); 
    			}
    		});
        
	
	}
	
	

}
