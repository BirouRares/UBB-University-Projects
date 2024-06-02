<?php
include 'functions_products.php';

$categoryId = $_GET['category_id'] ?? null;
$page = $_GET['page'] ?? 1;
$perPage = 4;

$start = ($page - 1) * $perPage;
$products = getProducts($categoryId, $start, $perPage);

echo "<table>";
echo "<tr><th>Name</th><th>Description</th><th>Price</th><th>Action</th></tr>";

foreach ($products as $product) {
    echo "<tr>";
    echo "<td>{$product['name']}</td>";
    echo "<td>{$product['description']}</td>";
    echo "<td>{$product['price']}</td>";
    echo "<td><button class='add-to-cart' data-product-id='{$product['id']}'>Add to Cart</button></td>"; // Add to Cart button
    echo "</tr>";
}

echo "</table>";

// Pagination
$totalProducts = countTotalProducts($categoryId); 
$totalPages = ceil($totalProducts / $perPage);

echo "<div class='pagination'>";
for ($i = 1; $i <= $totalPages; $i++) {
    echo "<a href='#' data-page='$i' data-category='$categoryId' class='" . ($page == $i ? 'active' : '') . "'>$i</a>";
}
echo "</div>";
?>
