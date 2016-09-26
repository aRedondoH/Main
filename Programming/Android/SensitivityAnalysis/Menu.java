package cube.analysis;


import com.google.ads.*;
import java.util.List;
import com.google.ads.AdRequest;
import com.google.ads.AdSize;
import com.google.ads.AdView;
import java.lang.Object;

import com.google.ads.*;

import cube.analysis.R;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

public class Menu extends Activity{
	
	private Button buttonCalculate;
	private Button buttonChart;
	private EditText  Variable1;
	private EditText  Variable2;
	private EditText Utility1Variable1;
	private EditText Utility2Variable1;
	private EditText Utility1Variable2;
	private EditText Utility2Variable2;
	private EditText Probability1;
	private EditText Probability2;
	private EditText TotalResult1;
	private EditText TotalResult2;
	private TextView variableText1;
	private TextView variableText2;
	
	private LinearLayout r2;
		
		
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState); 
        setContentView(R.layout.menu);
        
        r2 = (LinearLayout) findViewById(R.id.linearLayout1);
        
        AdView ad = new AdView(this, AdSize.BANNER,"a14f6da417b92ac");
        r2.addView(ad);
        //ad.setVisibility(AdView.VISIBLE);
        ad.loadAd(new AdRequest());
        ad.loadAd(new AdRequest());
        
        buttonCalculate = (Button) findViewById(R.id.buttonCalculate);
        buttonChart = (Button) findViewById(R.id.buttonChart);
        Variable1 = (EditText) findViewById(R.id.editText1);
    	Variable2 = (EditText) findViewById(R.id.editText2);
    	Utility1Variable1 = (EditText) findViewById(R.id.editText5); 	
    	Utility2Variable1 = (EditText) findViewById(R.id.editText6);
    	Utility1Variable2 = (EditText) findViewById(R.id.editText7);
    	Utility2Variable2 = (EditText) findViewById(R.id.editText8);
    	Probability1 = (EditText) findViewById(R.id.editText3);
    	Probability2 = (EditText) findViewById(R.id.editText4);
    	TotalResult1 = (EditText) findViewById(R.id.editText9);
    	TotalResult2 = (EditText) findViewById(R.id.editText10);
    	
    	variableText1 = (TextView) findViewById(R.id.textView3);
    	variableText2 = (TextView) findViewById(R.id.textView4);
    	
         buttonCalculate.setOnClickListener(new View.OnClickListener() {           	
        
            public void onClick(View v) {
    			// Call function
            	Calculate();
    		
    		}           
    	});  
        
     
         
         
        buttonChart.setOnClickListener(new View.OnClickListener() {  
        	
        	
        	
        	
            public void onClick(View v) {
    			// Call function           	
            	Intent myIntent = new Intent(Menu.this,ChartView.class);
            	// send new variables
            	myIntent.putExtra("Utility1Variable1", Utility1Variable1.getText().toString());
            	myIntent.putExtra("Utility2Variable1", Utility2Variable1.getText().toString());
            	myIntent.putExtra("Utility1Variable2", Utility1Variable2.getText().toString());
            	myIntent.putExtra("Utility2Variable2", Utility2Variable2.getText().toString());
            	myIntent.putExtra("Variable1", Variable1.getText().toString());
            	myIntent.putExtra("Variable2", Variable2.getText().toString());
            	
            	startActivity(myIntent);   		
            	//finish();            
    			}
    		});       
	 }
	
	
	public void Calculate(){
			
			
			Toast.makeText(this, "Calculando", Toast.LENGTH_LONG).show();
			
			// Take the variables		
			String Uti1Var1 = "";
			String Uti2Var1 = "";
			String Uti1Var2 = "";
			String Uti2Var2 = "";
			String Pro1 = "";
			String Pro2 = "";
			
			variableText1.setText(Variable1.getText().toString());
			variableText2.setText(Variable2.getText().toString());
			
			// Take variables dates	
			 Uti1Var1 = Utility1Variable1.getText().toString();
			 Uti2Var1 = Utility2Variable1.getText().toString();
			 Uti1Var2 = Utility1Variable2.getText().toString();
			 Uti2Var2 = Utility2Variable2.getText().toString();
			 Pro1 = Probability1.getText().toString();
			 Pro2 = Probability2.getText().toString();
			 
			// Convert string to int 
		/*	 int U1Var1 = Integer.parseInt(Uti1Var1);			
			 int U2Var1 = Integer.parseInt(Uti2Var1);
			 int U1Var2 = Integer.parseInt(Uti1Var2);
			 int U2Var2 = Integer.parseInt(Uti2Var2);
			 int P1 = Integer.parseInt(Pro1);
			 int P2 = Integer.parseInt(Pro2);*/
			 
			 float U1Var1 = Float.parseFloat(Uti1Var1);
			 float U2Var1 = Float.parseFloat(Uti2Var1);
			 float U1Var2 = Float.parseFloat(Uti1Var2);
			 float U2Var2 = Float.parseFloat(Uti2Var2);
			 float P1 = Float.parseFloat(Pro1);
			 float P2 = Float.parseFloat(Pro2);
			 
			 // Calculate the Sensivility Analisys
		/*	 int result1 = (U1Var1*P1)+(U2Var1*P2);
			 int result2 = (U1Var2*P1)+(U2Var2*P2);
			 TotalResult1.setText(Integer.toString(result1));
			 TotalResult2.setText(Integer.toString(result2)); */
			 
			 float result1 = (U1Var1*P1)+(U2Var1*P2);
			 float result2 = (U1Var2*P1)+(U2Var2*P2);
			 TotalResult1.setText(Float.toString(result1));
			 TotalResult2.setText(Float.toString(result2));
			
	 }	


}
