package paquete.sevilla;

import android.app.Activity;
import android.graphics.Matrix;
import android.graphics.PointF;
import android.os.Bundle;
import android.util.FloatMath;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.ImageView;

public class zoomcercaniassevilla extends Activity implements OnTouchListener{
	
	// Estas matrices se utilizarán para mover y hacer zoom sobre la imagen
			Matrix matrix = new Matrix();
			Matrix savedMatrix = new Matrix();
			
			// Podemos estar en uno de estos 3 estados
			static final int NONE = 0;
			static final int DRAG = 1;
			static final int ZOOM = 2;
			int mode = NONE;
			// Recuerda algunos aspectos para el proceso de zoom
			PointF start = new PointF();
			PointF mid = new PointF();
			float oldDist = 1f;
			
			private static final String TAG = "Touch";
			private static final float MIN_ZOOM = 1.0f;
			private static final float MAX_ZOOM = 5.0f;
			
			//MapView mapZoom;
		    /** Called when the activity is first created. */
		    @Override
		    public void onCreate(Bundle savedInstanceState) {
		        super.onCreate(savedInstanceState);
		        setContentView(R.layout.cercaniassevilla);
		        ImageView view = (ImageView) findViewById(R.id.imagecercaniassevilla);		        
		        view.setOnTouchListener(this);
		    }
		    
			public boolean onTouch(View v, MotionEvent event) {
				ImageView view = (ImageView) v;
				
				// Vuelca evento táctil en el registro
				dumpEvent(event);
				
				// Controla eventos táctiles aquí...
				switch (event.getAction() & MotionEvent.ACTION_MASK){
				
				case MotionEvent.ACTION_DOWN:
					savedMatrix.set(matrix);
					start.set(event.getX(),event.getY());
					Log.d(TAG, "mode=DRAG");
					mode = DRAG;
					break;
					
				case MotionEvent.ACTION_UP:
					
				case MotionEvent.ACTION_POINTER_UP:
					mode = NONE;
					Log.d(TAG, "mode=NONE");
					break;
					
				case MotionEvent.ACTION_MOVE:
					if (mode == DRAG){
						matrix.set(savedMatrix);
						matrix.postTranslate(event.getX() - start.x, event.getY() - start.y);
					}
					
					else if (mode == ZOOM){
						float newDist = spacing(event);
						Log.d(TAG, "newDist=" + newDist);
						
						if (newDist > 10f){
							matrix.set(savedMatrix);
							float scale = newDist / oldDist;
							
							
							
					//		Matrix temp = new Matrix();
					//		temp=getValue(temp, Matrix.MSCALE_X);
				    //           temp.set(matrix);
				    //           temp.postScale(zoomScale, zoomScale, mid.x, mid.y);

							
							//if (scale<MAX_ZOOM && scale>MIN_ZOOM){
								matrix.postScale(scale, scale, event.getX() - start.x, event.getY() - start.y);
								Log.d(TAG,"escala" + scale);
								Log.d(TAG,"getx" + event.getX());
								Log.d(TAG,"gety" + event.getY());
								Log.d(TAG,"getSize" + event.getSize());
						//	}
							
						}
					}
					break;
					
				case MotionEvent.ACTION_POINTER_DOWN:
					oldDist = spacing(event);
					Log.d(TAG, "oldDist=" + oldDist);
					if (oldDist > 10f){
						savedMatrix.set(matrix);
						midPoint(mid,event);
						mode = ZOOM;
						Log.d(TAG, "mode=ZOOM");
					}
					break;
					
				}
				view.setImageMatrix(matrix);
				return true; // indica que el evento tuvo lugar
			}
			private void midPoint(PointF mid2, MotionEvent event) {
				float x = event.getX(0) - event.getX(1);
				float y = event.getY(0) - event.getY(1);
				mid2.set(x / 2,y / 2);
				
			}
			private float spacing(MotionEvent event) {
				float x = event.getX(0) - event.getX(1);
				float y = event.getY(0) - event.getY(1);
				return FloatMath.sqrt(x * x + y * y);
			}
			private void dumpEvent(MotionEvent event) {
				
				String names[] = {"DOWN", "UP", "MOVE", "CANCEL", "OUTSIDE", "POINTER_DOWN", "POINTER_UP", "7?","8?", "9?"};
				StringBuilder sb = new StringBuilder();
				int action = event.getAction();
				int actionCode = action & MotionEvent.ACTION_MASK;
				sb.append("event ACTION_").append(names[actionCode]);
				
				if (actionCode == MotionEvent.ACTION_POINTER_DOWN || actionCode == MotionEvent.ACTION_POINTER_UP){
					
					sb.append("(pid ").append(
							action >> MotionEvent.ACTION_POINTER_ID_SHIFT);
					sb.append(")" );
				}
				sb.append("[");
				for(int i = 0; i < event.getPointerCount();i++) {
					sb.append("#").append(i);
					sb.append("(pid ").append(event.getPointerId(i));
					sb.append(")=").append((int) event.getX(i));
					sb.append(",").append((int) event.getY(i));
					if (i + 1 < event.getPointerCount())
						sb.append(";");
					
				}
				sb.append("]");
				Log.d(TAG, sb.toString());
				// TODO Auto-generated method stub
				
			}

}
