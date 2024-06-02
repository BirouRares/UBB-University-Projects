<?php
session_start();
unset($_SESSION['cart']); // Clear the cart session
header("Location: cart.php"); 
?>
