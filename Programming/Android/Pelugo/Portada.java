package com.cliente.pelugo;



import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

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







import test.Droidlogin.library.Httppostaux;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.SystemClock;
import android.os.Vibrator;
import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class Portada extends Activity {
	
		
	EditText user;
	EditText pass;
	Button botonEntrar;
	TextView registrar;
	Httppostaux post;
    
    // Datos en servidor
    String IP_Server="www.pelugo.es";//IP DE NUESTRO PC
    String URL_connect="http://"+IP_Server+"/templates/dd_sosassy_19/droidlogin/acces.php";//ruta en donde estan nuestros archivos
  
    boolean result_back;
    private ProgressDialog pDialog;
    private String respuestaServidorPelu;
	

    @Override
    public void onCreate(Bundle savedInstanceState) {
    	
        super.onCreate(savedInstanceState);
        setContentView(R.layout.actividad_principalv2);
        post=new Httppostaux();
        
        user = (EditText) findViewById(R.id.editText1);
        pass = (EditText) findViewById(R.id.editText2);
        botonEntrar = (Button) findViewById(R.id.Enterbutton);
        registrar=(TextView) findViewById(R.id.link_to_register);
        
        botonEntrar.setOnClickListener(new View.OnClickListener() {        	
            public void onClick(View view) {
            	
            	//Extreamos datos de los EditText
                String usuario=user.getText().toString();
                String passw=pass.getText().toString();
               
                //verificamos si estan en blanco
                if( checklogindata( usuario , passw )==true){
                	//si pasamos esa validacion ejecutamos el asynctask pasando el usuario y clave como parametros               
                	new asynclogin().execute(usuario,passw);    
                }else{
                	//si detecto un error en la primera validacion vibrar y mostrar un Toast con un mensaje de error.
                	err_login();
                }
            }      
          });
        
        registrar.setOnClickListener(new View.OnClickListener(){
        	public void onClick(View view){
        		//Abre el navegador al formulario adduser.html
        		String url = "http://www.pelugo.es/index.php/component/users/?view=registration";
        		Intent i = new Intent(Intent.ACTION_VIEW);
        		i.setData(Uri.parse(url));
        		startActivity(i);        		
        	}        															});
        }    
    
    //vibra y muestra un Toast
    public void err_login(){
    	Vibrator vibrator =(Vibrator) getSystemService(Context.VIBRATOR_SERVICE);
	    vibrator.vibrate(200);
	    Toast toast1 = Toast.makeText(getApplicationContext(),"Error:Nombre de usuario o password incorrectos", Toast.LENGTH_SHORT);
 	    toast1.show();    	
    }
    
    
    /*Valida el estado del logueo solamente necesita como parametros el usuario y passw*/
    public boolean loginstatus(String username ,String password ) {
    	
    	int logstatus=-1;
    	
    	/*Creamos un ArrayList del tipo nombre valor para agregar los datos recibidos por los parametros anteriores
    	 * y enviarlo mediante POST a nuestro sistema para relizar la validacion*/ 
    		ArrayList<NameValuePair> postparameters2send= new ArrayList<NameValuePair>();
     		
		    postparameters2send.add(new BasicNameValuePair("usuario",username));
		    postparameters2send.add(new BasicNameValuePair("password",password));

		   //realizamos una peticion y como respuesta obtenes un array JSON
      		JSONArray jdata=post.getserverdata(postparameters2send, URL_connect);

      		/*como estamos trabajando de manera local el ida y vuelta sera casi inmediato
      		 * para darle un poco realismo decimos que el proceso se pare por unos segundos para poder
      		 * observar el progressdialog
      		 * la podemos eliminar si queremos
      		 */
		    SystemClock.sleep(950);
		    		
		    	//si lo que obtuvimos no es null
		    	if (jdata!=null && jdata.length() > 0){

		    		JSONObject json_data; //creamos un objeto JSON
					try {
						json_data = jdata.getJSONObject(0); //leemos el primer segmento en nuestro caso el unico
						 logstatus=json_data.getInt("logstatus");//accedemos al valor 
						 Log.e("loginstatus","logstatus= "+logstatus);//muestro por log que obtuvimos
					} catch (JSONException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}		            
		             
					//validamos el valor obtenido
		    		 if (logstatus==0){// [{"logstatus":"0"}] 
		    			 Log.e("loginstatus ", "invalido");
		    			 return false;
		    		 }
		    		 else{// [{"logstatus":"1"}]
		    			 Log.e("loginstatus ", "valido");
		    			 return true;
		    		 }
		    		 
			     }else{	//json obtenido invalido verificar parte WEB.
		    			 Log.e("JSON  ", "ERROR");
			    		return false;
			     }
    	
    }
    
    //validamos si no hay ningun campo en blanco
    public boolean checklogindata(String username ,String password ){    	
    	if 	(username.equals("") || password.equals("")){
    		Log.e("Login ui", "checklogindata user or pass error");
    		return false; 
    	}else{
    		return true;
    	}
    }    
    
    /*		CLASE ASYNCTASK
     * 
     * usaremos esta para poder mostrar el dialogo de progreso mientras enviamos y obtenemos los datos
     * podria hacerse lo mismo sin usar esto pero si el tiempo de respuesta es demasiado lo que podria ocurrir    
     * si la conexion es lenta o el servidor tarda en responder la aplicacion sera inestable.
     * ademas observariamos el mensaje de que la app no responde.     
     */
        
        class asynclogin extends AsyncTask< String, String, String > {
        	 
        	String user,pass;
        	String passEncripted;
            protected void onPreExecute() {
            	//para el progress dialog
                pDialog = new ProgressDialog(Portada.this);
                pDialog.setMessage("Autenticando....");
                pDialog.setIndeterminate(false);
                pDialog.setCancelable(false);
                pDialog.show();
            }
            
            // Encripta el password a MD5
            protected String md5(String s) {
                try {
                    // Create MD5 Hash
                    MessageDigest digest = java.security.MessageDigest.getInstance("MD5");
                    digest.update(s.getBytes());
                    byte messageDigest[] = digest.digest();

                    // Create Hex String
                    StringBuffer hexString = new StringBuffer();
                    for (int i=0; i<messageDigest.length; i++)
                        hexString.append(Integer.toHexString(0xFF & messageDigest[i]));
                    return hexString.toString();

                } catch (NoSuchAlgorithmException e) {
                    e.printStackTrace();
                }
                return "";
            }
            
            Random _rnd;
            
            // Covierte un password MD5 al formato de joomla     
            protected  String create(String passwd) {
                StringBuffer saltBuf = new StringBuffer();
                //synchronized (Joomla15PasswordHash.class) {
              
              if (_rnd==null) 
            	  _rnd=new SecureRandom();
              int i;
              for (i=0;i<32;i++) {
                 saltBuf.append(Integer.toString(_rnd.nextInt(36),36));
              }
                //}
                String salt = saltBuf.toString();
                return salt;         
             }
     
    		protected String doInBackground(String... params) {
    			
    			//obtenemos usr y pass
    			user=params[0];
    			pass=params[1];
    			
    			//enviamos y recibimos y analizamos los datos en segundo plano.
        		if (loginstatus(user,pass)==true){    		    		
        			return "ok"; //login valido
        			
        		}else if (user.equals("Alberto") && pass.equals("Camarma")){ //comprobamos si es el peluquero el que inicia sesion
        			
        			return "peluquero";
        		}else{
        			return "err";
        		}		
    		 }
           
    		/*Una vez terminado doInBackground segun lo que halla ocurrido 
    		pasamos a la sig. activity
    		o mostramos error*/
            protected void onPostExecute(String result) {

               pDialog.dismiss();//ocultamos progess dialog.
               Log.e("onPostExecute=",""+result);
               
               if (result.equals("ok")){

    				Intent i=new Intent(Portada.this, menuPrincipal.class);
    				i.putExtra("user",user);
    				startActivity(i); 
            	   
                }else
                	if (result.equals("peluquero")){
                		Intent i=new Intent(Portada.this, menuPeluquero.class);
        				i.putExtra("user",user);
        				startActivity(i); 
                	}else{
                		err_login();
                	}
                }
        }

}
