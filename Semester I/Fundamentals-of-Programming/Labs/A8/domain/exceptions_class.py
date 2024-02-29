class IdException(Exception):
    def __init__(self,err):
        self._err=err
    def __str__(self):
        return self._err

class RentalException(Exception):
    def __init__(self, error):
        self._error = error

    def __str__(self):
        return self._error


class DateException(Exception):
    def __init__(self,err):
        self._err=err
    def __str__(self):
        return self._err

class RepositoryException(Exception):
    def __init__(self,err):
        self._err=err
    def __str__(self):
        return self._err
class BookException(Exception):
    def __init__(self,err):
        self._err=err
    def __str__(self):
        return self._err

class ClientException(Exception):
    def __init__(self,err):
        self._err=err
    def __str__(self):
        return self._err

class UndoRedoException(Exception):
    def __init__(self,err):
        self._err=err
    def __str__(self):
        return self._err
class BookValidatorExceptions(BookException):
    def __init__(self, err_list):
        self._err_list=err_list
    def __str__(self):
        err_prt=''
        for i in self._err_list:
            err_prt=err_prt+i
            err_prt=err_prt+'\n'
        return err_prt

class ClientValidatorExceptions(ClientException):
    def __init__(self, err_list):
        self._err_list=err_list
    def __str__(self):
        err_prt=''
        for i in self._err_list:
            err_prt=err_prt+i
            err_prt=err_prt+'\n'
        return err_prt
