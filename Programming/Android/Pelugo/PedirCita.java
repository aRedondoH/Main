package com.cliente.pelugo;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Calendar;
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
import org.json.JSONException;
import org.json.JSONObject;
import com.cliente.pelugo.Portada.asynclogin;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.StrictMode;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

public class PedirCita extends Activity{
	



//Datos en servidor
String IP_Server="www.pelugo.es";//IP DE NUESTRO PC
String URL_connect="http://"+IP_Server+"/templates/dd_sosassy_19/droidlogin/obtenerPeluquerias.php";//ruta en donde estan nuestros archivos

String user;

Button botonActualizarPeluquerias;
Button botonActualizarTratamientos;
Button botonActualizarHorarios;
Button botonConfirmarCita;


DatePicker dpResult;
private int year;
private int month;
private int day;
String fecha;
String mes="Enero"; // Para ponerlo en español
private String hora;
private String respuestaServidor;

private Spinner spinnerPeluquerias;
private Spinner spinnerTratamientos;
private Spinner spinnerHorarios;

String[] id_pelus;
String[] peluquerias;
String[] tratamientos;
String[] horarios;


String eleccionPeluqueriaGlobal;
String eleccionTratamientoGlobal;
String eleccionHorarioGlobal;




	
	
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState); 
        setContentView(R.layout.actividad_pedircitav2);
        
        Bundle extras = getIntent().getExtras();
        //Obtenemos datos enviados en el intent.
        if (extras != null) {
     	   user  = extras.getString("user");//usuario
        }else{
     	   user="error";
     	   }
       
      //Avoid NetworkOnMainThreadException 
        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);
        
        
        InputStream is=null;
        InputStream is2=null;
        //InputStream is3=null;
        
        String line=null;
        String line2=null;
        String result=null;
        String result2=null;
        
        botonActualizarPeluquerias = (Button) findViewById(R.id.buttonActualizarPeluqueria);
        botonActualizarTratamientos = (Button) findViewById(R.id.buttonActualizarTratamiento);
        botonActualizarHorarios = (Button) findViewById(R.id.buttonActualizarHorario);
        botonConfirmarCita = (Button) findViewById(R.id.confirmarLaCitaDelCliente);
        
        spinnerPeluquerias= (Spinner) findViewById(R.id.spinnerPeluqueria);
        spinnerTratamientos = (Spinner) findViewById(R.id.spinnerTratamiento);
        spinnerHorarios = (Spinner) findViewById(R.id.spinnerHorario);
        
    	dpResult = (DatePicker) findViewById(R.id.fechadorv2);
        
        final List<String> list1 = new ArrayList<String>();
        final List<String> list2 = new ArrayList<String>();
        final List<String> list3 = new ArrayList<String>();
        
        botonActualizarHorarios.setOnClickListener(new View.OnClickListener() {   
        	
        	InputStream is3=null;
        	String line3=null;
        	String result3=null;
        	
            public void onClick(View view) {
            	
            	//						   //
            	// Rellenamos los horarios //
            	//						   //
            	
            	try{
            	
            		// Utilizamos la clase Httpclient para conectar
                	HttpClient httpclient3 = new DefaultHttpClient(); 
                
                	// Utilizamos la HttpPost para enviar lso datos
                	// A la url donde se encuentre nuestro archivo receptor
                	HttpPost httppost3 = new HttpPost("http://"+IP_Server+"/templates/dd_sosassy_19/droidlogin/verHorariosPeluquerias.php");      
                
                	List<NameValuePair> postValues = new ArrayList<NameValuePair>(2);         	
                    postValues.add(new BasicNameValuePair("pelu", eleccionPeluqueriaGlobal));
                    
                    //Encapsulamos
                    httppost3.setEntity(new UrlEncodedFormEntity(postValues));          
                    //Lanzamos la petición
                    HttpResponse respuesta3 = httpclient3.execute(httppost3);
                    
                    HttpEntity entity3 = respuesta3.getEntity();
                    Log.e("Fail 1", "4");
                    
                    is3 = entity3.getContent();
                    Log.e("Pass 1", "connection success ");
            
            	}     
            	
            	catch(Exception e)
                {
                		 Log.e("Fail 1", e.toString());
                		 Toast.makeText(getApplicationContext(), "Invalid IP Address Paco 1",Toast.LENGTH_LONG).show();
                		 finish();

                }
            	
            	 try{
                 	
                 	BufferedReader reader = new BufferedReader(new InputStreamReader(is3,"iso-8859-1"),8);
                 	StringBuilder sb = new StringBuilder();
                 	while ((line3 = reader.readLine()) != null)
                 	{
                 		sb.append(line3 + "\n");
                 	}
                 		result3 = sb.toString();
                    }
                    catch(Exception e)
                    {
                 	   Log.e("Fail 2", e.toString());
                    }
                 
                       
                 try{
                 	
                 	JSONArray JA3=new JSONArray(result3);
                 	JSONObject json3= null;
                 
                 	json3=JA3.getJSONObject(0);
                 	
                 	
                 	int contador=0;
                 	
                 	int uno=json3.getInt("8_30");
                 	if (uno==1){
                 		contador++;
                 	}
                 	int dos=json3.getInt("9_");
                 	if (dos==1){
                 		contador++;
                 	}
                 	int tres=json3.getInt("9_30");
                 	if (tres==1){
                 		contador++;
                 	}
                 	int cuatro=json3.getInt("10_");
                 	if (cuatro==1){
                 		contador++;
                 	}
                 	int cinco=json3.getInt("10_30");
                 	if (cinco==1){
                 		contador++;
                 	}
                 	int seis=json3.getInt("11_");
                 	if (seis==1){
                 		contador++;
                 	}
                 	int siete=json3.getInt("11_30");
                 	if (siete==1){
                 		contador++;
                 	}
                 	int ocho=json3.getInt("12_");
                 	if (ocho==1){
                 		contador++;
                 	}
                 	int nueve=json3.getInt("12_30");
                 	if (nueve==1){
                 		contador++;
                 	}
                 	int diez=json3.getInt("13_");
                 	if (diez==1){
                 		contador++;
                 	}
                 	int once=json3.getInt("13_30");
                 	if (once==1){
                 		contador++;
                 	}
                 	int doce=json3.getInt("14_");
                 	if (doce==1){
                 		contador++;
                 	}
                 	int trece=json3.getInt("14_30");
                 	if (trece==1){
                 		contador++;
                 	}
                 	int catorce=json3.getInt("15_");
                 	if (catorce==1){
                 		contador++;
                 	}
                 	int quince=json3.getInt("15_30");
                 	if (quince==1){
                 		contador++;
                 	}
                 	int dieciseis=json3.getInt("16_");
                 	if (dieciseis==1){
                 		contador++;
                 	}
                 	int diecisiete=json3.getInt("16_30");
                 	if (diecisiete==1){
                 		contador++;
                 	}
                 	int dieciocho=json3.getInt("17_");
                 	if (dieciocho==1){
                 		contador++;
                 	}
                 	int diecinueve=json3.getInt("17_30");
                 	if (diecinueve==1){
                 		contador++;
                 	}
                 	int veinte=json3.getInt("18_");
                 	if (veinte==1){
                 		contador++;
                 	}
                 	int veintiuno=json3.getInt("18_30");
                 	if (veintiuno==1){
                 		contador++;
                 	}
                 	int veintidos=json3.getInt("19_");
                 	if (veintidos==1){
                 		contador++;
                 	}
                 	int veintitres=json3.getInt("19_30");
                 	if (veintitres==1){
                 		contador++;
                 	}
                 	int veinticuatro=json3.getInt("20_");
                 	if (veinticuatro==1){
                 		contador++;
                 	}
                 	int veinticinco=json3.getInt("20_30");
                 	if (veinticinco==1){
                 		contador++;
                 	}
                 	int veintiseis=json3.getInt("21_");
                 	if (veintiseis==1){
                 		contador++;
                 	}
                 	int veintisiete=json3.getInt("21_30");
                 	if (veintisiete==1){
                 		contador++;
                 	}
                 	int veintiocho=json3.getInt("22_");
                 	if (veintiocho==1){
                 		contador++;
                 	}
                 	int veintinueve=json3.getInt("22_30");
                 	if (veintinueve==1){
                 		contador++;
                 	}
                 	int treinta=json3.getInt("23_");
                 	if (treinta==1){
                 		contador++;
                 	}
                 	
                 	horarios = new String[contador];                 	
                 	contador = 0;
                 	
                 	uno=json3.getInt("8_30");
                 	if (uno==1){
                 		horarios[contador++]="8:30";
                 	}
                 	dos=json3.getInt("9_");
                 	if (dos==1){
                 		horarios[contador++]="9:00";
                 	}
                 	tres=json3.getInt("9_30");
                 	if (tres==1){
                 		horarios[contador++]="9:30";
                 	}
                 	cuatro=json3.getInt("10_");
                 	if (cuatro==1){
                 		horarios[contador++]="10:00";
                 	}
                 	cinco=json3.getInt("10_30");
                 	if (cinco==1){
                 		horarios[contador++]="10:30";
                 	}
                 	seis=json3.getInt("11_");
                 	if (seis==1){
                 		horarios[contador++]="11:00";
                 	}
                 	siete=json3.getInt("11_30");
                 	if (siete==1){
                 		horarios[contador++]="11:30";
                 	}
                 	ocho=json3.getInt("12_");
                 	if (ocho==1){
                 		horarios[contador++]="12:00";
                 	}
                 	nueve=json3.getInt("12_30");
                 	if (nueve==1){
                 		horarios[contador++]="12:30";
                 	}
                 	diez=json3.getInt("13_");
                 	if (diez==1){
                 		horarios[contador++]="13:00";
                 	}
                 	once=json3.getInt("13_30");
                 	if (once==1){
                 		horarios[contador++]="13:30";
                 	}
                 	doce=json3.getInt("14_");
                 	if (doce==1){
                 		horarios[contador++]="14:00";
                 	}
                 	trece=json3.getInt("14_30");
                 	if (trece==1){
                 		horarios[contador++]="14:30";
                 	}
                 	catorce=json3.getInt("15_");
                 	if (catorce==1){
                 		horarios[contador++]="15:00";
                 	}
                 	quince=json3.getInt("15_30");
                 	if (quince==1){
                 		horarios[contador++]="15:30";
                 	}
                 	dieciseis=json3.getInt("16_");
                 	if (dieciseis==1){
                 		horarios[contador++]="16:00";
                 	}
                 	diecisiete=json3.getInt("16_30");
                 	if (diecisiete==1){
                 		horarios[contador++]="16:30";
                 	}
                 	dieciocho=json3.getInt("17_");
                 	if (dieciocho==1){
                 		horarios[contador++]="17:00";
                 	}
                 	diecinueve=json3.getInt("17_30");
                 	if (diecinueve==1){
                 		horarios[contador++]="17:30";
                 	}
                 	veinte=json3.getInt("18_");
                 	if (veinte==1){
                 		horarios[contador++]="18:00";
                 	}
                 	veintiuno=json3.getInt("18_30");
                 	if (veintiuno==1){
                 		horarios[contador++]="18:30";
                 	}
                 	veintidos=json3.getInt("19_");
                 	if (veintidos==1){
                 		horarios[contador++]="19:30";
                 	}
                 	veintitres=json3.getInt("19_30");
                 	if (veintitres==1){
                 		horarios[contador++]="19:30";
                 	}
                 	veinticuatro=json3.getInt("20_");
                 	if (veinticuatro==1){
                 		horarios[contador++]="20:00";
                 	}
                 	veinticinco=json3.getInt("20_30");
                 	if (veinticinco==1){
                 		horarios[contador++]="20:30";
                 	}
                 	veintiseis=json3.getInt("21_");
                 	if (veintiseis==1){
                 		horarios[contador++]="21:00";
                 	}
                 	veintisiete=json3.getInt("21_30");
                 	if (veintisiete==1){
                 		horarios[contador++]="21:30";
                 	}
                 	veintiocho=json3.getInt("22_");
                 	if (veintiocho==1){
                 		horarios[contador++]="22:00";
                 	}
                 	veintinueve=json3.getInt("22_30");
                 	if (veintinueve==1){
                 		horarios[contador++]="22:30";
                 	}
                 	treinta=json3.getInt("23_");
                 	if (treinta==1){
                 		horarios[contador++]="23:00";
                 	}
                 	
                 	
                 	
                 	spinner_fn3();
                                                                                
                 	}
                 	catch(Exception e)
                 	{
                 		Log.e("Fail 3", e.toString());
                 	}
            	
            	
            }      
          });
        
        
        
        
        //							  //
        // Rellenamos las peluquerias //
        //							  //
        
        
        try { 
        	
        	 // Utilizamos la clase Httpclient para conectar
            HttpClient httpclient = new DefaultHttpClient();
            
            // Utilizamos la HttpPost para enviar los datos
            // A la url donde se encuentre nuestro archivo receptor
            HttpPost httppost = new HttpPost("http://"+IP_Server+"/templates/dd_sosassy_19/droidlogin/obtenerPeluquerias.php");
            
            //Lanzamos la petición
            HttpResponse respuesta = httpclient.execute(httppost);
            
            HttpEntity entity = respuesta.getEntity();
            Log.e("Fail 1", "4");
            
            is = entity.getContent();
            Log.e("Pass 1", "connection success ");
            
            
            }
            	catch(Exception e)
            {
            		 Log.e("Fail 1", e.toString());
            		 Toast.makeText(getApplicationContext(), "Invalid IP Address Paco 2",Toast.LENGTH_LONG).show();
            		 finish();

            }
        
            
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
        	peluquerias = new String[JA.length()];       

        	for(int i=0;i<JA.length();i++)
        	{
        		json=JA.getJSONObject(i);
        		peluquerias[i] = json.getString("nombre");
        	}
        
        	
        	spinner_fn();
                                                                       
        	}
        	catch(Exception e)
        	{
        		Log.e("Fail 3", e.toString());
        	}
        
        
        	     
	
	// 							   //
	// Rellenamos los tratamientos //
	//							   //
	
        try { 
        	
       	 // Utilizamos la clase Httpclient para conectar  
           HttpClient httpclient2 = new DefaultHttpClient();
           
           // Utilizamos la HttpPost para enviar los datos
           // A la url donde se encuentre nuestro archivo receptor
           HttpPost httppost2 = new HttpPost("http://"+IP_Server+"/templates/dd_sosassy_19/droidlogin/obtenerTratamiento.php");
           
           //Lanzamos la petición
           HttpResponse respuesta2 = httpclient2.execute(httppost2);
           HttpEntity entity2 = respuesta2.getEntity();
           Log.e("Fail 1", "4");
           

           is2 = entity2.getContent();
           Log.e("Pass 2", "connection success ");
           
           
           }
           	catch(Exception e)
           {
           		 Log.e("Fail 1", e.toString());
           		 Toast.makeText(getApplicationContext(), "Invalid IP Address Paco 3",Toast.LENGTH_LONG).show();
           		 finish();

           }
       
      
       
       try{
       	
       	BufferedReader reader2 = new BufferedReader(new InputStreamReader(is2,"iso-8859-1"),8);
       	StringBuilder sb2 = new StringBuilder();
       	while ((line2 = reader2.readLine()) != null)
       	{
       		sb2.append(line2 + "\n");
       	}
       		is2.close();
       		result2 = sb2.toString();
          }
          catch(Exception e)
          {
       	   Log.e("Fail 2", e.toString());
          }
       
       
       try{
       	
       	
       	JSONArray JA2=new JSONArray(result2);
       	JSONObject json2 = null;       
       	tratamientos = new String[JA2.length()];

       	for(int i=0;i<JA2.length();i++)
       	{
       		json2=JA2.getJSONObject(i);        		
       		tratamientos[i] = json2.getString("tipo");
       	}
       	
       	
       	
       	for(int i=0;i<tratamientos.length;i++)
       	{      		        
       		list2.add(tratamientos[i]);
       	}
         
       	spinner_fn2();
                                                                      
       	}
       	catch(Exception e)
       	{
       		Log.e("Fail 3", e.toString());
       	}
       
       
	
	// ********************************* // 
	// 			Confirmamos cita		 //
	// ********************************* //
        
        
     
        
        botonConfirmarCita.setOnClickListener(new View.OnClickListener() {
        	
            public void onClick(View v) {
            	     
                try {         
                
                	
                	
                	//	Cogemos la fecha                 	
            		day = dpResult.getDayOfMonth();
            		month = dpResult.getMonth();
            		
            		// Pasamos el mes al español
            		switch(month){
            		  case 0: mes="Enero";
            		       break;
            		  case 1: mes="Febrero";
            		       break;
            		  case 2: mes="Marzo";
       		       		   break;
            		  case 3: mes="Abril";
       		               break;
            		  case 4: mes="Mayo";
       		       		   break;
            		  case 5: mes="Junio";
       		       		   break;
            		  case 6: mes="Julio";
       		       		   break;
            		  case 7: mes="Agosto";
       		       	       break;
            		  case 8: mes="Septiembre";
       		       		   break;
            		  case 9: mes="Octubre";
       		               break;
            		  case 10: mes="Noviembre";
       		               break;
            		  case 11: mes="Diciembre";
       		       		   break;
            		  }
            		
            		// Cogemos el año
            		year = dpResult.getYear();
            		// Incluimos todos los parámetros             	
            		// set current date into datepicker
            		dpResult.init(year, month, day, null);
                	
                
                	
                	
                String diaElegido = String.valueOf(day);
                String mesElegido = String.valueOf(month+1);
                String anioElegido = String.valueOf(year);
                List<NameValuePair> postValues = new ArrayList<NameValuePair>(2);         
                postValues.add(new BasicNameValuePair("user", user));
                
                postValues.add(new BasicNameValuePair("dia", diaElegido));
                postValues.add(new BasicNameValuePair("mes", mesElegido));
                postValues.add(new BasicNameValuePair("anio", anioElegido));
                
                postValues.add(new BasicNameValuePair("pelu", eleccionPeluqueriaGlobal));
                postValues.add(new BasicNameValuePair("tratamiento", eleccionTratamientoGlobal));
                postValues.add(new BasicNameValuePair("horario", eleccionHorarioGlobal));
                String confirmacion="no";
                postValues.add(new BasicNameValuePair("confirmacion", confirmacion));
                
                
                // Utilizamos la clase Httpclient para conectar
                    HttpClient httpclient4 = new DefaultHttpClient();   
                    // Utilizamos la HttpPost para enviar lso datos
                    // A la url donde se encuentre nuestro archivo receptor
                    HttpPost httppost4 = new HttpPost("http://"+IP_Server+"/templates/dd_sosassy_19/droidlogin/pedirCita2.php"); 
                
                //Encapsulamos
                httppost4.setEntity(new UrlEncodedFormEntity(postValues));          
                //Lanzamos la petición
                HttpResponse respuesta4 = httpclient4.execute(httppost4);
                
                
                
                InputStream is4 = respuesta4.getEntity().getContent();
                BufferedInputStream bis = new BufferedInputStream(is4);
                ByteArrayBuffer baf = new ByteArrayBuffer(20);
                	 
                int current = 0;
                	             
                while((current = bis.read()) != -1){
                     baf.append((byte)current);
                } 
                	 
                 //Convert the Bytes read to a String. 
                  respuestaServidor = new String(baf.toByteArray());
                  Toast.makeText(getApplicationContext(),respuestaServidor,Toast.LENGTH_LONG).show();
                
               
                
            }catch (Exception e) {
            		            // TODO Auto-generated catch block
            	Log.e("Fail sent cita", e.toString());
            }
            	
            	
            }
        });
    
	}    
       
            
            private void spinner_fn() {
            	// TODO Auto-generated method stub
            	// ArrayAdapter<String> dataAdapter1 = new ArrayAdapter<String>(getApplicationContext(),
                //         android.R.layout.simple_spinner_item, peluquerias);
            	
            	ArrayAdapter<String> dataAdapter1 = new ArrayAdapter<String>(this,
                                 android.R.layout.simple_spinner_item, peluquerias);
            	 
            	 dataAdapter1.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
            	 spinnerPeluquerias.setAdapter(dataAdapter1); 
            	 
            	 spinnerPeluquerias.setOnItemSelectedListener(new OnItemSelectedListener() {
                  	
                  	public void onItemSelected(AdapterView<?> arg0, View arg1,int position, long arg3) {
                  	// TODO Auto-generated method stub                  	
                  		eleccionPeluqueriaGlobal = (String) spinnerPeluquerias.getItemAtPosition(position);
                  		//Toast.makeText(getApplicationContext(), eleccionPeluqueriaGlobal,Toast.LENGTH_LONG).show();            
                  	}

 					public void onNothingSelected(AdapterView<?> arg0) {
 						// TODO Auto-generated method stub
 						
 					}

 					
             	 	
                  });
            }
            
            private void spinner_fn2() {
            	// TODO Auto-generated method stub            	 
            	 
            	 ArrayAdapter<String> dataAdapter2 = new ArrayAdapter<String>(this,
                         android.R.layout.simple_spinner_item, tratamientos);
            	 
            	 dataAdapter2.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
            	 spinnerTratamientos.setAdapter(dataAdapter2);
            	           	 
            	 spinnerTratamientos.setOnItemSelectedListener(new OnItemSelectedListener() {
                 	
                 	public void onItemSelected(AdapterView<?> arg0, View arg1,int position, long arg3) {
                 	// TODO Auto-generated method stub
                 		eleccionTratamientoGlobal = (String) spinnerTratamientos.getItemAtPosition(position);
                 		//Toast.makeText(getApplicationContext(), eleccionTratamientoGlobal,Toast.LENGTH_LONG).show();        
                 		
                 	}

					public void onNothingSelected(AdapterView<?> arg0) {
						// TODO Auto-generated method stub
						
					}

					
            	 	
                 });
            }
            
            private void spinner_fn3() {
            	// TODO Auto-generated method stub            	 
            	 
            	 ArrayAdapter<String> dataAdapter3 = new ArrayAdapter<String>(this,
                         android.R.layout.simple_spinner_item, horarios);
            	 
            	 dataAdapter3.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
            	 spinnerHorarios.setAdapter(dataAdapter3);            	 
            	 spinnerHorarios.setOnItemSelectedListener(new OnItemSelectedListener() {                 	
                 	public void onItemSelected(AdapterView<?> arg0, View arg1,int position, long arg3) {
                 	// TODO Auto-generated method stub
                 		eleccionHorarioGlobal = (String) spinnerHorarios.getItemAtPosition(position);
                 		//Toast.makeText(getApplicationContext(), eleccionHorarioGlobal,Toast.LENGTH_LONG).show();                		
                 	}

					public void onNothingSelected(AdapterView<?> arg0) {
						// TODO Auto-generated method stub						
					}
         	 	
                 });
            }
            
            


}
