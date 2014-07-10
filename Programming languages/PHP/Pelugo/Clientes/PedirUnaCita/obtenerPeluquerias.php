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

$fecha=$_POST['fecha'];

$peluquerias = mysql_query("SELECT nombre FROM peluquerias  ");

	  // si hubiese una peluquería seleccionada saldría la primera
	  //echo " {$_POST['peluqueria']}  ";
	  echo '<option value=' .$_POST['peluqueria']. '>' .$_POST['peluqueria']. '';
	   
	  while($gu=mysql_fetch_assoc($peluquerias)){ 
		  //echo " {$gu["nombre"]} "; 
		  echo '<option value="' .$gu['nombre']. '">' .$gu["nombre"]. '</option>'; 
	  } 
	  
	  
	  
?>
