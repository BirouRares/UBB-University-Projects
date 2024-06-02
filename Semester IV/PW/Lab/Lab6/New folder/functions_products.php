<?php
include 'db.php';

function getProducts($categoryId, $start, $perPage) {
    global $db;
    $sql = "SELECT * FROM products";
    if ($categoryId) {
        $sql .= " WHERE category_id = :category_id";
    }
    $sql .= " LIMIT :start, :perPage";
    $stmt = $db->prepare($sql);
    if ($categoryId) {
        $stmt->bindParam(':category_id', $categoryId);
    }
    $stmt->bindParam(':start', $start, PDO::PARAM_INT);
    $stmt->bindParam(':perPage', $perPage, PDO::PARAM_INT);
    $stmt->execute();
    return $stmt->fetchAll(PDO::FETCH_ASSOC);
}

function countTotalProducts($categoryId) {
    global $db;
    $sql = "SELECT COUNT(*) AS total FROM products";
    if ($categoryId) {
        $sql .= " WHERE category_id = :category_id";
    }
    $stmt = $db->prepare($sql);
    if ($categoryId) {
        $stmt->bindParam(':category_id', $categoryId);
    }
    $stmt->execute();
    $result = $stmt->fetch(PDO::FETCH_ASSOC);
    return $result['total'];
}

// Add similar functions for insert, update, delete
?>
