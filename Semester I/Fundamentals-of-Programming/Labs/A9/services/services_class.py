from src.repository.book_repo import BookRepo
from src.repository.client_repo import ClientRepo
from src.repository.rental_repo import RentalRepo
from src.domain.rental_class import Rental
from src.domain.rental_class import BooksRentals
from src.domain.rental_class import AuthorRentals
from src.domain.rental_class import ClientsRental
from src.domain.book_class import Book
from src.domain.client_class import Client
from src.domain.validator_class import BookValidator
from src.domain.validator_class import ClientValidator
from src.domain.validator_class import RentalValidator
from src.domain.exceptions_class import RepositoryException
from src.domain.exceptions_class import IdException
from src.domain.exceptions_class import UndoRedoException
from src.domain.exceptions_class import RentalException
import datetime
import re

class UndoRedoObj:
    def __init__(self, undo_function, redo_function):
        self._undo_function = undo_function
        self._redo_function = redo_function
    def undo_function(self):
        self._undo_function()

    def redo_function(self):
        self._redo_function()

class UndoRedoServ:
    def __init__(self, book_repository, client_repository, rental_repository):
        self._book_repository = book_repository
        self._client_repository = client_repository
        self._rental_repository = rental_repository
        self._undo_stack = []
        self._undo_pointer = 0

    @property
    def undo_stack(self):
        return self._undo_stack
    def correct_stack(self):
        while len(self._undo_stack) != self._undo_pointer:
            self._undo_stack.pop()
    def add_undo_redo_operations(self, operations_object):
        self.correct_stack()
        self._undo_stack.append(operations_object)
        self._undo_pointer += 1
    def undo(self):
        if self._undo_pointer == 0:
            raise UndoRedoException("There are no operations to undo !")
        self._undo_pointer -= 1
        self._undo_stack[self._undo_pointer].undo_function()
    def redo(self):
        if self._undo_pointer == len(self._undo_stack):
            raise UndoRedoException("There are no operations to redo !")
        self._undo_stack[self._undo_pointer].redo_function()
        self._undo_pointer += 1
