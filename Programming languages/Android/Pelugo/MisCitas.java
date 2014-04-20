package com.cliente.pelugo;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
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
import org.apache.http.util.ByteArrayBuffer;
import org.json.JSONArray;
import org.json.JSONObject;
import org.w3c.dom.Text;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.widget.EditText;
import android.widget.TextView;


public class MisCitas extends Activity{
	
	// Datos en servidor
	String IP_Server="www.pelugo.es";//IP DE NUESTRO PC
    String URL_connect="http://"+IP_Server+"/templates/dd_sosassy_19/droidlogin/acces.php";//ruta en donde estan nuestros archivos
	
	String respuestaServidor3;
	String user;
	EditText cubileteCitaActual;
	
	String line=null;
	InputStream is=null;
    String result=null;
    String[] citasCliente;
    
    TextView pelu;
    TextView tratamiento;
    TextView fecha;
    TextView horario;
    TextView confirmacion;
	
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState); 
        setContentView(R.layout.actividad_mostrarmicita);
        pelu = (TextView) findViewById(R.id.peluqueria);
        tratamiento = (TextView) findViewById(R.id.tratamiento);
        fecha = (TextView) findViewById(R.id.fecha);
        horario = (TextView) findViewById(R.id.horario);
        confirmacion = (TextView) findViewById(R.id.confirmacion);
        
        
        Bundle extras = getIntent().getExtras();
        //Obtenemos datos enviados en el intent.
        if (extras != null) {
     	   user  = extras.getString("user");//usuario
        }else{
     	   user="error";
     	   }
        
     // Utilizamos la clase Httpclient para conectar
        HttpClient httpclient = new DefaultHttpClient(); 
        
        // Utilizamos la HttpPost para enviar lso datos
        // A la url donde se encuentre nuestro archivo receptor
        HttpPost httppost = new HttpPost("http://"+IP_Server+"/templates/dd_sosassy_19/droidlogin/verCitaActualCliente.php");
        
        
        try { 
        	List<NameValuePair> postValues = new ArrayList<NameValuePair>(2);         	
            postValues.add(new BasicNameValuePair("user", user));
            
            
            //Encapsulamos
            httppost.setEntity(new UrlEncodedFormEntity(postValues));          
            //Lanzamos la petición
            HttpResponse respuesta = httpclient.execute(httppost);
            
            HttpEntity entity = respuesta.getEntity();
            Log.e("Fail 1", "4");
            
            

            is = entity.getContent();
            Log.e("Pass 1", "connection success ");
            
            try{
            	
            	BufferedReader reader = new BufferedReader(new InputStreamReader(is,"iso-8859-1"),8);
            	StringBuilder sb = new StringBuilder();
            	while ((line = reader.readLine()) != null)
            	{
            		sb.append(line + "\n");
            	}
            		result = sb.toString();
               }
               catch(Exception e)
               {
            	   Log.e("Fail 2", e.toString());
               }
            
                  
            try{
            	
            	JSONArray JA=new JSONArray(result);
            	JSONObject json= null;
            		json=JA.getJSONObject(0);
            		pelu.setText(json.getString("peluqueria"));
            		tratamiento.setText(json.getString("tipoDeCita"));
            		horario.setText(json.getString("hora"));
            		fecha.setText(json.getInt("dia")+"/"+json.getInt("mes")+"/"+json.getInt("anio"));
            		confirmacion.setText(json.getString("confirmacion"));
            		                                                           
            	}
            	catch(Exception e)
            	{
            		Log.e("Fail 3", e.toString());
            	}
               
        }catch (ClientProtocolException e) {
        		            // TODO Auto-generated catch block
         }catch (IOException e) {         
            //TODO Auto-generated catch block     
         } 
        }
        
        
        
	}
	
	


