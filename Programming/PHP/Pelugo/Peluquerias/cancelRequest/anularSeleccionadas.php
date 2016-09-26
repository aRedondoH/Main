<?php
	
		/** * Database config variables */ 
		define("DB_HOST", "db462711312.db.1and1.com"); 
		define("DB_USER", "dbo462711312");
		
		//cambiar por el nombre de usuario definido en la configuracion de la BD. 
		define("DB_PASSWORD", "arh217956");
		
		//Modificar por el password elegido 
		define("DB_DATABASE", "db462711312");
		
		//Nombre de la base de datos reemplazar si se utilizo otro diferente al mencionado en el tutorial. 
		// Connecting to database 		
		$con = mysql_connect(DB_HOST, DB_USER, DB_PASSWORD); 
		
		// selecting database 
		mysql_select_db(DB_DATABASE); 
		$checked = $_GET['confirm']; 
		
			
			for($i=0; $i<count($checked); $i++){ 
					$result = mysql_query("UPDATE citas SET confirmacion='no' WHERE usuario='$checked[$i]' "); 
					if ($result){ 
						echo "Anulada la cita del cliente: " . $checked[$i] . "<br />"; 
					} 
			} 
						
						
						
?> 
