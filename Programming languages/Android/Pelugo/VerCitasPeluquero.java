package com.cliente.pelugo;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.util.ByteArrayBuffer;

import android.app.Activity;
import android.os.Bundle;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class VerCitasPeluquero extends Activity{
	
//String IP_Server="192.168.0.198";//IP DE NUESTRO PC 
//String IP_Server="192.168.1.134";//IP DE NUESTRO PC
	
	// Datos en servidor
    String IP_Server="pelugo.atwebpages.com";//IP DE NUESTRO PC
	//String IP_Server="192.168.0.198";//IP DE NUESTRO PC 
    String URL_connect="http://"+IP_Server+"/droidlogin/acces.php";//ruta en donde estan nuestros archivos	


String respuestaServidor;
EditText cubilete;

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState); 
        setContentView(R.layout.actividad_vercitaspeluquero);
        cubilete=(EditText) findViewById(R.id.editorParaVerCitas);
        
     // Utilizamos la clase Httpclient para conectar
        HttpClient httpclient = new DefaultHttpClient();   
        // Utilizamos la HttpPost para enviar lso datos
        // A la url donde se encuentre nuestro archivo receptor
        HttpPost httppost = new HttpPost("http://"+IP_Server+"/droidlogin/verCitasPeluquero.php");      
        try { 
        	List<NameValuePair> postValues = new ArrayList<NameValuePair>(2);         
            /*postValues.add(new BasicNameValuePair("user", user));
            postValues.add(new BasicNameValuePair("dia_cita", fecha));
            postValues.add(new BasicNameValuePair("hora_cita", hora));
            postValues.add(new BasicNameValuePair("confirmacion", "no"));*/
            
            //Encapsulamos
            httppost.setEntity(new UrlEncodedFormEntity(postValues));          
            //Lanzamos la petición
            HttpResponse respuesta = httpclient.execute(httppost);
            
            
            
            InputStream is = respuesta.getEntity().getContent();
            BufferedInputStream bis = new BufferedInputStream(is);
            ByteArrayBuffer baf = new ByteArrayBuffer(20);
            	 
            int current = 0;
            	             
            while((current = bis.read()) != -1){
                 baf.append((byte)current);
            } 
            	 
             //Convert the Bytes read to a String. 
              respuestaServidor = new String(baf.toByteArray());
              respuestaServidor.replace("\\n", "\n");
              cubilete.setText(respuestaServidor);
              //Toast.makeText(getApplicationContext(),respuestaServidor,Toast.LENGTH_LONG).show();
            
           
            
        }catch (ClientProtocolException e) {
        		            // TODO Auto-generated catch block
         }catch (IOException e) {         
            //TODO Auto-generated catch block     
         } 
        }
        
        
        
	
        

}
