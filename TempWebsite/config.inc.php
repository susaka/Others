<?php

$dbhost  = 'localhost';
$dbuser  = 'root';
$dbpass  = 'password';
$dbname  = 'Room1_dth';
$dbtable = 'datalog';


function Connection()
{
$server="localhost";
$user="root";
$pass="password";
$db="Room1_dth";

$connection = mysql_connect($server, $user, $pass);

	if(!$connection)
	{
	die('MySQL ERROR: '. mysql_error());
	}
mysql_select_db($db) or die( 'MySQL ERROR: '. mysql_error());

return $connection;
}
?>
