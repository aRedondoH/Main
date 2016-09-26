<?php

echo "Fecha de hoy: ";
echo "<b-->"; 
echo date("d-m-Y H:i:s"); 
echo ""; 
echo "<br />"; 
echo "<h3>&nbsp;</h3><p>Elija las citas que desea anular:</p>"; 
echo "<br />"; 


/** * Database config variables */ 
define("DB_HOST", "db462711312.db.1and1.com"); 
define("DB_USER", "dbo462711312");

//cambiar por el nombre de usuario definido en la configuracion de la BD. 
define("DB_PASSWORD", "arh217956");

//Modificar por el password elegido 
define("DB_DATABASE", "db462711312");

//Nombre de la base de datos reemplazar si se utilizo otro diferente al mencionado en el tutorial. 
// obtenemos el usuario actual 
$usuario_sesion = mysql_query("SELECT username FROM l3heb_session "); 

while($e=mysql_fetch_assoc($usuario_sesion)){ $usuario=$e["username"]; } 

// Connecting to database 
	$con = mysql_connect(DB_HOST, DB_USER, DB_PASSWORD); 
// selecting database 
	mysql_select_db(DB_DATABASE); 

$result = mysql_query("SELECT * FROM citas WHERE confirmacion='si' "); 
echo ""; 
echo ""; 
$d = date("d"); 
$m = date("m"); 
$a = date("Y"); 

echo "<table>";
	echo "<tbody><tr><td><b>Cliente</b></td><td><b>Hora de la cita</b></td><td><b>Dia</b></td><td><b>Mes</b></td><td><b>Año</b></td><td><b>Tipo de cita</b></td><td><b>Peluquería</b></td><td><b>Confirmación</b></td><td><b>Confirmar?</b></td></tr>"; 

while($row=mysql_fetch_array($result)){ 
	$peluqueria = $row['peluqueria']; 
	$usuario = $row['usuario']; 
	$dia = $row['dia']; 
	$mes = $row['mes']; 
	$anio = $row['anio']; 
	$hora = $row['hora']; 
	$tipoDeCita = $row['tipoDeCita']; 
	$confirmacion = $row['confirmacion']; 
	  
	
	echo "<tr>";
	
	echo "<td>";
	$usuario=$row['usuario']; 
	echo $row['usuario']; 	
	echo "</td>"; 
	 
	echo "<td>"; 
	echo $row['hora']; 
	$hora=$row['hora'];	 
	echo "</td>"; 
	 
	echo "<td>";
	echo $row['dia']; 
	$dia=$row['dia']; 
	echo"</td>"; 
	 
	echo "<td>" ;
	echo $row['mes']; 
	$mes=$row['mes']; 
	echo"</td>"; 
	
	echo "<td>";
	echo $row['anio']; 
	$anio=$row['anio']; 
	echo"</td>"; 
	
	echo "<td>";
	echo $row['tipoDeCita']; 	
	echo"</td>"; 
	
	echo "<td>";
	echo $row['peluqueria']; 	
	echo"</td>"; 
	 
	echo "<td>"; 
	echo $row['confirmacion']; 
	echo " se encuentra confirmada"; 
	echo "</td>"; 
	
	echo "<td>";	
	echo '<input name="confirm[]" type="checkbox" value="' . $row['usuario'] . '" />'; 	
	echo "</td>";
	
	echo "</tr>";
	
	}
	echo "</tbody></table>";

?> 
