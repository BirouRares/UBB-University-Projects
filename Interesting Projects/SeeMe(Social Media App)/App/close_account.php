<?php
include("includes/header.php");

if(isset($_POST['cancel'])) {
	header("Location: settings.php");
}

if(isset($_POST['close_account'])) {
	$close_query = mysqli_query($con, "UPDATE users SET user_closed='yes' WHERE username='$userLoggedIn'");
	session_destroy();
	header("Location: register.php");
}


?>

<div class="main_column column">

	<h4>Închidere cont</h4>

	Ești sigur că vrei să îți închizi contul?<br><br>
	Închiderea contului va duce la ștergerea postărilor tale.<br><br>
	Poți să îți redeschizi contul prin conectare.<br><br>

	<form action="close_account.php" method="POST">
		<input type="submit" name="close_account" id="close_account" value="Da! Închide-l!" class="danger settings_submit">
		<input type="submit" name="cancel" id="update_details" value="Nu!" class="info settings_submit">
	</form>

</div>