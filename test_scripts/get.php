<?php  
	if ($_SERVER["REQUEST_METHOD"] == "GET")
	{
		$name=$_GET["username"];//receiving name field value in $name variable  
		$password=$_GET["password"];//receiving password field value in $password variable  
		echo "Welcome: $name, your password is: $password";  
	}
?>  