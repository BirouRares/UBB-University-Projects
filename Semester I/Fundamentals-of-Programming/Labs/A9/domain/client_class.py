import random
class Client:
    def __init__(self, client_id: int, client_name: str):
        self._client_id=client_id
        self._client_name=client_name

    @property
    def client_id(self):
        return self._client_id
    @client_id.setter
    def client_id(self, client_id):
        self._client_id=client_id
    @property
    def name(self):
        return self._client_name
    @name.setter
    def name(self, client_name):
        self._client_name=client_name

    def __str__(self):
        return "Client id: " + str(self._client_id) + ", Name: " + self._client_name


CLIENTS = ["Rares", "Andrei", "Marian", "Marius", "Flavia", "Vlad", "Georgiana", "Andreea", "Paul"]
def generate_clients():
    clients_data = {}
    clients_data[1] = Client(1, "Anamaria")
    for i in range(2,21):
        client_id=i
        client_name=CLIENTS[random.randint(0,8)]
        clients_data[client_id]=Client(client_id, client_name)
    return clients_data