<?php

/**
 * Database config variables
 */
define("DB_HOST", "db462711312.db.1and1.com");
define("DB_USER", "dbo462711312");//cambiar por el nombre de usuario definido en la configuracion de la BD.
define("DB_PASSWORD", "arh217956");//Modificar por el password elegido
define("DB_DATABASE", "db462711312");//Nombre de la base de datos reemplazar si se utilizo otro diferente al mencionado en el tutorial.

 
    // Connecting to database
   // public function connect() {
        $con = mysql_connect(DB_HOST, DB_USER, DB_PASSWORD);
        // selecting database
        mysql_select_db(DB_DATABASE);
        

 
 $checked = $_POST['confirm'];
 //foreach($_POST['confirm'] as $user){
 //$botonConfirmar = $_GET['checkbox'];
 //if ($botonConfirmar){	 
//if (isset($_POST[checkbox])){	 

$comprobarCheckbox = $_POST['checkbox'];
if ($comprobarCheckbox=="1234"){	
	
  for($i=0; $i < count($checked); $i++){
	  
  //IF($_POST['confirm'] == 'activado'){
       

	$result = mysql_query("UPDATE citas SET confirmacion='si' WHERE usuario='$checked[$i]' ");
       if ($result){
             echo "<b-->Confirmada la cita del cliente: " . $checked[$i] . "<br />"; 
             $result4 = mysql_query("SELECT * FROM citas WHERE usuario='$checked[$i]' "); 
             while($row=mysql_fetch_array($result4)){ 
				 $peluCorreo = $row['peluqueria']; 
				 $horaCorreo = $row['hora']; 
				 $diaCorreo = $row['dia']; 
				 $mesCorreo = $row['mes']; 
				 $anioCorreo = $row['anio']; 
				 $result5 = mysql_query("SELECT * FROM l3heb_users WHERE username='$checked[$i]' "); 
				 while($row2=mysql_fetch_array($result5)){ 
					 $correoDelCliente = $row2['email']; } 
					 // Enviamos un correo de confirmación al cliente 
					 //$to = "albert.eagle.uni@gmail.com"; 
					 //Email del usuario $to = $correoDelCliente; 
					 //Email del usuario $subject = "Confirmacion de su cita"; 
					 $message = "Estimado/a " . $checked[$i] . ",\n le comunicamos que su cita ha sido confirmada.\n \n Datos de la cita \n \n Peluquería: " .$peluCorreo. "\n Día: " .$diaCorreo. "\n Hora: " .$horaCorreo. "\n Mes: " .$mesCorreo. "\n Año: " .$anioCorreo. "\n \n Gracias por confiar en PeluGo"; 
					 $from = "info@pelugo.es"; 
					 $headers = "From:" . 
					 $from; mail($to,$subject,$message,$headers); 
					 echo "<b>Email de confirmarción enviado al cliente:</b> ". $checked[$i] . "<br />"; } 
					 
					 
					 // while 
					 } 
					 // if result 
					 } 
					 // for 
					 // $botonConfirmar = 0; 
					 //$checked = 0; 
					 } 
					 //if ?&gt; 
?>