class Service:
    def __init__(self, book_repository=None, client_repository=None, book_validator=None, client_validator=None, rental_repository=None, rental_validator=None):
        if book_repository is None:
            book_repository = BookRepo()
        if client_repository is None:
            client_repository = ClientRepo()
        if book_validator is None:
            book_validator = BookValidator()
        if client_validator is None:
            client_validator = ClientValidator()
        if rental_repository is None:
            rental_repository = RentalRepo()
        if rental_validator is None:
            rental_validator = RentalValidator()
        self._book_repository = book_repository
        self._client_repository = client_repository
        self._book_validator = book_validator
        self._client_validator = client_validator
        self._rental_repository = rental_repository
        self._rental_validator = rental_validator
        self._undo_redo_service = UndoRedoServ(self._book_repository, self._client_repository,self._rental_repository)
    @property
    def client_repository(self):
        return self._client_repository

    @property
    def book_repository(self):
        return self._book_repository

    @property
    def rental_repository(self):
        return self._rental_repository

    def data_from_books_repository(self):
        books_list=self._book_repository.books_data_list()
        return books_list
    def data_from_clients_repository(self):
        clients_list=self._client_repository.clients_data_list()
        return clients_list
    def data_from_rentals_repository(self):
        rentals_list=self._rental_repository.rentals_data_list()
        return rentals_list
    def find_book(self, book_id):
        books_list = self.data_from_books_repository()
        for book in books_list:
            current_book_id = book.book_id
            if current_book_id == int(book_id):
                return True, book
        return False, None
    def find_client(self, client_id):
        clients_list=self.data_from_clients_repository()
        for c in clients_list:
            current_id=c.client_id
            if current_id==int(client_id):
                return True, c
        return False, None
    def is_book_rented(self, book_id):
        rentals_list = self.data_from_rentals_repository()
        for rental in rentals_list:
            current_rental_book_id = rental.book_id
            current_rental_return_date = rental.returned_date
            if current_rental_book_id == int(book_id) and current_rental_return_date is None:
                return True, rental.rental_id
        return False,None
    def was_book_rented(self, book_id):
        rentals_list = self.data_from_rentals_repository()
        for rental in rentals_list:
            current_rental_book_id = rental.book_id
            if current_rental_book_id == int(book_id):
                return True, rental.rental_id
        return False,None
    def find_rental(self, rental_id):
        rentals_list = self.data_from_rentals_repository()
        for rental in rentals_list:
            current_rental_id = rental.rental_id
            if current_rental_id == int(rental_id):
                return True, rental.rented_date, rental
        return False,None,None
    def client_has_rentals(self, client_id):
        rentals_list = self.data_from_rentals_repository()
        clients_rental_ids_list = []
        for rental in rentals_list:
            current_rental_client_id = rental.client_id
            if current_rental_client_id == int(client_id):
                clients_rental_ids_list.append(rental.rental_id)
        if len(clients_rental_ids_list)==0:
            return False,None
        return True, clients_rental_ids_list
    def return_rental_for_a_given_book(self, book_id):
        rentals_list = self.data_from_rentals_repository()
        for rental in rentals_list:
            current=rental.book_id
            if current== int(book_id):
                return rental
        return None

    def create_rentals_list_for_a_given_client(self,client_id):
        rentals_list_for_given_client = []
        rentals_list=self.data_from_rentals_repository()
        for rental in rentals_list:
            current =rental.client_id
            if current== int(client_id):
                rentals_list_for_given_client.append(rental)
        return rentals_list_for_given_client
    def add_book(self, id,title,author):
        if not id.isnumeric():
            raise IdException("Invalid ID! Try something else!")
        book = Book(int(id), title, author)
        self._book_validator.validate_book(book)
        exist, book1=self.find_book(id)
        if exist:
            raise RepositoryException("This book id already exists! ")
        self._undo_redo_service.add_undo_redo_operations(UndoRedoObj(lambda: self.book_repository.remove_book(id),lambda: self.book_repository.add_book(book)))
        self._book_repository.add_book(book)
    def remove_book(self, id):
        if not id.isnumeric():
            raise IdException("Invalid ID! Try something else!")
        exist, book1=self.find_book(int(id))
        if exist:
            found_book_rental, rental_id = self.was_book_rented(int(id))
            if found_book_rental:
                rental=self.return_rental_for_a_given_book(int(id))

            def undo_function():
                if found_book_rental:
                    self.rental_repository.add_rental(rental)
                self.book_repository.add_book(book1)
            def redo_function():
                if found_book_rental:
                    self.rental_repository.delete_rental(int(rental_id))
                self.book_repository.remove_book(int(id))
            self._undo_redo_service.add_undo_redo_operations(UndoRedoObj(undo_function, redo_function))
            if found_book_rental:
                self._rental_repository.delete_rental(rental_id)
            self._book_repository.remove_book(int(id))
        else:
            raise RepositoryException("There are no books with given ID!")

    def update_book(self,id, title, author):
        if not id.isnumeric():
            raise IdException("Invalid ID! Try something else!")
        updated_book=Book(int(id), title,author)
        self._book_validator.validate_book(updated_book)#####
        exist, book=self.find_book(int(id))
        if exist:
            self._undo_redo_service.add_undo_redo_operations(
                UndoRedoObj(lambda: self.book_repository.update_book(book),lambda: self.book_repository.update_book(updated_book)))
            self._book_repository.update_book(updated_book)
        else:
            raise RepositoryException("Update failed! This book does not exist in the list!")

    def search_book_by_id(self, id):
        book_matches_list=[]
        books_list=self.data_from_books_repository()
        for book in books_list:
            if re.search(id, str(book.book_id), re.IGNORECASE):
                book_matches_list.append(book)
        return book_matches_list
    def search_book_by_title(self, title):
        book_matches_list = []
        books_list = self.data_from_books_repository()
        for book in books_list:
            if re.search(title, book.title, re.IGNORECASE):
                book_matches_list.append(book)
        return book_matches_list
    def search_book_by_author(self, author):
        book_matches_list = []
        books_list = self.data_from_books_repository()
        for book in books_list:
            if re.search(author, book.author, re.IGNORECASE):
                book_matches_list.append(book)
        return book_matches_list


    def add_client(self, id, name):
        if not id.isnumeric():
            raise IdException("Invalid ID! Try something else!")
        client = Client(int(id), name)
        self._client_validator.validate_client(client)
        exist,client1 = self.find_client(int(id))
        if exist:
            raise RepositoryException("This client id already exists! ")
        self._client_repository.add_client(client)
        self._undo_redo_service.add_undo_redo_operations(UndoRedoObj(lambda: self.client_repository.remove_client(int(id)),lambda: self.client_repository.add_client(client)))

    def remove_client(self, id):
        if not id.isnumeric():
            raise IdException("Invalid ID! Try something else!")
        exist, client = self.find_client(int(id))
        if exist:
            client_has_rental, rental_ids_list = self.client_has_rentals(int(id))
            if client_has_rental:
                list_of_client_rentals = self.create_rentals_list_for_a_given_client(int(id))

            def undo_function():
                if client_has_rental:
                    if len(list_of_client_rentals) != 0:
                        for rental in list_of_client_rentals:
                            self.rental_repository.add_rental(rental)
                self.client_repository.add_client(client)

            def redo_function():
                if client_has_rental:
                    for a_rental_id in rental_ids_list:
                        self.rental_repository.delete_rental(int(a_rental_id))
                self.client_repository.remove_client(int(id))

            self._undo_redo_service.add_undo_redo_operations(UndoRedoObj(undo_function, redo_function))
            if client_has_rental:
                for a_rental_id in rental_ids_list:
                    self.rental_repository.delete_rental(int(a_rental_id))
            self._client_repository.remove_client(int(id))
        else:
            raise RepositoryException("There are no clients with given ID!")
    def update_client(self, id, name):
        if not id.isnumeric():
            raise IdException("Invalid input for the ID!")
        updated_client = Client(int(id), name)
        self._client_validator.validate_client(updated_client)
        exist, client = self.find_client(int(id))
        if exist:
            self._undo_redo_service.add_undo_redo_operations(UndoRedoObj(lambda: self.client_repository.update_client(client),lambda: self.client_repository.update_client(updated_client)))
            self._client_repository.update_client(updated_client)
        else:
            raise RepositoryException("Update failed! This client does not exist in the list!")

    def search_client_by_id(self, id):
        client_matches_list = []
        clients_list = self.data_from_clients_repository()
        for client in clients_list:
            if re.search(id, str(client.client_id), re.IGNORECASE):
                client_matches_list.append(client)
        return client_matches_list

    def search_client_by_name(self, name):
        client_matches_list = []
        clients_list = self.data_from_clients_repository()
        for client in clients_list:
            if re.search(name, client.name, re.IGNORECASE):
                client_matches_list.append(client)
        return client_matches_list

    def rent_book(self, rental_id, book_id, client_id, rented_date):
        if not rental_id.isnumeric():
            raise IdException("Invalid input for the rental ID!")

        if not book_id.isnumeric():
            raise IdException("Invalid input for the book ID!")

        if not client_id.isnumeric():
            raise IdException("Invalid input for the client ID!")

        does_rental_exist, rental_date, rental = self.find_rental(rental_id)
        if does_rental_exist:
            raise RepositoryException("There already exists a rental with the same ID!")

        is_book_rented, rent_id = self.is_book_rented(int(book_id))
        if is_book_rented:
            raise RentalException("This book is already rented!")

        does_book_exist, book = self.find_book(book_id)
        if not does_book_exist:
            raise RentalException("This book does not exist!")

        does_client_exist, client = self.find_client(client_id)
        if not does_client_exist:
            raise RentalException("This client does not exist!")

        self._rental_validator.is_rental_date_valid(rented_date)
        day, month, year = rented_date.split('/')
        rented_date = datetime.date(int(year.strip()), int(month.strip()), int(day.strip()))
        book_rental = Rental(int(rental_id), int(book_id), int(client_id), rented_date)

        self._undo_redo_service.add_undo_redo_operations(UndoRedoObj(lambda: self.rental_repository.delete_rental(int(rental_id)),lambda: self.rental_repository.add_rental(book_rental)))
        self._rental_repository.add_rental(book_rental)

    def return_book(self, rental_id, return_date):
        if not rental_id.isnumeric():
            raise IdException("Invalid input for the rental ID!")

        exist, rental_date, rental = self.find_rental(int(rental_id))
        if exist:
            self._rental_validator.is_return_date_valid(return_date, rental_date)
            day, month, year = return_date.split('/')
            return_date = datetime.date(int(year.strip()), int(month.strip()), int(day.strip()))

            def undo_function():
                self.rental_repository.rentals_data_list()[rental.rental_id - 1].returned_date = None

            self._undo_redo_service.add_undo_redo_operations(UndoRedoObj(undo_function,lambda: self.rental_repository.return_book(int(rental_id), return_date)))
            self._rental_repository.return_book(int(rental_id), return_date)
        else:
            raise RentalException("There does not exist any rental with this ID")

    def create_statistics_for_most_rented_books(self):
        rentals_data_list = self.data_from_rentals_repository()
        books_data_list = self.data_from_books_repository()
        most_rented_books = {}
        for book in books_data_list:
            current_book_id = book.book_id
            most_rented_books[current_book_id] = 0
        for rental in rentals_data_list:
            current_rental_book_id = rental.book_id
            most_rented_books[current_rental_book_id] += 1
        return most_rented_books

    def create_and_sort_list_of_statistics_for_most_rented_books(self, most_rented_books_dictionary):
        books_data_list = self.data_from_books_repository()
        most_rented_books_list = []
        for book_id in most_rented_books_dictionary:
            current_book_number_of_rentals = most_rented_books_dictionary.get(book_id)
            for book in books_data_list:
                current_book_id = book.book_id
                if book_id == current_book_id:
                    most_rented_books_list.append(BooksRentals(book, current_book_number_of_rentals))
        most_rented_books_list.sort(reverse=True,  key=lambda book_with_rentals: book_with_rentals.number_of_rentals)
        return most_rented_books_list

    def create_statistics_for_most_active_clients(self):
        rentals_data_list = self.data_from_rentals_repository()
        clients_data_list = self.data_from_clients_repository()
        most_active_clients = {}
        for client in clients_data_list:
            current_client_id = client.client_id
            most_active_clients[current_client_id] = 0
        for rental in rentals_data_list:
            current_rental_client_id = rental.client_id
            length_of_rental = self._rental_repository.len_of_rental(rental.rental_id)
            most_active_clients[int(current_rental_client_id)] += length_of_rental
        return most_active_clients

    def create_and_sort_list_of_statistics_for_most_active_clients(self, most_active_clients_dictionary):
        clients_data_list = self.data_from_clients_repository()
        most_active_clients_list = []
        for client_id in most_active_clients_dictionary:
            current_client_number_of_book_rental_days = most_active_clients_dictionary.get(client_id)
            for client in clients_data_list:
                current_client_id = client.client_id
                if client_id == current_client_id:
                    most_active_clients_list.append(ClientsRental(client, current_client_number_of_book_rental_days))
        most_active_clients_list.sort(key=lambda client_with_rental_days: client_with_rental_days.number_of_days_of_rentals, reverse=True)
        return most_active_clients_list

    def create_statistics_for_most_rented_authors(self):
        rentals_data_list = self.data_from_rentals_repository()
        books_data_list = self.data_from_books_repository()
        most_rented_author = {}
        for book in books_data_list:
            current_book_author = book.author
            if current_book_author not in most_rented_author:
                most_rented_author[current_book_author] = 0
        for rental in rentals_data_list:
            current_rental_book_id = rental.book_id
            for book in books_data_list:
                current_book_id = book.book_id
                current_book_author = book.author
                if current_book_id == current_rental_book_id:
                    most_rented_author[current_book_author] += 1
        return most_rented_author

    def create_and_sort_list_of_statistics_for_most_rented_authors(self, most_rented_author_dictionary):
        most_rented_author_list = []
        for author in most_rented_author_dictionary:
            current_author_number_of_rentals = most_rented_author_dictionary.get(author)
            most_rented_author_list.append(AuthorRentals(author, current_author_number_of_rentals))
        most_rented_author_list.sort(key=lambda author_with_rentals: author_with_rentals.number_of_rentals,reverse=True)
        return most_rented_author_list

    def undo(self):
        self._undo_redo_service.undo()

    def redo(self):
        self._undo_redo_service.redo()