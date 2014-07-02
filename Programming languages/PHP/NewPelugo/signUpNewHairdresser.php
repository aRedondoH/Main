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

function signUp(){
	
	/* Obtaining arguments from POST variable */
	$id=null;
	$nameHairdresser= $_POST['hairdresserName'];
	$adressToSafe= $_POST['adress'];
	$cityToSafe= $_POST['city'];
	$provinceToSafe = $_POST['province'];
	$timetableToSafe = $_POST['timeTable'];
	$emailToSafe = $_POST['email'];
	$phoneToSafe = $_POST['phoneNumber'];
	
	/* Query */
$result = mysql_query("INSERT INTO peluquerias (id_pelu, nombre, direccion, ciudad, provincia, horario, correo, telefono) VALUES ('$id', '$nameHairdresser', '$adressToSafe', '$cityToSafe', '$provinceToSafe', '$timetableToSafe', '$emailToSafe', '$phoneToSafe') ");
	if($result){
			echo "Su peluquería ha sido registrada correctamente";
	}else{
			echo "Ha ocurrido un error durante el registro";
	}
}

function check(){
	JPluginHelper::importPlugin('captcha');
	$post = JRequest::get('post');   
	$dispatcher = JEventDispatcher::getInstance();
	$res = $dispatcher->trigger('onInit',$post['dynamic_recaptcha_1']);
	if(!$res[0]){
		die('Invalid Captcha');
	}else{	
	
		if ( (!empty($_POST['hairdresserName'])) && (!empty($_POST['adress'])) && (!empty($_POST['city'])) && (!empty($_POST['province'])) && (!empty($_POST['timeTable']))  &&(!empty($_POST['email'])) && (!empty($_POST['phoneNumber']))  ){
				signUp();
				
		}else{
				echo "Ha ocurrido un error";
		}
	}	
	

}

if (isset($_POST['submit'])){
	
	check();
}

?>
