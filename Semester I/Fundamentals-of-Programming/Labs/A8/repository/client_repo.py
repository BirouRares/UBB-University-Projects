from src.domain.client_class import generate_clients

class ClientRepo:
    def __init__(self):
        self._clients_data=generate_clients()
    def __setitem__(self, key, value):
        self._clients_data[key]=value
    def __delitem__(self, key):
        del self._clients_data[key]
    def __len__(self):
        return len(self._clients_data)
    def clients_data_list(self):
        return list(self._clients_data.values())
    def add_client(self, client):
        self._clients_data[int(client.client_id)]=client
    def remove_client(self, client_id):
        del self._clients_data[int(client_id)]
    def update_client(self, client):
        self._clients_data[int(client.client_id)]=client
