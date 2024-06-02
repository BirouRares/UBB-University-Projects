<?php
session_start();

// Check if product_id is provided and it's a valid integer
if (isset($_GET['product_id']) && filter_var($_GET['product_id'], FILTER_VALIDATE_INT)) {
    $productId = $_GET['product_id'];

    // Search for the product in the cart and remove it
    if (($key = array_search($productId, $_SESSION['cart'])) !== false) {
        unset($_SESSION['cart'][$key]);
        // Reset array keys to ensure continuous indexing
        $_SESSION['cart'] = array_values($_SESSION['cart']);
    }
}

// Redirect back to the cart page
header("Location: cart.php");
exit();
?>
