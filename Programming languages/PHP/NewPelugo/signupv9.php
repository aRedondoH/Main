<?php

/** * Database config variables */ 
define("DB_HOST", "db462711312.db.1and1.com"); 
define("DB_USER", "dbo462711312");
define("DB_PASSWORD", "arh217956");
define("DB_DATABASE", "db462711312");

function sendEmailToAdmin(){

// Get variables
$nameHairdresser= $_POST['hairdresserName'];
$adressToSafe= $_POST['adress'];
$cityToSafe= $_POST['city']; 
$provinceToSafe = $_POST['province'];
$timetableToSafe = $_POST['timeTable'];
$emailToSafe = $_POST['email'];
$phoneToSafe = $_POST['phoneNumber'];
$mapToShow = $_POST['map'];

// Destination
$to = "info@pelugo.es";;; 
// Email data 
$subject = "Registro de una nueva peluquería"; 
$message = "Estimado Administrador, \n 
le comunicamos que ha habido un nuevo registro de una peluqueria con los siguientes datos \n 
Nombre: " .$nameHairdresser." \n 
Dirección: ".$adressToSafe. "\n 
Ciudad: ".$cityToSafe. "\n
Provincia: ".$provinceToSafe. "\n
Correo: " .$emailToSafe. "\n 
Teléfono: " .$phoneToSafe; 
$from = "info@pelugo.es";;; 
$headers = "From:" .$from; 
// Send email 
mail($to,$subject,$message,$headers);
}

function sendEmailToClient(){

// Get variables
$nameHairdresser= $_POST['hairdresserName'];
$adressToSafe= $_POST['adress'];
$cityToSafe= $_POST['city']; 
$provinceToSafe = $_POST['province'];
$timetableToSafe = $_POST['timeTable'];
$emailToSafe = $_POST['email'];
$phoneToSafe = $_POST['phoneNumber'];
$mapToShow = $_POST['map'];

// Destination
$to = $_POST['email']; 
// Email data 
$subject = "Bienvenido a PeluGo ".$nameHairdresser; 
$message = "Gracias por confiar en PeluGo, ahora todo el mundo podrá encontrar tu peluquería de forma sencilla\n 
Los datos de su peluquería son los siguientes\n 
Nombre: " .$nameHairdresser." \n 
Dirección: ".$adressToSafe. "\n 
Ciudad: ".$cityToSafe. "\n
Provincia: ".$provinceToSafe. "\n
Correo: " .$emailToSafe. "\n 
Teléfono: " .$phoneToSafe. "\n 
si necesita modificar sus datos, no dude en ponerse en contacto con nosotros a través de info@pelugo.es";;; 
$from = "info@pelugo.es";;; 
$headers = "From:" .$from; 
// Send email 
mail($to,$subject,$message,$headers);

}

