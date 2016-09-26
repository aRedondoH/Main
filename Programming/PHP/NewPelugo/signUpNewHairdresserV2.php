<?php

/** * Database config variables */ 
define("DB_HOST", "db462711312.db.1and1.com"); 
define("DB_USER", "dbo462711312");
define("DB_PASSWORD", "arh217956");
define("DB_DATABASE", "db462711312");



function signUpWithBind(){

// Connecting to database 
$mysqli = new mysqli(DB_HOST, DB_USER, DB_PASSWORD,DB_DATABASE);




/* Prepare statement */
if (!$stmt=$mysqli->prepare("INSERT INTO peluquerias (id_pelu, nombre, direccion, ciudad, provincia, horario, correo, telefono, map) VALUES (0,?,?,?,'u','u','u',8,'u')")){
echo 'Error: ' . $mysqli->error;
return false;
}

/* Bind parameters*/
if (!$stmt->bind_param('sss',$nameHairdresser,$adressToSafe, $cityToSafe)) {
echo "Binding parameters failed: (" . $stmt->errno . ") " . $stmt->error;
}

/* Obtaining arguments from POST variable */
$id=0;
$nameHairdresser= $_POST['hairdresserName'];
$adressToSafe= $_POST['adress'];
$cityToSafe= $_POST['city'];
$provinceToSafe = $_POST['province'];
$timetableToSafe = $_POST['timeTable'];
$emailToSafe = $_POST['email'];
$phoneToSafe = $_POST['phoneNumber'];
$map = 'nothingBytheMomment';

/* Execute */
if (!$stmt->execute()){
echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;
}


printf("%d Fila insertada.\n", $stmt->affected_rows);

/* If everything is ok show a message */
if($stmt){
echo "Su peluquería ha sido registrada correctamente";
$mysqli->close();
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
if ( (!empty($_POST['hairdresserName'])) && (!empty($_POST['adress'])) && (!empty($_POST['city'])) && (!empty($_POST['province'])) && (!empty($_POST['timeTable'])) &&(!empty($_POST['email'])) && (!empty($_POST['phoneNumber'])) ){
signUpWithBind();

}else{
echo "Es necesario rellenar todos los campos";
}
} 


}

if (isset($_POST['submit'])){

check();
}

?>
