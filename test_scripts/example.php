<?php  
	if ($_SERVER["REQUEST_METHOD"] == "POST")
	{
		$name=$_POST["username"];//receiving name field value in $name variable  
		$password=$_POST["password"];//receiving password field value in $password variable  
		
		echo "Welcome: $name, your password is: $password";  
	}
?>  