function signUpWithBind(){

// Connecting to database 
$mysqli = new mysqli(DB_HOST, DB_USER, DB_PASSWORD,DB_DATABASE);


/* Prepare statement */
if (!$stmt=$mysqli->prepare("INSERT INTO peluquerias (id_pelu, nombre, direccion, ciudad, provincia, horario, correo, telefono, map, opiniones) VALUES (0,?,?,?,?,?,?,?,?,?)")){
echo 'Error: ' . $mysqli->error;
return false;
}

/* Bind parameters*/
if (!$stmt->bind_param('sssssssss',$nameHairdresser,$adressToSafe, $cityToSafe, $provinceToSafe, $timetableToSafe, $emailToSafe, $phoneToSafe, $mapToShow, $opinionesToShow)) {
echo "Binding parameters failed: (" . $stmt->errno . ") " . $stmt->error;
}

/* Cleaning variables */
$nameHairdresser= 'Hamar';
$adressToSafe= 'Hamar';
$cityToSafe= 'Hamar';
$provinceToSafe = 'Hamar';
$timetableToSafe = 'Hamar';
$emailToSafe = 'Hamar';
$phoneToSafe = 'Hamar';
$map = 'nothingBytheMomment';
$opinionesToShow= 'empty';

/* Remove accents */
$unwanted_array = array(    'Š'=>'S', 'š'=>'s', 'Ž'=>'Z', 'ž'=>'z', 'À'=>'A', 'Á'=>'A', 'Â'=>'A', 'Ã'=>'A', 'Ä'=>'A', 'Å'=>'A', 'Æ'=>'A', 'Ç'=>'C', 'È'=>'E', 'É'=>'E',
                            'Ê'=>'E', 'Ë'=>'E', 'Ì'=>'I', 'Í'=>'I', 'Î'=>'I', 'Ï'=>'I', 'Ñ'=>'N', 'Ò'=>'O', 'Ó'=>'O', 'Ô'=>'O', 'Õ'=>'O', 'Ö'=>'O', 'Ø'=>'O', 'Ù'=>'U',
                            'Ú'=>'U', 'Û'=>'U', 'Ü'=>'U', 'Ý'=>'Y', 'Þ'=>'B', 'ß'=>'Ss', 'à'=>'a', 'á'=>'a', 'â'=>'a', 'ã'=>'a', 'ä'=>'a', 'å'=>'a', 'æ'=>'a', 'ç'=>'c',
                            'è'=>'e', 'é'=>'e', 'ê'=>'e', 'ë'=>'e', 'ì'=>'i', 'í'=>'i', 'î'=>'i', 'ï'=>'i', 'ð'=>'o', 'ñ'=>'n', 'ò'=>'o', 'ó'=>'o', 'ô'=>'o', 'õ'=>'o',
                            'ö'=>'o', 'ø'=>'o', 'ù'=>'u', 'ú'=>'u', 'û'=>'u', 'ý'=>'y', 'ý'=>'y', 'þ'=>'b', 'ÿ'=>'y' );
$str = strtr( $str, $unwanted_array );

/* Obtaining arguments from POST variable */
$id=0;
if (!empty($_POST['hairdresserName'])){
$nameHairdresser= $_POST['hairdresserName'];
$nameHairdresser = strtr( $nameHairdresser, $unwanted_array );
}
if (!empty($_POST['adress'])){
$adressToSafe= $_POST['adress'];
$adressToSafe = strtr( $adressToSafe, $unwanted_array );
}
if (!empty($_POST['city'])){ 
$cityToSafe= $_POST['city'];
$cityToSafe = strtr( $cityToSafe, $unwanted_array );
}
if (!empty($_POST['province'])){ 
$provinceToSafe = $_POST['province'];
$provinceToSafe = strtr( $provinceToSafe, $unwanted_array );
}
if (!empty($_POST['timeTable'])){
$timetableToSafe = $_POST['timeTable'];
}
if (!empty($_POST['email'])){
$emailToSafe = $_POST['email'];
}
if (!empty($_POST['phoneNumber'])){
$phoneToSafe = $_POST['phoneNumber'];
}
if (!empty($_POST['map'])){
$mapToShow = $_POST['map'];
}

// if the map field is not empty
if(!empty($_POST['map'])){
// Create map file

$nameHairdresser= preg_replace( '/\s+/', ' ', $nameHairdresser );
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
$mapToShow='http://www.pelugo.es/php_pelugo/maps/defaultMap.php';
}

$opinionesToShow='http://www.pelugo.es/php_pelugo/voting/votingDefault.php';


/* Execute */
if (!$stmt->execute()){
echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;
}


/* If everything is ok show a message */
if($stmt){
echo "Su peluquería ha sido registrada correctamente, en breve recibirá un email de confirmación";
sendEmailToAdmin();
sendEmailToClient();
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
echo "Es necesario rellenar los campos requeridos";
}
}


}

if (isset($_POST['submit'])){

check();

}

?>
