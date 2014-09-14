<?php

/** * Database config variables */ 
define("DB_HOST", "db462711312.db.1and1.com"); 
define("DB_USER", "dbo462711312");
define("DB_PASSWORD", "arh217956");
define("DB_DATABASE", "db462711312");

function signUpWithoutBind(){
	
// Connecting to database 
        $con = mysql_connect(DB_HOST, DB_USER, DB_PASSWORD); 
// selecting database 
        mysql_select_db(DB_DATABASE);
        
        /* Obtaining arguments from POST variable */
        $id=null;
        $nameHairdresser= $_POST['hairdresserName'];
        $adressToSafe= $_POST['adress'];
        $cityToSafe= $_POST['city'];
        $provinceToSafe = $_POST['province'];
        $timetableToSafe = $_POST['timeTable'];
        $emailToSafe = $_POST['email'];
        $phoneToSafe = $_POST['phoneNumber'];
        $mapToShow = $_POST['map'];
        
        // if the map field is not empty
			if(!empty($_POST['map'])){
				// Create map file
				$filename = $nameHairdresser.'Map.php';
				$Content = $mapToShow;
				// Open
				$handle = fopen($_SERVER['DOCUMENT_ROOT']. '/php_pelugo/maps/' .$filename , 'x+');
				// Write
				fwrite($handle, $Content);
				// Close
				fclose($handle);
				$mapToShow='http://www.pelugo.es/php_pelugo/maps/' .$filename;
			}else{
				$mapToShow='http://www.pelugo.es/php_pelugo/maps/MadridMap.php';
			}   
		
        
        /* Query */
$result = mysql_query("INSERT INTO peluquerias (id_pelu, nombre, direccion, ciudad, provincia, horario, correo, telefono, map) VALUES ('$id', '$nameHairdresser', '$adressToSafe', '$cityToSafe', '$provinceToSafe', '$timetableToSafe', '$emailToSafe', '$phoneToSafe', '$mapToShow') ");
        if($result){
			
			
            echo "Su peluquería ha sido registrada correctamente";
        }else{
                        echo "Ha ocurrido un error durante el registro";
        }	
}

function signUpWithBind(){

	// Connecting to database 
	$mysqli = new mysqli(DB_HOST, DB_USER, DB_PASSWORD,DB_DATABASE);

	/* Obtaining arguments from POST variable */
	$id=null;
	$nameHairdresser= $_POST['hairdresserName'];
	$adressToSafe= $_POST['adress'];
	$cityToSafe= $_POST['city'];
	$provinceToSafe = $_POST['province'];
	$timetableToSafe = $_POST['timeTable'];
	$emailToSafe = $_POST['email'];
	$phoneToSafe = $_POST['phoneNumber'];
	$map = 'nothingBytheMomment';

	
/* Prepare statement */
if (!$stmt=$mysqli->prepare("INSERT INTO peluquerias (id_pelu, nombre, direccion, ciudad, provincia, horario, correo, telefono, map) VALUES (?,?,?,?,?,?,?,?,?)")){
	 echo 'Error: ' . $mysqli->error;
	 return false;
}

/* Bind parameters*/
if (!$stmt->bind_param("issssssss", $id,$nameHairdresser,$adressToSafe, $cityToSafe,$provinceToSafe, $timetableToSafe, $emailToSafe, $phoneToSafe,$map)) {
	echo "Binding parameters failed: (" . $stmt->errno . ") " . $stmt->error;
}

/* Execute */
if (!$stmt->execute()){
	echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;
}

/* If everything is ok show a message */
	if($stmt){
			echo "Su peluquería ha sido registrada correctamente";
	}else{
			echo "Ha ocurrido un error durante el registro";
	}
}

function check(){
	/* Enable captcha */
	JPluginHelper::importPlugin('captcha');
	$post = JRequest::get('post');   
	$dispatcher = JEventDispatcher::getInstance();
	$res = $dispatcher->trigger('onInit',$post['dynamic_recaptcha_1']);
	/* Check captcha */
	if(!$res[0]){
		die('Invalid Captcha');
	}else{	
		/* If the gaps are not empty*/
		if ( (!empty($_POST['hairdresserName'])) && (!empty($_POST['adress'])) && (!empty($_POST['city'])) && (!empty($_POST['province'])) && (!empty($_POST['timeTable']))  &&(!empty($_POST['email'])) && (!empty($_POST['phoneNumber']))  ){
				signUpWithoutBind();
				
		}else{
				echo "Es necesario rellenar todos los campos";
		}
	}	
	

}

if (isset($_POST['submit'])){
	
	check();
}

?>
