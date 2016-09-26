<?php

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

// Remove spaces from hairdresser name
$nameHairdresser= preg_replace( '/\s+/', ' ', $nameHairdresser );

// City to lowercase

$city = strtolower($city);


//echo $nameHairdresser. "<br />"; 
/* Query */
$result = mysql_query("SELECT * FROM peluquerias");

/* Make a table with the results */
echo "<table id=\"hor-zebra\">";
echo "<thead>";
echo "<tr>";
echo "<th scope=\"col\">Peluquería</th>";
echo "<th scope=\"col\">Dirección</th>";
echo "<th scope=\"col\">Ciudad</th>";
echo "<th scope=\"col\">Provincia</th>";
echo "<th scope=\"col\">Horario</th>";
echo "<th scope=\"col\">Correo</th>";
echo "<th scope=\"col\">Teléfono</th>";
echo "<th scope=\"col\">Mapa</th>";
echo "<th scope=\"col\">Opiniones</th>";
echo "</tr>";
echo "</thead>";

echo "<tbody>"; 
//echo "<tbody><tr><td><b>Peluquería</b></td><td><b>Dirección</b></td><td><b>Ciudad</b></td><td><b>Provincia</b></td><td><b>Horario</b></td><td><b>Correo</b></td><td><b>Teléfono</b></td><td><b>Mapa</b></td><td><b>Opiniones</b></td></tr>";

$counterLinesFail=0;
$counterTotalLines=0;
while($row=mysql_fetch_array($result)){ 
$hDresserName = $row['nombre']; 
$adressToShow = $row['direccion']; 
$cityToShow = $row['ciudad']; 
$provinceToShow = $row['provincia']; 
$timeTable = $row['horario']; 
$email = $row['correo']; 
$mobilePhone = $row['telefono']; 
$confirmacion = $row['confirmacion']; 


$checkHairdresser = levenshtein($nameHairdresser, $hDresserName);
$checkCity = levenshtein($city, $cityToShow);
$checkProvince = levenshtein($province, $provinceToShow);
$levenshteinLain = 8;

//echo $checkHairdresser. "<br />";
//echo $checkCity. "<br />";
//echo $checkProvince. "<br />";


if (($checkHairdresser<=$levenshteinLain) && ($checkCity<=3) && ($checkProvince==0)){
echo "<tr class=\"odd\">";

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

echo "<td>";
echo "<a href='".$row['map']."'>Ver mapa</a>";
echo "</td>";

echo "<td>";
echo "<a href='".$row['opiniones']."'>Ver opiniones</a>";
echo "</td>";

echo "</tr>";

}else{
$counterLinesFail++;
}
$counterTotalLines++;
} //while


echo "</tbody></table>"; 

if ($counterLinesFail==$counterTotalLines){
echo "No se encontraron peluquerias asociadas <br />";
}
}

function check(){
if ((!empty($_POST['hairdresserName'])) && (!empty($_POST['city']))){
showInfoHairdresser();
}else{
if (empty($_POST['hairdresserName'])){
echo "El nombre de la peluquería es dato obligatorio <br />";
}
if (empty($_POST['city'])){
echo "La ciudad es un dato obligatorio <br />";
}
}

}

if (isset($_POST['submit'])){

check();
}


?>
