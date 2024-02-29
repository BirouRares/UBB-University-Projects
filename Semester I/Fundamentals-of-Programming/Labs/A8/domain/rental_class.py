import datetime
import random
class Rental:
    def __init__(self, rental_id: int, book_id: int, client_id: int, rented_date: datetime, returned_date= None):
        self._rental_id = rental_id
        self._book_id = book_id
        self._client_id = client_id
        self._rented_date = rented_date
        self._returned_date = returned_date

    @property
    def rental_id(self):
        return self._rental_id
    @rental_id.setter
    def rental_id(self, rental_id):
        self._rental_id=rental_id
    @property
    def book_id(self):
        return self._book_id
    @book_id.setter
    def book_id(self, book_id):
        self._book_id=book_id
    @property
    def client_id(self):
        return self._client_id
    @client_id.setter
    def client_id(self, client_id):
        self._client_id = client_id
    @property
    def rented_date(self):
        return self._rented_date
    @rented_date.setter
    def rented_date(self, rented_date):
        self._rented_date = rented_date

    @property
    def returned_date(self):
        return self._returned_date

    @returned_date.setter
    def returned_date(self, returned_date):
        self._returned_date = returned_date

    def __len__(self):
        if self._returned_date is not None:
            return (self._returned_date- self._rented_date).days+1
        else:
            t=datetime.date.today()
            return (t-self._rented_date).days+1
    def __str__(self):
        return  "Rental ID: " + str(self.rental_id)+", Book ID: "+str(self.book_id) + ", Client ID: " +str(self.client_id) + ", Rented date: " + str(self.rented_date) + ", Returned date: " +str(self.returned_date)

def generate_rentals():
    books_list=list(range(2,20))
    rentals_data={}
    rentals_data[1]=Rental(1,1,1,datetime.date(2018,10,10))
    for i in range(2,11):
        r_id=i
        c_id=random.randint(1,20)
        b_id=random.choice(books_list)
        books_list.remove(b_id)
        rented_date_month= random.randint(1,12)
        rented_date_year= random.randint(2018,2021)
        if rented_date_month==2:
            if rented_date_year%4==0:
                rented_date_day = random.randint(1, 29)
            else:
                rented_date_day = random.randint(1, 28)
        elif rented_date_month in [1,3,5,7,8,10,12]:
            rented_date_day = random.randint(1, 31)
        else:
            rented_date_day = random.randint(1, 30)
        rent_date= datetime.date(rented_date_year,rented_date_month,rented_date_day)
        generated_rental=Rental(r_id,b_id,c_id,rent_date)
        rentals_data[r_id]=generated_rental
    return rentals_data

class BooksRentals:
    def __init__(self, book, number_of_rentals):
        self._book = book
        self._number_of_rentals = number_of_rentals

    @property
    def book(self):
        return self._book

    @property
    def number_of_rentals(self):
        return self._number_of_rentals
    def __str__(self):
        return "Book: " + str(self.book.title) +" written by "+str(self.book.author) + " was rented " +str(self.number_of_rentals) + " times"

class ClientsRental:
    def __init__(self, client, number_of_days_of_rentals):
        self._client = client
        self._number_of_days_of_rentals = number_of_days_of_rentals

    @property
    def client(self):
        return self._client

    @property
    def number_of_days_of_rentals(self):
        return self._number_of_days_of_rentals
    def __str__(self):
        return "Client: " + str(self.client.name) + " with id: " + str(self.client.client_id) + " has " +str(self.number_of_days_of_rentals) + " days of book rentals"

class AuthorRentals:
    def __init__(self, author, number_of_rentals):
        self._author = author
        self._number_of_rentals = number_of_rentals

    @property
    def author(self):
        return self._author

    @property
    def number_of_rentals(self):
        return self._number_of_rentals

    def __str__(self):
        return "Books by " + str(self.author) + " were rented " + str(self.number_of_rentals) + " times"