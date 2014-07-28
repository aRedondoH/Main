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



/* Some cheaking */
	$start=$_GET['start'];// To take care global variable if OFF
	if(strlen($start) > 0 and !is_numeric($start)){
		echo "Data Error";
		exit;
	}
	
/* page */
	$pageName = "index.php?option=com_content&view=article&id=28:show-info-by-city&catid=8:administration&Itemid=110&start=";
	

//function showInfoHairdresserByLocation(){
	
	
	
	
	/* Putting limits */
	//$start = 5 ; // FIX ME
	$eu = $start - 0;
	$limit = 8; // No of records to be shown per page.
	$thisWebPage = $eu + $limit;
	$back = $eu - $limit;
	$next = $eu + $limit;
	
		
	/* Obtaining arguments from POST variable */
	if (empty($_POST['city'])){
		$city= $_GET['city'];
	}else {
		$city=$_POST['city'];
	}
	if (empty($_POST['province'])){
		$province= $_GET['province'];
	}else{
		$province=$_POST['province'];
	}
	//$province='Madrid';
	
	
	/* Number of records exists in our table */
	$queryTotal = mysql_query("SELECT * FROM peluquerias ");
	
	$nume=mysql_num_rows($queryTotal);
	
	
	/* Query */
	$result = mysql_query("SELECT * FROM peluquerias WHERE ciudad='".$city."' AND  provincia='".$province."' limit $eu, $limit ");
	
	/* Print error query*/
	$result2=mysql_query($result);
	echo mysql_error();
	
	
	
	
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
	
	
	
	while($row=mysql_fetch_array($result)){
		$hDresserName = $row['nombre'];
		$adressToShow = $row['direccion'];
		$cityToShow = $row['ciudad'];
		$provinceToShow = $row['provincia'];
		$timeTable = $row['horario'];
		$email = $row['correo'];
		$mobilePhone = $row['telefono'];
		$confirmacion = $row['confirmacion'];
		
		
		//$checkHairdresser = levenshtein($nameHairdresser, $hDresserName);
		$checkCity = levenshtein($city, $cityToShow);
		$checkProvince = levenshtein($province, $provinceToShow);
		$levenshteinLain = 8;
		
		if (($checkCity<=3) && ($checkProvince<=2)){

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
	}
		
	} //while
	
	
	echo "</tbody></table>";
	
	/* Move back */
	echo "<table align = 'center' width='50%'><tr><td align='left' width='30%'>";
	if($back >=0) {
		$start=$back;
		//print "<a href='$pageName?start=$back'><font face='Verdana' size='2'>Anterior</font></a>";
		echo '<a href=" '.$pageName.$start.'&city='.$city.'&province='.$province.' ">Anterior</a> ';
	}
	
	/* Center links */
	//echo "</td><td align=center width='30%'>";
	$i=0;
	$l=1;
	for($i=0;$i < $nume;$i=$i+$limit){
		if($i <> $eu){
			$start=$i;
			//echo " <a href='$pageName?start=$i'><font face='Verdana' size='2'>$l</font></a> ";
			//echo '<a href=" '.$pageName.$start.' ">'.$l.'</a> ';
			echo '<a href=" '.$pageName.$start.'&city='.$city.'&province='.$province.' ">'.$l.'</a> ';
		}else { 
			echo "<font face='Verdana' size='4' color=green>$l</font>";
		} /// Current page is not displayed as link and given font color red
	$l=$l+1;
	}
	
	/* Move next */
	echo "</td><td align='right' width='30%'>";
	if($thisWebPage < $nume) {
		$start=$next;
		echo '<a href=" '.$pageName.$start.' ">Siguiente</a> ';
		//print "<a href='$pageName?start=$next'><font face='Verdana' size='2'>Siguiente</font></a>";
	}
	echo "</td></tr></table>";

	 
	
	//}
	
	//function check(){
	//if ((!empty($_POST['city']))){
		//showInfoHairdresserByLocation();
		
	//}
	//if (empty($_POST['city'])){
	//echo "La ciudad es un dato obligatorio <br />";
	//}
//}



//if (isset($_POST['submit'])){

	//check();
//}


?>
