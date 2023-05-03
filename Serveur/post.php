<?php
$temperature = $_GET['temperature'];
require 'db.php';

$sth = $db->prepare('INSERT INTO `esp` (`id`, `date`, `temperature`) VALUES (NULL, current_timestamp(), :temperature);');
$sth->execute([':temperature' => $temperature]);
