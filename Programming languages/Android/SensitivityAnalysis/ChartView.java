package cube.analysis;

import java.util.Arrays;
import com.google.ads.*;
import com.androidplot.series.XYSeries;
import com.androidplot.xy.LineAndPointFormatter;
import com.androidplot.xy.SimpleXYSeries;
import com.androidplot.xy.XYPlot;
import com.google.ads.AdRequest;
import com.google.ads.AdSize;
import com.google.ads.AdView;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.webkit.WebView;
import android.widget.LinearLayout;
import android.widget.Toast;

public class ChartView extends Activity{
	
	
	String Uti1Var1;
	String Uti2Var1;
	String Uti1Var2;
	String Uti2Var2;
	String VarTitle1;
	String VarTitle2;
	private XYPlot mySimpleXYPlot;
	private LinearLayout r1;
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.webview);
        
        r1= (LinearLayout) findViewById(R.id.LinearLayout2);
        
        AdView ad = new AdView(this, AdSize.BANNER,"a14f6da417b92ac");
        r1.addView(ad);
        //ad.setVisibility(AdView.VISIBLE);
        ad.loadAd(new AdRequest());
        ad.loadAd(new AdRequest());
        
        
      //  WebView wv = (WebView) findViewById(R.id.webView1);
        
        
        Intent startingIntent = getIntent();
        if (startingIntent != null) {
          Bundle b = startingIntent.getBundleExtra("android.intent.extra.INTENT");
          
          // Received Results variables
          this.Uti1Var1 = (String)getIntent().getSerializableExtra("Utility1Variable1");
          this.Uti2Var1 = (String)getIntent().getSerializableExtra("Utility2Variable1");
          this.Uti1Var2 = (String)getIntent().getSerializableExtra("Utility1Variable2");
          this.Uti2Var2 = (String)getIntent().getSerializableExtra("Utility2Variable2");
          this.VarTitle1 = (String)getIntent().getSerializableExtra("Variable1");	
          this.VarTitle2 = (String)getIntent().getSerializableExtra("Variable2");
  /*        Toast.makeText(this, this.Uti1Var1, Toast.LENGTH_LONG).show();
          Toast.makeText(this, this.Uti2Var1, Toast.LENGTH_LONG).show();
          Toast.makeText(this, this.Uti1Var2, Toast.LENGTH_LONG).show();
          Toast.makeText(this, this.Uti2Var2, Toast.LENGTH_LONG).show();*/
          
      }
        // Convert string to int 
		/* int U1Var1 = Integer.parseInt(Uti1Var1);
		 int U2Var1 = Integer.parseInt(Uti2Var1);
		 int U1Var2 = Integer.parseInt(Uti1Var2);
		 int U2Var2 = Integer.parseInt(Uti2Var2); */
        
         float U1Var1 = Float.parseFloat(Uti1Var1);
		 float U2Var1 = Float.parseFloat(Uti2Var1);
		 float U1Var2 = Float.parseFloat(Uti1Var2);
		 float U2Var2 = Float.parseFloat(Uti2Var2);
		 
        // Paint the Chart
        
        // Inicializamos el objeto XYPlot búscandolo desde el layout:
        mySimpleXYPlot = (XYPlot) findViewById(R.id.mySimpleXYPlot);
 
        // Creamos dos arrays de prueba. En el caso real debemos reemplazar

        // estos datos por los que realmente queremos mostrar

        Number[] series1Numbers = {U1Var1, U2Var1};
        Number[] series2Numbers = {U1Var2, U2Var2};
 
        // Añadimos Línea Número UNO:
        XYSeries series1 = new SimpleXYSeries(
                Arrays.asList(series1Numbers),  // Array de datos
                SimpleXYSeries.ArrayFormat.Y_VALS_ONLY, // Sólo valores verticales
                this.VarTitle1); // Nombre de la primera serie
 
        // Repetimos para la segunda serie
        XYSeries series2 = new SimpleXYSeries(Arrays.asList(series2Numbers
), SimpleXYSeries.ArrayFormat.Y_VALS_ONLY, this.VarTitle2);
 
        // Modificamos los colores de la primera serie
        LineAndPointFormatter series1Format = new LineAndPointFormatter(
                Color.rgb(0, 200, 0),                   // Color de la línea
                Color.rgb(0, 100, 0),                   // Color del punto
                Color.rgb(150, 190, 150));              // Relleno
 
        // Una vez definida la serie (datos y estilo), la añadimos al panel
        mySimpleXYPlot.addSeries(series1, series1Format);
 
        // Repetimos para la segunda serie
        mySimpleXYPlot.addSeries(series2, new LineAndPointFormatter
(Color.rgb(0, 0, 200), Color.rgb(0, 0, 100), Color.rgb(150, 150, 190)));
        
        
        
     //   wv.loadUrl("http://www.androiddom.com");
    } 

}
