<?php  
require 'config/config.php';
require 'includes/form_handlers/register_handler.php';
require 'includes/form_handlers/login_handler.php';
?>


<html>
<head>
	<title>Bun venit pe SeeMe!</title>
	<link rel="stylesheet" type="text/css" href="assets/css/register_style.css">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
	<script src="assets/js/register.js"></script>
</head>
<body>

	<?php  

	if(isset($_POST['register_button'])) {
		echo '
		<script>

		$(document).ready(function() {
			$("#first").hide();
			$("#second").show();
		});

		</script>

		';
	}


	?>
    
    <img class="wave" src="assets/images/wave.png">

	<div class="wrapper">
        
        <div class="img">
			<img src="assets/images/logo%20seeme.png" style="height:450px; width:450px;">
		</div>

		<div class="login_box">

			<div class="login_header">
				<h1>SeeMe</h1>
				Conectează-te sau înscrie-te mai jos!
			</div>
			<br>
			<div id="first">

				<form action="register.php" method="POST">
					<input type="email" name="log_email" placeholder="Adresa de email" value="<?php 
					if(isset($_SESSION['log_email'])) {
						echo $_SESSION['log_email'];
					} 
					?>" required>
					<br>
					<input type="password" name="log_password" placeholder="Parolă">
					<br>
					<?php if(in_array("Email or password was incorrect<br>", $error_array)) echo  "Email sau parolă incorectă<br>"; ?>
					<input type="submit" name="login_button" value="Conectare">
					<br>
					<a href="#" id="signup" class="signup">Ai nevoie de un cont? Înregistrează-te aici!</a>

				</form>

			</div>

			<div id="second">

				<form action="register.php" method="POST">
					<input type="text" name="reg_fname" placeholder="Prenume" value="<?php 
					if(isset($_SESSION['reg_fname'])) {
						echo $_SESSION['reg_fname'];
					} 
					?>" required>
					<br>
					<?php if(in_array("Your first name must be between 2 and 25 characters<br>", $error_array)) echo "Prenumele trebuie să aibă între 2 și 25 de caractere!<br>"; ?>
					
					


					<input type="text" name="reg_lname" placeholder="Nume" value="<?php 
					if(isset($_SESSION['reg_lname'])) {
						echo $_SESSION['reg_lname'];
					} 
					?>" required>
					<br>
					<?php if(in_array("Your last name must be between 2 and 25 characters<br>", $error_array)) echo "Numele trebuie să aibă între 2 și 25 de caractere!<br>"; ?>

					<input type="email" name="reg_email" placeholder="Email" value="<?php 
					if(isset($_SESSION['reg_email'])) {
						echo $_SESSION['reg_email'];
					} 
					?>" required>
					<br>

					<input type="email" name="reg_email2" placeholder="Confirmare Email" value="<?php 
					if(isset($_SESSION['reg_email2'])) {
						echo $_SESSION['reg_email2'];
					} 
					?>" required>
					<br>
					<?php if(in_array("Email already in use<br>", $error_array)) echo "Email deja folosit<br>"; 
					else if(in_array("Invalid email format<br>", $error_array)) echo "Email în format invalid<br>";
					else if(in_array("Emails don't match<br>", $error_array)) echo "Adresele de Email nu coincid<br>"; ?>


					<input type="password" name="reg_password" placeholder="Parolă" required>
					<br>
					<input type="password" name="reg_password2" placeholder="Confirmare Parolă" required>
					<br>
					<?php if(in_array("Your passwords do not match<br>", $error_array)) echo "Parolele nu coincid<br>"; 
					else if(in_array("Your password can only contain english characters or numbers<br>", $error_array)) echo "Parola poate să conțină doar litere sau numere<br>";
					else if(in_array("Your password must be betwen 5 and 30 characters<br>", $error_array)) echo "Parola trebuie să aibă între 5 și 30 de caractere<br>"; ?>


					<input type="submit" name="register_button" value="Creare cont">
					<br>

					<?php if(in_array("<span style='color: #14C800;'>Totul este pregătit! Poți să te conectezi acum!</span><br>", $error_array)) echo "<span style='color: #14C800;'>Totul este pregătit! Poți să te conectezi acum!</span><br>"; ?>
					<a href="#" id="signin" class="signin">Ai deja un cont? Conectează-te aici!</a>
				</form>
			</div>

		</div>

	</div>


</body>
</html>