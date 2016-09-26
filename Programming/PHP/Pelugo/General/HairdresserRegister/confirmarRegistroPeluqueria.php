<?php

/**
 * Database config variables
 */
define("DB_HOST", "db462711312.db.1and1.com");
define("DB_USER", "dbo462711312");//cambiar por el nombre de usuario definido en la configuracion de la BD.
define("DB_PASSWORD", "arh217956");//Modificar por el password elegido
define("DB_DATABASE", "db462711312");//Nombre de la base de datos reemplazar si se utilizo otro diferente al mencionado en el tutorial.

// Connecting to database
   
        // connecting to mysql
        $con = mysql_connect(DB_HOST, DB_USER, DB_PASSWORD);
        // selecting database
        mysql_select_db(DB_DATABASE);
$id=null;
$horarios=null;
$nombre=$_POST['nombre'];
$usuario=$_POST['usuario'];
$correo=$_POST['correo'];
$telefono=$_POST['telefono'];
$dir=$_POST['direccion'];
$nClientes=$_POST['nClientes'];
 $_8_30=1;

if ($_POST['_8_30'] == '1234'){
  $_8_30=1;
}else{
 $_8_30=0;}

if ($_POST['_9_'] == '1234') {
    $_9_=1;
}else{
 $_9_=0;}

if ($_POST['_9_30'] == '1234') {
    $_9_30=1;
}else{
 $_9_30=0;}

if ($_POST['_10_']  == '1234') {
    $_10_=1;
}else{
 $_10_=0;}

if ($_POST['_10_30']  == '1234') {
    $_10_30=1;
}else{
 $_10_30=0;}

if ($_POST['_11_']  == '1234') {
    $_11_=1;
}else{
 $_11_=0;}

if ($_POST['_11_30']  == '1234') {
    $_11_30=1;
}else{
 $_11_30=0;}

if ($_POST['_12_']  == '1234') {
    $_12_=1;
}else{
 $_12_=0;}

if ($_POST['_12_30']  == '1234') {
    $_12_30=1;
}else{
 $_12_30=0;}

if ($_POST['_13_']  == '1234') {
    $_13_=1;
}else{
 $_13_=0;}

if ($_POST['_13_30']  == '1234') {
    $_13_30=1;
}else{
 $_13_30=0;}

if ($_POST['_14_'] == '1234') {
    $_14_=1;
}else{
 $_14_=0;}

if ($_POST['_14_30'] == '1234') {
    $_14_30=1;
}else{
 $_14_30=0;}

if ($_POST['_15_']  == '1234') {
    $_15_=1;
}else{
 $_15_=0;}

if ($_POST['_15_30'] == '1234') {
    $_15_30=1;
}else{
 $_15_30=0;}

if ($_POST[_16_]  == '1234') {
    $_16_=1;
}else{
 $_16_=0;}

if ($_POST['_16_30']  == '1234') {
    $_16_30=1;
}else{
 $_16_30=0;}

if ($_POST['_17_']  == '1234') {
    $_17_=1;
}else{
 $_17_=0;}
 
if ($_POST['_17_30']  == '1234') {
    $_17_30=1;
}else{
 $_17_30=0;}

if ($_POST['_18_']  == '1234') {
    $_18_=1;
}else{
 $_18_=0;}

if ($_POST['_18_30']  == '1234') {
    $_18_30=1;
}else{
 $_18_30=0;}

if ($_POST['_19_']  == '1234') {
    $_19_=1;
}else{
 $_19_=0;}

if ($_POST['_19_30']  == '1234') {
    $_19_30=1;
}else{
 $_19_30=0;}

if ($_POST['_20_']  == '1234') {
    $_20_=1;
}else{
 $_20_=0;}

if ($_POST['_20_30']  == '1234') {
    $_20_30=1;
}else{
 $_20_30=0;}

if ($_POST['_21_']  == '1234') {
    $_21_=1;
}else{
 $_21_=0;}

if ($_POST['_21_30']  == '1234') {
    $_21_30=1;
}else{
 $_21_30=0;}

if ($_POST['_22_']  == '1234') {
    $_22_=1;
}else{
 $_22_=0;}

if ($_POST['_22_30']  == '1234') {
    $_22_30=1;
}else{
 $_22_30=0;}

if ($_POST['_23_']  == '1234') {
    $_23_=1;
}else{
 $_23_=0;}



$id_pelu=' ';

//$id=mysql_query("SELECT id_pelu FROM peluquerias  WHERE nombre='$nombre' ");
 
 //while($e=mysql_fetch_assoc($id)){	    
 //           $id_pelu=$e["id_pelu"];	    
//	}






if (isset($_POST[checkbox])){

$result2=mysql_query ("INSERT INTO horarios (id_pelu,nombre,8_30,9_,9_30,10_,10_30,11_,11_30,12_,12_30,13_,13_30,14_,14_30,15_,15_30,16_,16_30,17_,17_30,18_,18_30,19_,19_30,20_,20_30,21_,21_30,22_,22_30,23_) VALUES('2','$nombre','$_8_30','$_9_','$_9_30','$_10_','$_10_30','$_11_','$_11_30','$_12_','$_12_30','$_13_','$_13_30','$_14_','$_14_30','$_15_','$_15_30','$_16_','$_16_30','$_17_','$_17_30','$_18_','$_18_30','$_19_','$_19_30','$_20_','$_20_30','$_21_','$_21_30','$_22_','$_22_30','$_23_')");



$result = mysql_query ("INSERT INTO peluquerias (id_pelu,nombre,direccion,horario,maxClientesPorHora,usuario,correo,telefono) VALUES('$id','$nombre','$dir','$horario','$nClientes','$usuario','$correo','$telefono')");




 // check for successful store
        if ($result) {

           echo("Se ha registrado correctamente. En breve nos pondremos en contacto con usted ");
           $to = "info@pelugo.es"; 
			//Email del usuario 
			$subject = "Registro de una nueva peluquería"; 
			$message = "Estimado Administrador, \n le comunicamos que ha habido un nuevo registro  de una peluqueria con los siguientes datos \n nombre: " .$nombre." \n usuario: ".$usuario. "\n correo: " .$correo. "\n telefono: " .$telefono. "\n dirección: " .$dir; 
			$from = "info@pelugo.es"; 
			$headers = "From:" .$from; 
			mail($to,$subject,$message,$headers);
           

        } else {

            echo("Ha ocurrido un error.");
        }

}

?>
