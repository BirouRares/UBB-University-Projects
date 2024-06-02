<?php
include 'functions_category.php';

$categories = getCategories();
foreach ($categories as $category) {
    echo "<li class='category' data-id='{$category['id']}'>{$category['name']}</li>";
}

?>
