<?php  
	if ($_SERVER["REQUEST_METHOD"] == "DELETE")
	{
		$fname=$_DELETE["path_file"];//receiving name field value in $name variable  
		
		echo "$fname, is deleted. lol";
	}
?>  