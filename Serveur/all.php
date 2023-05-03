<?php

require 'db.php';

$data = $db->query('SELECT * from esp ORDER BY id DESC LIMIT 10')->fetchAll();

header('Content-Type: application/json; charset=utf-8');
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: GET, POST');
header("Access-Control-Allow-Headers: X-Requested-With");
echo json_encode($data);