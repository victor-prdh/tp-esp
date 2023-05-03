<?php

require 'db.php';

$data = $db->query('SELECT * FROM `esp` ORDER BY `esp`.`id` DESC LIMIT 1')->fetch();

header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: GET, POST');
header("Access-Control-Allow-Headers: X-Requested-With");

echo 'La température est de ' .$data['temperature'] . ' degré celsius' ?? 'Température indisponible';