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
 

  $id_cita=null;
  $fecha=$_POST['fecha'];
  $hora_cita = $_POST['hora'];
  $dia=$_POST['dia'];
  $mes=$_POST['mes'];
  $anio=$_POST['anio'];
  $confirmacion='no';
  $peluqueria=$_POST['peluqueria'];
  $usuario=null;
  $tipoDeCita=$_POST['tipoDeCita'];

   
// Los delimitadores pueden ser barra, punto o guión
list($dia, $mes, $anio) = split('[/.-]', $fecha);


 if (!empty($_POST["fecha"])){
	if (isset($_POST[checkbox])){

		// obtenemos el usuario actual
		$usuario_sesion = mysql_query("SELECT username FROM l3heb_session ");
   	
        while($e=mysql_fetch_assoc($usuario_sesion)){	    
            $usuario=$e["username"];	    
	    }   
 
		echo $usuario;
		$result = mysql_query("INSERT INTO citas(id_cita,hora,dia,mes,anio,confirmacion,peluqueria,usuario,tipoDeCita) VALUES(null,'$hora_cita','$dia','$mes','$anio','$confirmacion','$peluqueria','$usuario','$tipoDeCita')");
        
        // check for successful store
        if ($result) {
           echo(" La cita fue agregada  correctamente.");
        } else {
           echo(" Ha ocurrido un error.");
        }

    }
  }  // if exterior


?>
