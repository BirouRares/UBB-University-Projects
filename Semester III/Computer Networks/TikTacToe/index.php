<?php
// Connect to the server
$serverAddress = '172.30.114.150';
$serverPort = 8080;

$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    die("Unable to create socket\n");
}

$result = socket_connect($socket, $serverAddress, $serverPort);
if ($result === false) {
    die("Unable to connect to the server\n");
}

while (true) {
    $response = socket_read($socket, 1024);
    echo $response;

    if (strpos($response, "Your move") !== false) {
        $move = trim(fgets(STDIN));
        socket_write($socket, $move, strlen($move));
    } elseif (strpos($response, "Player") !== false or strpos($response, "It's") !== false) {
        break;
    }
}

socket_close($socket);
?>