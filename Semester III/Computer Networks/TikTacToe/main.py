import socket

# Connect to the server
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(("172.30.114.150", 8080))

while True:
    response = client.recv(1024).decode()
    print(response)

    if "Your move" in response:
        move = input()
        client.send(move.encode())
    elif "Player" in response:
        break

client.close()