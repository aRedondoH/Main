<?php
echo "<b-->Fecha de hoy: "; 
echo date("d-m-Y H:i:s"); 
echo "<br />"; 
echo "<br />"; 


/** * Database config variables */ 
define("DB_HOST", "db462711312.db.1and1.com"); 
define("DB_USER", "dbo462711312");
define("DB_PASSWORD", "arh217956");
define("DB_DATABASE", "db462711312");


// Connecting to database 
	$con = mysql_connect(DB_HOST, DB_USER, DB_PASSWORD); 
// selecting database 
	mysql_select_db(DB_DATABASE);
	
function showInfoHairdresser(){

/* Obtaining arguments from POST variable */
$nameHairdresser= $_POST['hairdresserName'];
$city= $_POST['city'];
$province= $_POST['province'];

/* Query */
$result = mysql_query("SELECT * FROM peluquerias WHERE nombre='$nameHairdresser' AND ciudad='$city' AND provincia='$province' ");

/* Make a table with the results */
echo "<table>";
	echo "<tbody><tr><td><b>Peluquería</b></td><td><b>Dirección</b></td><td><b>Ciudad</b></td><td><b>Provincia</b></td><td><b>Horario</b></td><td><b>Correo</b></td><td><b>Teléfono</b></td></tr>"; 

while($row=mysql_fetch_array($result)){ 
	$hDresserName = $row['nombre']; 
	$adressToShow = $row['direccion']; 
	$cityToShow = $row['ciudad']; 
	$provinceToShow = $row['provincia']; 
	$timeTable = $row['horario']; 
	$email = $row['correo']; 
	$mobilePhone = $row['telefono']; 
	$confirmacion = $row['confirmacion']; 
	  
	
	echo "<tr>";
	
	echo "<td>";
	$hDresserName = $row['nombre']; 
	echo $row['nombre']; 	
	echo "</td>"; 
	 
	echo "<td>"; 
	echo $row['direccion']; 
	$adressToShow = $row['direccion'];	 
	echo "</td>"; 
	 
	echo "<td>";
	echo $row['ciudad']; 
	$cityToShow = $row['ciudad']; 
	echo"</td>"; 
	 
	echo "<td>" ;
	echo $row['provincia']; 
	$provinceToShow = $row['provincia']; 
	echo"</td>"; 
	
	echo "<td>";
	echo $row['horario']; 
	$timeTable = $row['horario']; 
	echo"</td>"; 
	
	echo "<td>";
	echo $row['correo'];	
	echo"</td>"; 
	
	echo "<td>";
	echo $row['telefono']; 	
	echo"</td>"; 
	 
	
	echo "</tr>";
	
	}
	echo "</tbody></table>";	
}

function check(){
		if (!empty($_POST['hairdresserName'])){
				showInfoHairdresser();
		}else{
				echo "Ha ocurrido un error";
		}

}

if (isset($_POST['submit'])){
	
	check();
}

	
?>
