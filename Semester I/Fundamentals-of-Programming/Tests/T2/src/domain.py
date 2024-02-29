class Player:
    def __init__(self, id, name, strength):
        self._id=id
        self._name=name
        self._strength=strength
    def __str__(self):
        return f"{self._id} {self._name} {self._strength}"
    @property
    def id(self):
        return self._id
    @property
    def name(self):
        return self._name
    @property
    def strength(self):
        return self._strength
    @strength.setter
    def strength(self, value):
        self._strength=value
    @id.setter
    def id(self, value):
        self._id=value
    @name.setter
    def name(self, value):
        self._name=value

