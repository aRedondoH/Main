<?php

/**
 * Database config variables
 */
define("DB_HOST", "db462711312.db.1and1.com");
define("DB_USER", "dbo462711312");//cambiar por el nombre de usuario definido en la configuracion de la BD.
define("DB_PASSWORD", "arh217956");//Modificar por el password elegido
define("DB_DATABASE", "db462711312");//Nombre de la base de datos reemplazar si se utilizo otro diferente al mencionado en el tutorial.
  
// connecting to mysql
	$con = mysql_connect(DB_HOST, DB_USER, DB_PASSWORD);
// selecting database
	mysql_select_db(DB_DATABASE);

$pelu=$_POST['peluqueria'];
$fecha=$_POST['fecha'];

// Los delimitadores pueden ser barra, punto o guión
list($dia, $mes, $anio) = split('[/.-]', $fecha);

$hora = mysql_query("SELECT 8_30,9_,9_30,10_,10_30,11_,11_30,12_,12_30,13_,13_30,14_,14_30,15_,15_30,16_,16_30,17_,17_30,18_,18_30,19_,19_30,20_,20_30,21_,21_30,22_,22_30,23_ FROM horarios WHERE nombre='$pelu' ");
   	
        while($gg=mysql_fetch_assoc($hora)){
		   
		  if ($gg["8_30"]==1){           
              $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia'  AND mes = '$mes'  AND anio = '$anio'  AND hora = '9:30'   AND peluqueria = '$pelu'  "); // comprobamos si existe la cita
              $num_rows = mysql_num_rows($existeCita); //numero de filas retornadas
                  if ($num_rows >0) { 
					  // la cita existe con en esa hora y dia 
				  } else { 
					   // la cita no existe en esa hora y dia 
					   echo '<option value="8:30">8:30</option>'; 
				  }
		   }else{ 
				// no hacer nada 
		   } 
		   	
		  if ($gg["9_"]==1){           
              $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia'  AND mes = '$mes'  AND anio = '$anio'  AND hora = '9:30'   AND peluqueria = '$pelu'  "); // comprobamos si existe la cita
              $num_rows = mysql_num_rows($existeCita); //numero de filas retornadas
                  if ($num_rows >0) { 
					  // la cita existe con en esa hora y dia 
				  } else { 
					   // la cita no existe en esa hora y dia 
					   echo '<option value="9:00">9:00</option>'; 
				  }
		   }else{ 
				// no hacer nada 
		   }
         
          if ($gg["9_30"]==1){           
              $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia'  AND mes = '$mes'  AND anio = '$anio'  AND hora = '9:30'   AND peluqueria = '$pelu'  "); // comprobamos si existe la cita
              $num_rows = mysql_num_rows($existeCita); //numero de filas retornadas
                  if ($num_rows >0) { 
					  // la cita existe con en esa hora y dia 
				  } else { 
					   // la cita no existe en esa hora y dia echo '<option value="9:30">9:30</option>'; 
				  }
		   }else{ 
				// no hacer nada 
		   } 
					     
		  if ($gg["10_"]==1){ 
			  $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '10:00' AND peluqueria = '$pelu' "); 
			  // comprobamos si existe la cita 
			  $num_rows = mysql_num_rows($existeCita); 
			  //numero de filas retornadas 
			  if ($num_rows > 0) { 
				  // la cita existe con en esa hora y dia 
				  } else { 
				  // la cita no existe en esa hora y dia 
				  echo '<option value="10:00">10:00</option>'; 
				  } 
		  }else{ 
			  // no hacer nada 
		  } 
		  
		  if ($gg["10_30"]==1){ 
			  $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '10:30' AND peluqueria = '$pelu' "); 
			  // comprobamos si existe la cita 
			  $num_rows = mysql_num_rows($existeCita); 
			  //numero de filas retornadas 
			  if ($num_rows > 0) { 
				  // la cita existe con en esa hora y dia 
				  } else { 
					  // la cita no existe en esa hora y dia 
					  echo '<option value="10:30">10:30</option>'; 
				  } 
		  }else{ 
			  // no hacer nada
		  } 
		  
		  
		  if ($gg["11_"]==1){ 
			  $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '11:00' AND peluqueria = '$pelu' "); 
			  // comprobamos si existe la cita 
			  $num_rows = mysql_num_rows($existeCita); 
			  //numero de filas retornadas 
			  if ($num_rows > 0) { 
				  // la cita existe con en esa hora y dia 
			  } else { 
				  // la cita no existe en esa hora y dia 
				  echo '<option value="11:00">11:00</option>'; 
			  } 
		  }else{ // no hacer nada 
		  
		  } 
		
		
		  if ($gg["11_30"]==1){ 
			  $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '11:30' AND peluqueria = '$pelu' "); 
			  // comprobamos si existe la cita 
			  $num_rows = mysql_num_rows($existeCita); 
			  //numero de filas retornadas 
			  if ($num_rows > 0) { 
				  // la cita existe con en esa hora y dia 
			  } else { 
				  // la cita no existe en esa hora y dia 
				  echo '<option value="11:30">11:30</option>'; 
			  } 
		  }else{ 
			  // no hacer nada 
		  } 
		  
		  
		  if ($gg["12_"]==1){ 
			  $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '12:00' AND peluqueria = '$pelu' "); 
			  // comprobamos si existe la cita 
			  $num_rows = mysql_num_rows($existeCita); 
			  //numero de filas retornadas 
			  if ($num_rows > 0) { 
				  // la cita existe con en esa hora y dia 
			  } else { 
				  // la cita no existe en esa hora y dia 
				  echo '<option value="12:00">12:00</option>'; 
			  } 
		  }else{ 
			  // no hacer nada 
		  } 
		  
		  
		  if ($gg["12_30"]==1){ 
			  $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '12:30' AND peluqueria = '$pelu' "); 
			  // comprobamos si existe la cita 
			  $num_rows = mysql_num_rows($existeCita); 
			  //numero de filas retornadas 
			  if ($num_rows > 0) { 
				  // la cita existe con en esa hora y dia 
			  } else { 
				  // la cita no existe en esa hora y dia 
				  echo '<option value="12:30">12:30</option>'; 
			  } 
	      }else{ 
			  // no hacer nada 
		  } 
		  
		  
		  if ($gg["13_"]==1){ 
			  $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '13:00' AND peluqueria = '$pelu' "); 
			  // comprobamos si existe la cita 
			  $num_rows = mysql_num_rows($existeCita); 
			  //numero de filas retornadas 
			  if ($num_rows > 0) { 
				  // la cita existe con en esa hora y dia 
		      } else { 
				  // la cita no existe en esa hora y dia 
				  echo '<option value="13:00">13:00</option>'; 
			  } 
		 }else{ 
			 // no hacer nada 
	     } 
	     
	     
	     if ($gg["13_30"]==1){ 
			 $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '13:30' AND peluqueria = '$pelu' "); 
			// comprobamos si existe la cita 
			$num_rows = mysql_num_rows($existeCita); 
			//numero de filas retornadas 
			if ($num_rows > 0) { 
				// la cita existe con en esa hora y dia 
			} else { 
				// la cita no existe en esa hora y dia 
				echo '<option value="13:30">13:30</option>'; 
			} 
		}else{ 
			// no hacer nada 
		} 
		
		
		
		if ($gg["14_"]==1){ 
			$existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '14:00' AND peluqueria = '$pelu' "); 
			// comprobamos si existe la cita 
			$num_rows = mysql_num_rows($existeCita); 
			//numero de filas retornadas 
			if ($num_rows > 0) { 
				// la cita existe con en esa hora y dia 
			} else { 
				// la cita no existe en esa hora y dia 
				echo '<option value="14:00">14:00</option>'; 
			} 
		}else{ 
			// no hacer nada 
		} 
		
		
		
		if ($gg["14_30"]==1){ 
			$existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '14:30' AND peluqueria = '$pelu' "); 
			// comprobamos si existe la cita 
			$num_rows = mysql_num_rows($existeCita); 
			//numero de filas retornadas 
			if ($num_rows > 0) { 
				// la cita existe con en esa hora y dia 
			} else { 
				// la cita no existe en esa hora y dia 
			    echo '<option value="14:30">14:30</option>'; 
			} 
			
		}else{ 
			// no hacer nada 
		} 
		
		
		
		if ($gg["15_"]==1){ 
			$existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '15:00' AND peluqueria = '$pelu' "); 
			// comprobamos si existe la cita 
			$num_rows = mysql_num_rows($existeCita); 
			//numero de filas retornadas 
			if ($num_rows > 0) { 
				// la cita existe con en esa hora y dia 
			} else { 
				// la cita no existe en esa hora y dia 
			    echo '<option value="15:00">15:00</option>'; 
			} 
	   }else{ 
		   // no hacer nada 
	   } 
	   
	   
	   
	   if ($gg["15_30"]==1){ 
		   $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '15:30' AND peluqueria = '$pelu' "); 
		   // comprobamos si existe la cita 
		   $num_rows = mysql_num_rows($existeCita); 
		   //numero de filas retornadas 
		   if ($num_rows > 0) { 
			   // la cita existe con en esa hora y dia 
		   } else { 
			   // la cita no existe en esa hora y dia 
			   echo '<option value="15:30">15:30</option>'; 
		   } 
	  }else{ 
		  // no hacer nada 
	  } 
	  
	  
	  
	  if ($gg["16_"]==1){ 
		  $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '16:00' AND peluqueria = '$pelu' "); 
		  // comprobamos si existe la cita 
		  $num_rows = mysql_num_rows($existeCita); 
		  //numero de filas retornadas 
		  if ($num_rows > 0) { 
			  // la cita existe con en esa hora y dia 
		  } else { 
			  // la cita no existe en esa hora y dia 
	      echo '<option value="16:00">16:00</option>'; 
	      } 
	  }else{ 
		  // no hacer nada 
	  } 
	  
	  
	  if ($gg["16_30"]==1){ 
		  $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '16:30' AND peluqueria = '$pelu' "); 
		  // comprobamos si existe la cita 
		  $num_rows = mysql_num_rows($existeCita); 
		  //numero de filas retornadas 
		  if ($num_rows > 0) { 
			  // la cita existe con en esa hora y dia 
			  } else { 
				  // la cita no existe en esa hora y dia 
				  echo '<option value="16:30">16:30</option>'; 
			  } 
      }else{ 
		  // no hacer nada 
	  } 
	  
	  
	  
	  if ($gg["17_"]==1){ 
		  $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '17:00' AND peluqueria = '$pelu' "); 
		  // comprobamos si existe la cita 
		  $num_rows = mysql_num_rows($existeCita); 
		  //numero de filas retornadas 
		  if ($num_rows > 0) { 
			  // la cita existe con en esa hora y dia 
		  } else { 
			  // la cita no existe en esa hora y dia 
			  echo '<option value="17:00">17:00</option>'; 
	      } 
	  }else{ 
		  // no hacer nada 
	  }
	   
	   
	  
	  if ($gg["17_30"]==1){ 
		  $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '17:30' AND peluqueria = '$pelu' "); 
		  // comprobamos si existe la cita 
		  $num_rows = mysql_num_rows($existeCita); 
		  //numero de filas retornadas 
		  if ($num_rows > 0) { 
			  // la cita existe con en esa hora y dia 
		  } else { 
				  // la cita no existe en esa hora y dia 
				  echo '<option value="17:30">17:30</option>'; 
	      } 
	  }else{ 
		  // no hacer nada 
	  } 
	  
	  
	  
	  if ($gg["18_"]==1){ 
		  $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '18:00' AND peluqueria = '$pelu' "); 
		  // comprobamos si existe la cita 
		  $num_rows = mysql_num_rows($existeCita); 
		  //numero de filas retornadas 
		  if ($num_rows > 0) { 
			  // la cita existe con en esa hora y dia 
		  } else { 
			  // la cita no existe en esa hora y dia 
			  echo '<option value="18:00">18:00</option>'; 
		  } 
	  }else{ 
		  // no hacer nada 
	  } 
	  
	  
	  
	  
	  if ($gg["18_30"]==1){ 
		  $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '18:30' AND peluqueria = '$pelu' "); 
		  // comprobamos si existe la cita 
		  $num_rows = mysql_num_rows($existeCita); 
		  //numero de filas retornadas 
		  if ($num_rows > 0) { 
			  // la cita existe con en esa hora y dia 
			  } else { 
				  // la cita no existe en esa hora y dia 
				  echo '<option value="18:30">18:30</option>'; 
		      } 
	  }else{ 
		  // no hacer nada 
	  } 
	  
	  
	  
	  
	  if ($gg["19_"]==1){ 
		  $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '19:00' AND peluqueria = '$pelu' "); 
		  // comprobamos si existe la cita 
		  $num_rows = mysql_num_rows($existeCita); 
		  //numero de filas retornadas 
		  if ($num_rows > 0) { 
			  // la cita existe con en esa hora y dia 
		  } else { 
			  // la cita no existe en esa hora y dia 
			  echo '<option value="19:00">19:00</option>'; 
		  } 
	  }else{ 
		  // no hacer nada 
	  } 
	  
	  
	  
	  
	  if ($gg["19_30"]==1){ 
		  $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '19:30' AND peluqueria = '$pelu' "); 
		  // comprobamos si existe la cita 
		  $num_rows = mysql_num_rows($existeCita); 
		  //numero de filas retornadas 
		  if ($num_rows > 0) { 
			  // la cita existe con en esa hora y dia 
	      } else { 
			  // la cita no existe en esa hora y dia 
			  echo '<option value="19:30">19:30</option>'; 
		  } 
	  }else{ 
		  // no hacer nada 
	  } 
	  
	  
	  if ($gg["20_"]==1){ 
		  $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '20:00' AND peluqueria = '$pelu' "); 
		  // comprobamos si existe la cita 
		  $num_rows = mysql_num_rows($existeCita); 
		  //numero de filas retornadas 
		  if ($num_rows > 0) { 
			  // la cita existe con en esa hora y dia 
		  } else { 
			  // la cita no existe en esa hora y dia 
			  echo '<option value="20:00">20:00</option>'; 
	      } 
	  }else{ 
		  // no hacer nada 
	  } 
	  
	  
	  
	  
	  if ($gg["20_30"]==1){ 
		  $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '20:30' AND peluqueria = '$pelu' "); 
		  // comprobamos si existe la cita 
		  $num_rows = mysql_num_rows($existeCita); 
		  //numero de filas retornadas 
		  if ($num_rows > 0) { 
			  // la cita existe con en esa hora y dia 
		  } else { 
			  // la cita no existe en esa hora y dia 
			  echo '<option value="20:30">20:30</option>'; 
		  } 
	  }else{ 
		  // no hacer nada 
	  } 
	  
	  
	  
	  
	  if ($gg["21_"]==1){ 
		  $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '21:00' AND peluqueria = '$pelu' "); 
		  // comprobamos si existe la cita 
		  $num_rows = mysql_num_rows($existeCita); 
		  //numero de filas retornadas 
		  if ($num_rows > 0) { 
			  // la cita existe con en esa hora y dia 
			  } else { 
				  // la cita no existe en esa hora y dia 
				  echo '<option value="21:00">21:00</option>'; 
			  } 
     }else{ 
			  // no hacer nada 
     } 
     
     
     
     if ($gg["21_30"]==1){ 
		 $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '21:30' AND peluqueria = '$pelu' "); 
		 // comprobamos si existe la cita 
		 $num_rows = mysql_num_rows($existeCita); 
		 //numero de filas retornadas 
		 if ($num_rows > 0) { 
			 // la cita existe con en esa hora y dia 
		 } else { 
			 // la cita no existe en esa hora y dia 
			 echo '<option value="21:30">21:30</option>'; 
	     } 
	 }else{ 
		 // no hacer nada 
	 } 
	 
	 
	 
	 
	 if ($gg["22_"]==1){ 
		 $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '22:00' AND peluqueria = '$pelu' "); 
		 // comprobamos si existe la cita 
		 $num_rows = mysql_num_rows($existeCita); 
		 //numero de filas retornadas 
		 if ($num_rows > 0) { 
			 // la cita existe con en esa hora y dia 
		 } else { 
			 // la cita no existe en esa hora y dia 
			 echo '<option value="22:00">22:00</option>'; 
	     } 
	 }else{ 
		 // no hacer nada 
	 } 
	 
	 
	 
	 if ($gg["22_30"]==1){ 
		 $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '22:30' AND peluqueria = '$pelu' "); 
		 // comprobamos si existe la cita 
		 $num_rows = mysql_num_rows($existeCita); 
		 //numero de filas retornadas 
		 if ($num_rows > 0) { 
			 // la cita existe con en esa hora y dia 
			 } else { 
				 // la cita no existe en esa hora y dia 
				 echo '<option value="22:30">22:30</option>'; 
		     } 
	 }else{ 
		 // no hacer nada 
	 } 
	 
	 
	 
	 
	 if ($gg["23_"]==1){ 
		 $existeCita = mysql_query("SELECT dia, mes, anio, hora, peluqueria from citas WHERE dia = '$dia' AND mes = '$mes' AND anio = '$anio' AND hora = '23:00' AND peluqueria = '$pelu' "); 
		 // comprobamos si existe la cita 
		 $num_rows = mysql_num_rows($existeCita); 
		 //numero de filas retornadas 
		 if ($num_rows > 0) { 
			 // la cita existe con en esa hora y dia 
	     } else { 
			 // la cita no existe en esa hora y dia 
			 echo '<option value="23:00">23:00</option>'; 
		 } 
     }else{ 
		 // no hacer nada 
     } 
     
 } // end while 
 //echo '</select>'; 
 //echo $dia; 
 //echo '<br />'; 
 //echo $mes; 
 //echo '<br />'; 
 //echo $anio; 
 echo '<br />'; 
 //echo $pelu; 
 echo '<br />'; 

?>
