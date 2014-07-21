<?php

function sendContactEmail(){
	
	// Get variables
	$nameLastName= $_POST['nameAndLastName'];
	$emailToSafe= $_POST['email'];
	$subjectToSafe= $_POST['subject'];
	$messageToSafe= $_POST['message'];
	

	// Destination
		$to = "info@pelugo.es"; 
	// Email data 
		$subject = $nameLastName ." quiere contactar con PeluGo \n"; 
		$message = "Asunto: " .$subjectToSafe. "\n
				    Mensaje: " .$messageToSafe. "\n";
		$from = $_POST['email']; 
		$headers = "From:" .$from; 
	// Send email	
		mail($to,$subject,$message,$headers);
}


if (isset($_POST['submit'])){

		sendContactEmail();
		echo "Gracias por ponerse en contacto con PeluGo, en breve nos pondremos en contacto con usted";
	
}


?>
