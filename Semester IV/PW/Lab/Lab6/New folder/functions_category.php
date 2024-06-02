<?php
include 'db.php';

function getCategories() {
    global $db;
    $stmt = $db->query("SELECT * FROM categories");
    return $stmt->fetchAll(PDO::FETCH_ASSOC);
}

// Add similar functions for insert, update, delete
?>
