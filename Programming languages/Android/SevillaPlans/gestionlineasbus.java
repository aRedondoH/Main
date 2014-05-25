package paquete.sevilla;

import android.app.Activity;
import android.app.ListActivity;
import android.app.LoaderManager.LoaderCallbacks;
import android.content.Intent;
import android.database.Cursor;
import android.os.Bundle;
import android.provider.Contacts.People;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.SimpleCursorAdapter;
import android.widget.Toast;

public class gestionlineasbus extends ListActivity{	
		public void onCreate(Bundle icicle) {
			super.onCreate(icicle);
			String[] values = new String[] { "01: PGNO.NORTE - GLORIETA PLUS ULTRA",
					"02: BARQUETA - GLORIETA HELIOPOLIS",
					"05: PUERTA TRIANA - SANTA AURELIA",
					"06: SAN LAZARO - GLORIETA HELIOPOLIS",
					"10: PONCE DE LEÓN - SAN JERÓNIMO",
					"11: PONCE DE LEÓN - LOS PRINCIPES",
					"12: PONCE DE LEÓN - PINO MONTANO",					
					"13: PLAZA DUQUE - PINO MONTANO",
					"14: PLAZA DUQUE - POLIGONO NORTE",
					"15: PONCE DE LEÓN - SAN DIEGO",
					"16: PZA.JERON.CORDOBA - VALDEZORRAS",
					"20: PONCE DE LEÓN - PGNO. SAN PABLO",
					"21: PRADO - POLIGONO SAN PABLO",
					"22: PRADO - SEVILLA ESTE",
					"24: PONCE DE LEÓN - PALMETE",
					"25: PRADO - ROCHELAMBERT",
					"26: PRADO - CERRO DEL AGUILA",
					"27: PLAZA DEL DUQUE - SEVILLA ESTE",
					"28: PRADO - PARQUE ALCOSA",
					"29: PRADO - TORREBLANCA",
					"30: PRADO - LA PAZ",
					"31: PRADO - POLIGONO SUR",
					"32: PLAZA DUQUE - POLIGONO SUR",
					"34: PRADO - LOS BERMEJALES",
					"37: PRADO - BELLAVISTA",
					"38: PRADO SAN SEBASTIAN-UPO",
					"39: LOS ARCOS-HACIENDA SAN ANTONIO",
					"40: PLAZA MAGDALENA - TRIANA",
					"41: PLAZA MAGDALENA - TABLADA",
					"43: PLAZA MAGDALENA - EL TURRUÑUELO",
					"52: SAN BERNARDO - PALMETE",
					"B3: GRAN PLAZA - SANTA CLARA",
					"B4: GRAN PLAZA - TORREBLANCA",
					"B5: PLAZA MAGDALENA - SAN JERONIMO",
					"C1-C2: ISLA DE LA CARTUJA - PRADO",
					"C3-C4: BARQUETA - PRADO",
					"C5: PLAZA S. FRANCISCO - PLAZA DUQUE",
					"EA: PRADO - AEROPUERTO",
					"C6: SAN JERÓNIMO-VALDEZORRAS"};
			ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
					android.R.layout.simple_list_item_1, values);
			//ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
			//		R.layout.lineasbus,android.R.id.empty, values);
			
			setListAdapter(adapter);
		}

		@Override
		public void onListItemClick(ListView l, View v, int position, long id) {
			String item = (String) getListAdapter().getItem(position);
			Toast.makeText(this, item + " selected", Toast.LENGTH_LONG).show();
			
			
			if (position==0){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea1.class);
            	startActivity(myIntent);            	
			}
			if (position==1){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea2.class);
            	startActivity(myIntent);            	
			}
			if (position==2){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea5.class);
            	startActivity(myIntent);            	
			}
			if (position==3){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea6.class);
            	startActivity(myIntent);            	
			}
			if (position==4){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea10.class);
            	startActivity(myIntent);            	
			}
			if (position==5){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea11.class);
            	startActivity(myIntent);            	
			}
			if (position==6){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea12.class);
            	startActivity(myIntent);            	
			}
			if (position==7){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea13.class);
            	startActivity(myIntent);            	
			}
			if (position==8){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea14.class);
            	startActivity(myIntent);            	
			}
			if (position==9){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea15.class);
            	startActivity(myIntent);            	
			}
			if (position==10){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea16.class);
            	startActivity(myIntent);            	
			}
			if (position==11){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea20.class);
            	startActivity(myIntent);            	
			}
			if (position==12){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea21.class);
            	startActivity(myIntent);            	
			}
			if (position==13){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea22.class);
            	startActivity(myIntent);            	
			}
			if (position==14){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea24.class);
            	startActivity(myIntent);            	
			}
			if (position==15){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea25.class);
            	startActivity(myIntent);            	
			}
			if (position==16){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea26.class);
            	startActivity(myIntent);            	
			}
			if (position==17){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea27.class);
            	startActivity(myIntent);            	
			}
			if (position==18){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea28.class);
            	startActivity(myIntent);            	
			}
			if (position==19){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea29.class);
            	startActivity(myIntent);            	
			}
			if (position==20){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea30.class);
            	startActivity(myIntent);            	
			}
			if (position==21){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea31.class);
            	startActivity(myIntent);            	
			}
			if (position==22){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea32.class);
            	startActivity(myIntent);            	
			}
			
			if (position==23){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea34.class);
            	startActivity(myIntent);            	
			}
			if (position==24){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea37.class);
            	startActivity(myIntent);            	
			}
			if (position==25){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea38.class);
            	startActivity(myIntent);            	
			}
			if (position==26){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea39.class);
            	startActivity(myIntent);            	
			}
			if (position==27){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea40.class);
            	startActivity(myIntent);            	
			}
			if (position==28){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea41.class);
            	startActivity(myIntent);            	
			}
			if (position==29){				
				
				Intent myIntent = new Intent(gestionlineasbus.this,linea43.class);
            	startActivity(myIntent);            	
			}
			if (position==30){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea52.class);
            	startActivity(myIntent);            	
			}
			if (position==31){				
				Intent myIntent = new Intent(gestionlineasbus.this,lineab3.class);
            	startActivity(myIntent);            	
			}
			if (position==32){				
				Intent myIntent = new Intent(gestionlineasbus.this,lineab4.class);
            	startActivity(myIntent);            	
			}
			if (position==33){				
				Intent myIntent = new Intent(gestionlineasbus.this,lineab5.class);
            	startActivity(myIntent);            	
			}
			if (position==34){				
				Intent myIntent = new Intent(gestionlineasbus.this,lineac1c2.class);
            	startActivity(myIntent);            	
			}
			if (position==35){				
				Intent myIntent = new Intent(gestionlineasbus.this,lineac3c4.class);
            	startActivity(myIntent);            	
			}
			if (position==36){				
				Intent myIntent = new Intent(gestionlineasbus.this,lineac5.class);
            	startActivity(myIntent);            	
			}
			if (position==37){				
				Intent myIntent = new Intent(gestionlineasbus.this,lineaea.class);
            	startActivity(myIntent);            	
			}
			if (position==38){				
				Intent myIntent = new Intent(gestionlineasbus.this,lineac6.class);
            	startActivity(myIntent);            	
			}
			
		}
   // }

}
