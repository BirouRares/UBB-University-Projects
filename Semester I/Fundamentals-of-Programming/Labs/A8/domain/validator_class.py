from src.domain.exceptions_class import BookValidatorExceptions
from src.domain.exceptions_class import ClientValidatorExceptions
from src.domain.exceptions_class import DateException
import datetime

class BookValidator:
    @staticmethod
    def title_valid(t):
        return not t.isnumeric() and not isinstance(t, float) and not isinstance(t, list) and not isinstance(t, dict) and not isinstance(t, tuple) and not t.isspace() and isinstance(t, str)

    @staticmethod
    def author_valid(t):
        return not t.isnumeric() and not isinstance(t, float) and not isinstance(t, list) and not isinstance(t, dict) and not isinstance(t, tuple) and not t.isspace() and isinstance(t, str)
    def validate_book(self,b):
        err_list=[]
        if not self.title_valid(b.title):
            err_list.append("The title should be a string! ")
        if not self.author_valid(b.author):
            err_list.append("The author should be a string! ")
        if len(err_list)>0:
            raise BookValidatorExceptions(err_list)

class ClientValidator:
    @staticmethod
    def name_valid(t):
        return not t.isnumeric() and not isinstance(t, float) and not isinstance(t, list) and not isinstance(t, dict) and not isinstance(t, tuple) and not t.isspace() and isinstance(t, str)

    def validate_client(self,c):
        err_list=[]
        if not self.name_valid(c.name):
            err_list.append("The name should be a string! ")
        if len(err_list)>0:
            raise ClientValidatorExceptions(err_list)

class RentalValidator:
    @staticmethod
    def is_rental_date_valid(rental_date):
        day, month, year = rental_date.split('/')
        try:
            datetime.date(int(year.strip()), int(month.strip()), int(day.strip()))
        except ValueError:
            raise DateException("Invalid date!")
        rental_date=datetime.date(int(year.strip()), int(month.strip()), int(day.strip()))
        if rental_date > datetime.date.today():
            raise DateException("Rental date do not exist!")
    @staticmethod
    def is_return_date_valid(return_date, rental_date):
        day, month, year = return_date.split('/')
        try:
            datetime.date(int(year.strip()), int(month.strip()), int(day.strip()))
        except ValueError:
            raise DateException("Invalid date!")
        return_date=datetime.date(int(year.strip()), int(month.strip()), int(day.strip()))
        if rental_date > return_date:
            raise DateException("Return date cannot be before rental date!")