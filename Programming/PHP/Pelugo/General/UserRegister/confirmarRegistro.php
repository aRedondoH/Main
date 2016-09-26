<?php

/**
 * Database config variables
 */
define("DB_HOST", "db462711312.db.1and1.com");
define("DB_USER", "dbo462711312");//cambiar por el nombre de usuario definido en la configuracion de la BD.
define("DB_PASSWORD", "arh217956");//Modificar por el password elegido
define("DB_DATABASE", "db462711312");//Nombre de la base de datos reemplazar si se utilizo otro diferente al mencionado en el tutorial.

// Connecting to database
   
        // connecting to mysql
        $con = mysql_connect(DB_HOST, DB_USER, DB_PASSWORD);
        // selecting database
        mysql_select_db(DB_DATABASE);
$id=null;
$horarios=null;
$nombre=$_POST['nombre'];
$usuario=$_POST['usuario'];
$contraseña=$_POST['contraseña'];
$contraseñaEncriptada=md5($contraseña);
$correo=$_POST['correo'];



if (isset($_POST[checkbox])){

  $result2 = mysql_query("SELECT username from l3heb_users WHERE username='$usuario' ");
  $num_rows = mysql_num_rows($result2); //numero de filas retornadas

  if ($num_rows -->0) { 
	  echo("El usuario ya existe"); 
  }else{ 
	  $result = mysql_query ("INSERT INTO l3heb_users (id,name,username,email,password,block,sendEmail,registerDate,lastvisitDate,activation,params,lastResetTime,resetCount) VALUES('','$nombre','$usuario','$correo','$contraseñaEncriptada',0,0,'0000-00-00 00:00:00','0000-00-00 00:00:00','','{\"admin_style\":\"\",\"admin_language\":\"\",\"language\":\"es-ES\",\"editor\":\"\",\"helpsite\":\"\",\"timezone\":\"Europe\/Madrid\"}','0000-00-00 00:00:00',0)"); 
	  // check for successful store 
	  if ($result) { 
		  $to = "info@pelugo.es"; 
		  //Email del usuario 
	      $subject = "Registro de un nuevo cliente"; 
	      $message = "Estimado Administrador, \n le comunicamos que ha habido un nuevo registro con los siguientes datos \n nombre: " .$nombre." \n usuario: ".$usuario. "\n contraseña: " .$contraseña. "\n correo: " .$correo; 
	      $from = "info@pelugo.es"; 
	      $headers = "From:" .$from; 
	      mail($to,$subject,$message,$headers); 
	      echo("Se ha registrado correctamente. En breve nos pondremos en contacto con usted "); 
	  } else { 
		  echo("Ha ocurrido un error."); 
	  } 
   } 
} 
  
?>

