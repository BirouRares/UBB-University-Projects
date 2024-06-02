<?php
session_start();
include 'db.php';
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <title>Shopping Cart</title>
    <style>
        body 
        {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #f4f4f4;
        }

        h1 
        {
            text-align: center;
            margin-top: 20px;
        }

        table 
        {
            width: 80%;
            margin: 20px auto;
            border-collapse: collapse;
        }

        th, td 
        {
            border: 1px solid #ddd;
            padding: 8px;
            text-align: left;
        }

        th 
        {
            background-color: #f2f2f2;
        }

        tr:nth-child(even) 
        {
            background-color: #f2f2f2;
        }

        tr:hover 
        {
            background-color: #ddd;
        }

        .action 
        {
            text-align: center;
        }

        .action a 
        {
            text-decoration: none;
            color: #333;
            padding: 5px 10px;
            background-color: #f44336;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }

        .action a:hover 
        {
            background-color: #d32f2f;
        }

        .clear-cart 
        {
            display: block;
            width: fit-content;
            margin: 20px auto;
            text-align: center;
        }

        .clear-cart-btn {
            display: inline-block;
            padding: 10px 20px;
            background-color: #f44336;
            color: white;
            text-align: center;
            text-decoration: none;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            font-size: 16px;
            transition: background-color 0.3s;
        }

        .clear-cart-btn:hover {
            background-color: #d32f2f;
        }
    </style>
</head>
<body>
    <h1>Shopping Cart</h1>
    <table>
        <tr>
            <th>Name</th>
            <th>Description</th>
            <th>Price</th>
            <th class="action">Action</th>
        </tr>
        <?php
        // Fetch products from the cart
        if (!empty($_SESSION['cart'])) {
            foreach ($_SESSION['cart'] as $productId) {
                // Fetch product details from the database and display in a table row
                $stmt = $db->prepare("SELECT * FROM products WHERE id = :id");
                $stmt->bindParam(':id', $productId);
                $stmt->execute();
                $product = $stmt->fetch(PDO::FETCH_ASSOC);
                // Display product details
                echo "<tr>";
                echo "<td>{$product['name']}</td>";
                echo "<td>{$product['description']}</td>";
                echo "<td>{$product['price']}</td>";
                echo "<td class='action'><a href='remove_from_cart.php?product_id={$product['id']}' >Remove</a></td>"; // Remove button
                echo "</tr>";
            }
        } else {
            echo "<tr><td colspan='4'>Your cart is empty.</td></tr>";
        }
        ?>
    </table>
    <button onclick="window.location.href='clear_cart.php'" class="clear-cart-btn">Clear Cart</button>
</body>
</html>
