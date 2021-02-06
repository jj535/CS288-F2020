<html>
<body>
<head>
<title>CS288 HW8 Mike Jeong</title>
</head>

<?php

$conn = mysqli_connect("localhost", "root", "password", "stock_market");

$tn = "yahoo_2020_12_03_20_41_02";
$result = $conn->query("SELECT * from $tn");

$table_attrs = "border = '1'";

$ncol = mysqli_num_fields($result);
echo "<h2>CS288 Homework. Used 100 most active stocks. PHP file was originally in /var/www/html/stock but moved to other directory for submission</h2>";
echo "<h3>Price in \$, Volume/Avg Volume in M, Market Cap in B</h3>";
echo "<h4>This is clickable, but not sortable. </h4>";
echo "<table $table_attrs>";

echo "<tr>";

while($field = $result->fetch_field()) {
	$finm = $field->name;

	echo("<th><a href=stock.php>$finm</a></th>");
}
echo "</tr>";

while ($row = $result->fetch_array()) {
	echo "<tr>";
	for ($col=0;$col<$ncol; $col++) {
		echo "<td>$row[$col]</td>";
	}
	echo "</tr>";
}

echo "</table>";


?>


</body>
</html>
