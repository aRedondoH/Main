
<?php

/** * Database config variables */ 
define("DB_HOST", "db462711312.db.1and1.com"); 
define("DB_USER", "dbo462711312");
define("DB_PASSWORD", "arh217956");
define("DB_DATABASE", "db462711312");



function signUpWithBind(){
	


// Connecting to database 
$link = mysqli_connect(DB_HOST, DB_USER, DB_PASSWORD,DB_DATABASE);

/* verificar conexión */
if (!$link) {
    printf("Error de conexión: %s\n", mysqli_connect_error());
    exit();
}

/* Obtaining arguments from POST variable */


if (!$stmt = mysqli_prepare($link, "INSERT INTO peluquerias (id_pelu, nombre, direccion, ciudad, provincia, horario, correo, telefono, map) VALUES (?,?,?,?,?,?,?,?,?)")){
	echo 'Error: ' . $mysqli->error;
	echo "something is wronngssssssss";
	return false;
}else{
	mysqli_stmt_bind_param($stmt, "sssssssss",$id,$nameHairdresser,$adressToSafe,$cityToSafe,$provinceToSafe,$timetableToSafe,$emailToSafe,$phoneToSafe,$mapToShow);
	$id=null;
	$nameHairdresser= $_POST['hairdresserName'];
	$adressToSafe= $_POST['adress'];
	$cityToSafe= $_POST['city'];
	$provinceToSafe = $_POST['province'];
	$timetableToSafe = $_POST['timeTable'];
	$emailToSafe = $_POST['email'];
	$phoneToSafe = $_POST['phoneNumber'];
	$mapToShow = 'ent';
}




echo "$nameHairdresser";
echo "$adressToSafe";
echo "$cityToSafe";
echo "$provinceToSafe";
echo "$timetableToSafe";
echo "$emailToSafe";
echo "$phoneToSafe";
echo "$mapToShow";



//mysqli_stmt_bind_param($stmt, 'issssssss',$id,$_POST['hairdresserName'],$_POST['adress'],$_POST['city'],$_POST['province'],$_POST['timeTable'],$_POST['email'],$_POST['phoneNumber'],$map);






/* Execute */
mysqli_stmt_execute($stmt);
printf("Error: %s.\n", mysqli_stmt_error($stmt));

printf("%d Fila insertada.\n", $stmt->affected_rows);


/* If everything is ok show a message */
if($stmt){
echo "Su peluquería ha sido registrada correctamente";
mysqli_stmt_close($stmt);
mysqli_close($link);
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
//if(!$res[0]){
//die('Invalid Captcha');
//}else{ 
/* If the gaps are not empty*/
//if ( (!empty($_POST['hairdresserName'])) && (!empty($_POST['adress'])) && (!empty($_POST['city'])) && (!empty($_POST['province'])) && (!empty($_POST['timeTable'])) &&(!empty($_POST['email'])) && (!empty($_POST['phoneNumber'])) ){
//signUpWithBind();

//}else{
//echo "Es necesario rellenar todos los campos";
//}
} 




if (isset($_POST['submit'])){

//check();
signUpWithBind();
}

?>
