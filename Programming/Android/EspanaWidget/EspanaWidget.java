

package earth.pakage;
import java.util.Random;


import android.R;
import android.util.Log;
import android.widget.RemoteViews;
import android.app.PendingIntent;
import android.appwidget.AppWidgetManager;
import android.appwidget.AppWidgetProvider;
import android.content.ComponentName;
import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;

public class EspanaWidget extends AppWidgetProvider{
	
	
	
	public void updateQuake (Context context, AppWidgetManager appWidgetManager,int[] appWidgetIds){
		
		
				ComponentName thisWidget = new ComponentName(context,
						EspanaWidget.class);
				int[] allWidgetIds = appWidgetManager.getAppWidgetIds(thisWidget);
				for (int widgetId : allWidgetIds) {
					// Create some random data
					int number = (new Random().nextInt(100));

					RemoteViews remoteViews = new RemoteViews(context.getPackageName(),	earth.pakage.R.layout.espana_widget);
					Log.w("WidgetExample", String.valueOf(number));
					// Set the text
					remoteViews.setTextViewText(earth.pakage.R.id.bandera, String.valueOf(number));

					// Register an onClickListener
					Intent intent = new Intent(context, EspanaWidget.class);

					intent.setAction(AppWidgetManager.ACTION_APPWIDGET_UPDATE);
					intent.putExtra(AppWidgetManager.EXTRA_APPWIDGET_IDS, appWidgetIds);

					PendingIntent pendingIntent = PendingIntent.getBroadcast(context,
							0, intent, PendingIntent.FLAG_UPDATE_CURRENT);
					remoteViews.setOnClickPendingIntent(earth.pakage.R.id.bandera, pendingIntent);
					appWidgetManager.updateAppWidget(widgetId, remoteViews);
				}
		
		
	}
	
	/*public void updateQuake(Context context){
		
		ComponentName thisWidget = new ComponentName(context,EspanaWidget.class);		
		AppWidgetManager appWidgetManager = 
				AppWidgetManager.getInstance(context);
		int[] appWidgetIds = appWidgetManager.getAppWidgetIds(thisWidget);
		updateQuake(context, appWidgetManager, appWidgetIds);
	}*/
	

}
