<?php

require_once 'config.inc.php';

$time = $_REQUEST['time'];
$t = $_REQUEST['t'];
$h = $_REQUEST['h'];

//open database
$conn = mysql_connect($dbhost, $dbuser, $dbpass) or die('error connecting to MySQL');
mysql_select_db($dbname, $conn);

//insert data into MySQL database
$sql = "INSERT INTO $dbtable(time, t, h) VALUES('$time', '$t', '$h')";
$result = mysql_query($sql);

mysql_close($conn);

?>
