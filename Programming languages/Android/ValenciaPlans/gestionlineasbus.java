package mi.paquete.valencia;

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
			String[] values = new String[] {"1. EST. D'AUTOBUSOS --> LA MALVA-ROSA",
											"2. LA MALVA-ROSA --> CAMPANAR",
											"14. FORN D'ALCEDO/PINEDO --> MARQUÉS DE SOTELO",
											"15. PINEDO --> MARQUÉS DE SOTELO",
											"19. LA MALVA-ROSA --> PL. DE L'AJUNTAMENT",
											"20. PLATGES --> AV. DEL CID",
											"23. PLATGES --> NATZARET/ CREU COBERTA",
											"31. LA MALVA-ROSA --> POETA QUEROL",
											"32. PASSEIG MARÍTIM --> MARQUÉS DE SOTELO",
											"N1. PL.DE L' AJUNTAMENT --> B. IBAÑEZ/LA MALVA-ROSA",
											"N9. PL. DE L'AJUNTAMENT --> MONT-OLIVET/CABANYAL"
			
			};
			
			//ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
			//		android.R.layout.simple_list_item_1, values);
			ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
					R.layout.lineasbus,android.R.id.empty, values);
			
			setListAdapter(adapter);
		}

		@Override
		public void onListItemClick(ListView l, View v, int position, long id) {
			String item = (String) getListAdapter().getItem(position);
			//Toast.makeText(this, item + " selected", Toast.LENGTH_LONG).show();
			
			
			if (position==0){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea1.class);
            	startActivity(myIntent);            	
			}
			if (position==1){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea2.class);
            	startActivity(myIntent);            	
			}
			if (position==2){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea14.class);
            	startActivity(myIntent);            	
			}
			if (position==3){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea15.class);
            	startActivity(myIntent);            	
			}
			if (position==4){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea19.class);
            	startActivity(myIntent);            	
			}
			if (position==5){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea20.class);
            	startActivity(myIntent);            	
			}
			if (position==6){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea23.class);
            	startActivity(myIntent);            	
			}
			if (position==7){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea31.class);
            	startActivity(myIntent);            	
			}
			if (position==8){				
				Intent myIntent = new Intent(gestionlineasbus.this,linea32.class);
            	startActivity(myIntent);            	
			}
			if (position==9){				
				Intent myIntent = new Intent(gestionlineasbus.this,linean1.class);
            	startActivity(myIntent);            	
			}
			if (position==10){				
				Intent myIntent = new Intent(gestionlineasbus.this,linean9.class);
            	startActivity(myIntent);            	
			}
			
						
		}
   // }

}
