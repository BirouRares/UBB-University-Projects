<?php
    session_start();

    if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['product_id'])) {
        $productId = $_POST['product_id'];

        // Initialize cart session if not already set
        if (!isset($_SESSION['cart'])) {
            $_SESSION['cart'] = [];
        }
        $_SESSION['cart'][] = $productId;
        echo json_encode(['success' => true, 'message' => 'Product added to cart successfully']);
        /* Add product to the cart session if not already added
        if (!in_array($productId, $_SESSION['cart'])) {
            $_SESSION['cart'][] = $productId;
            echo json_encode(['success' => true, 'message' => 'Product added to cart successfully']);
        } else {
            echo json_encode(['success' => false, 'message' => 'Product is already in the cart']);
        }*/
    } 
    else 
    {
        echo json_encode(['success' => false, 'message' => 'Invalid request']);
    }
?>
