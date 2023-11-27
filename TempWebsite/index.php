<?php

	include("config.inc.php");

	$link=Connection();

	$result=mysql_query("SELECT * FROM `datalog` ORDER BY `time` DESC",$link);

?>

<html>
	<head>
		<title>Sensor Data</title>
	</head>

	<body>
	<h1>Temperature/Moisture sensor readings</h1>
		<table border="1" cellspacing="1" cellpadding="1">
		<tr>
			<td>&nbsp;Timestamp&nbsp in unixtime;</td>
			<td>&nbsp;Temperature 1&nbsp;</td>
			<td>&nbsp;Moisture 1&nbsp;</td>
		</tr>
	<?php

		if($result!==FALSE)
			{
			while($row = mysql_fetch_array($result))
				{
				printf("<tr><td> &nbsp;%s </td><td> &nbsp;%s&nbsp; </td><td> &nbsp;%s&nbsp; </td></tr>",
				$row["time"], $row["t"], $row["h"]);
				}
			mysql_free_result($result);
			mysql_close();
			}
	?>
		</table>
	</body>
</html>
