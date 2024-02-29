import unittest
from src.repository.book_repo import BookRepo
from src.repository.client_repo import ClientRepo
from src.repository.rental_repo import RentalRepo
from src.domain.rental_class import Rental, generate_rentals
from src.domain.rental_class import BooksRentals
from src.domain.rental_class import AuthorRentals
from src.domain.rental_class import ClientsRental
from src.domain.book_class import Book, generate_books
from src.domain.client_class import Client
from src.domain.validator_class import BookValidator
from src.domain.validator_class import ClientValidator
from src.domain.validator_class import RentalValidator
from src.domain.exceptions_class import RepositoryException, ClientValidatorExceptions, BookValidatorExceptions, \
    DateException, BookException, ClientException
from src.domain.exceptions_class import IdException
from src.domain.exceptions_class import UndoRedoException
from src.domain.exceptions_class import RentalException
from src.services.services_class import Service
import datetime

class Test(unittest.TestCase):
    def setUp(self) -> None:
        self._service=Service()

        self._correct_book_id = 1
        self._correct_book_title = "Povestea lui Harap Alb"
        self._correct_book_author = "Ion Creanga"
        self._book = Book(self._correct_book_id, self._correct_book_title, self._correct_book_author)

        self._correct_client_id = 1
        self._correct_name = "Alexandra"
        self._client = Client(self._correct_client_id, self._correct_name)

        self._rental = Rental(1, 1, 1, datetime.date(2020, 12, 12), datetime.date(2020, 12, 15))
        self._rental_with_no_return_date = Rental(2, 2, 2, datetime.date(2021, 12, 1))
        self._book = Book(1, "Povestea lui Harap Alb", "Ion Creanga")
        self._number_of_rentals_for_book = 3
        self._book_with_rentals = BooksRentals(self._book, self._number_of_rentals_for_book)
        self._client = Client(1, "Anamaria")
        self._number_of_days_of_rentals = 10
        self._client_with_rental_days = ClientsRental(self._client, self._number_of_days_of_rentals)
        self._author = "Ion Creanga"
        self._number_of_rentals_for_author = 3
        self._author_with_rentals = AuthorRentals(self._author, self._number_of_rentals_for_author)

        self._book_repository = BookRepo()

        self._client_repository = ClientRepo()

        self._rental_repository = RentalRepo()

        self._IdException = IdException
        self._UndoRedoException = UndoRedoException
        self._DateException = DateException
        self._RepositoryException = RepositoryException
        self._RentalException = RentalException
        self._BookException = BookException
        self._BookValidatorExceptions = BookValidatorExceptions
        self._ClientException = ClientException
        self._ClientValidatorExceptions = ClientValidatorExceptions

        self._book_validator = BookValidator()
        self._wrong_book_id = "a"
        self._wrong_book_title = "1"
        self._wrong_book_author = "1"
        self._wrong_book = Book(self._wrong_book_id, self._wrong_book_title, self._wrong_book_author)
        self._rental_validator = RentalValidator()
        self._client_validator = ClientValidator()
        self._wrong_client_id = "a"
        self._wrong_name = "1"
        self._wrong_client = Client(self._wrong_client_id, self._wrong_name)

    def test_ClientRepo_NoInput_Listofclients(self):
        self.assertIsInstance(self._service.data_from_clients_repository(), list)
    def test_addClient_allcorect(self):
        self._service.add_client("245", "Ioan")
        self.assertEqual(len(self._service.client_repository), 21)
    def test_addClient_wrongID(self):
        with self.assertRaises(IdException):
            self._service.add_client("3rt", "Ioan")
    def test_addClient_WrongName(self):
        with self.assertRaises(ClientValidatorExceptions):
            self._service.add_client("245", "300")
    def test_addClient_IDused(self):
        with self.assertRaises(RepositoryException):
            self._service.add_client("20", "Ioan")

    def test_removeClient_allCorect(self):
        self._service.remove_client("1")
        self.assertEqual(len(self._service.client_repository), 19)
    def test_removeClient_WrongInput(self):
        with self.assertRaises(IdException):
            self._service.remove_client("a")
    def test_removeClient_IdNotExist(self):
        with self.assertRaises(RepositoryException):
            self._service.remove_client("21")

    def test_updateClient_allCorect(self):
        self._service.update_client("4","Mihai")
        self.assertEqual(self._service.data_from_clients_repository()[3].name, "Mihai")
    def test_updateClient_WrongID(self):
        with self.assertRaises(IdException):
            self._service.update_client("43e", "Mihai")
    def test_updateClient_IdNotExist(self):
        with self.assertRaises(RepositoryException):
            self._service.update_client("21","Mihai")

    def test_updateClient_WrongName(self):
        with self.assertRaises(ClientValidatorExceptions):
            self._service.update_client("21", "300")


    def test_dataFromBooksRepository(self):
        self.assertIsInstance(self._service.data_from_books_repository(), list)

    def test_addBook_allcorect(self):
        self._service.add_book("21", "O poveste", "Mihai Daian")
        self.assertEqual(len(self._service.book_repository), 21)
    def test_addBook_wrongid(self):
        with self.assertRaises(IdException):
            self._service.add_book("a", "O poveste", "Mihai Daian")

    def test_addBook_bookExists(self):
        with self.assertRaises(RepositoryException):
            self._service.add_book("1", "O poveste", "Mihai Daian")
    def test_addBook_wrongtitle(self):
        with self.assertRaises(BookValidatorExceptions):
            self._service.add_book("21", "300", "Mihai Daian")
    def test_addBook_wrongauthor(self):
        with self.assertRaises(BookValidatorExceptions):
            self._service.add_book("21", "O poveste", "300")

    def test_removeBook__CorrectInput(self):
        self._service.remove_book("7")
        self.assertEqual(len(self._service.book_repository),19)
    def test_removeBook_WorngId(self):
        with self.assertRaises(IdException):
            self._service.remove_book("a")
    def test_removeBook_bookNotExist(self):
        with self.assertRaises(RepositoryException):
            self._service.remove_book("21")


    def test_updateBook__CorrectInput(self):
        self._service.update_book("8", "Enigma Otiliei", "George Calinescu")
        self.assertEqual(self._service.data_from_books_repository()[7].title, "Enigma Otiliei")
        self.assertEqual(self._service.data_from_books_repository()[7].author, "George Calinescu")
    def test_updateBook_wrongId(self):
        with self.assertRaises(IdException):
            self._service.update_book("a", "Enigma Otiliei", "George Calinescu")
    def test_updateBook_bookNotExist(self):
        with self.assertRaises(RepositoryException):
            self._service.update_book("21", "Enigma Otiliei", "George Calinescu")
    def test_updateBook_wrongTitle(self):
        with self.assertRaises(BookValidatorExceptions):
            self._service.update_book("8", "300", "George Calinescu")
    def test_updateBook_wrongAuthor(self):
        with self.assertRaises(BookValidatorExceptions):
            self._service.update_book("8", "Enigma Otiliei", "300")

    def test_dataFromRentalsRepository(self):
        self.assertIsInstance(self._service.data_from_rentals_repository(), list)
    def test_rentBook_allCorect(self):
        self._service.rent_book("11", "20", "1", "20/11/2020")
        self.assertEqual(len(self._service.rental_repository), 11)

    def test_rentBook_wrongRentalId(self):
        with self.assertRaises(IdException):
            self._service.rent_book("a", "20", "1", "20/11/2020")

    def test_rentBook_wrongBookId(self):
        with self.assertRaises(IdException):
            self._service.rent_book("11", "a", "1", "20/11/2020")
    def test_rentBook_wrongClientId(self):
        with self.assertRaises(IdException):
            self._service.rent_book("11", "20", "t3", "20/11/2020")
    def test_rentBook_wrongDate(self):
        with self.assertRaises(DateException):
            self._service.rent_book("11", "20", "1", "200/100/2020")
    def test_rentBook_DateNotReached(self):
        with self.assertRaises(DateException):
            self._service.rent_book("11", "20", "1", "20/11/2024")
    def test_rentBook_IdUsed(self):
        with self.assertRaises(RepositoryException):
            self._service.rent_book("1", "20", "1", "20/11/2020")
    def test_rentBook_BookNotExist(self):
        with self.assertRaises(RentalException):
            self._service.rent_book("11", "2000", "1", "20/11/2020")
    def test_rentBook_ClientDoesNotExist(self):
        with self.assertRaises(RentalException):
            self._service.rent_book("11", "20", "1234", "20/11/2020")
    def test_rentBook_BookAlreadyRented(self):
        with self.assertRaises(RentalException):
            self._service.rent_book("11", "1", "5", "20/11/2020")

    def test_returnBook__CorrectInput(self):
        self._service.return_book("1", "2/11/2021")
        self.assertEqual(self._service.data_from_rentals_repository()[0].returned_date, datetime.date(2021, 11, 2))
    def test_returnBook__WrongInputForRentalId(self):
        with self.assertRaises(IdException):
            self._service.return_book("a", "1/11/2021")
    def test_returnBook__WrongDate(self):
        with self.assertRaises(DateException):
            self._service.return_book("1", "100/11/2021")

    def test_returnBook__DateBeforRental(self):
        with self.assertRaises(DateException):
            self._service.return_book("1", "10/11/1990")
    def test_returnBook__IdNotExists(self):
        with self.assertRaises(RentalException):
            self._service.return_book("100", "10/11/2022")


    def test_searchBookById__CorrectInput(self):
        self.assertEqual(len(self._service.search_book_by_id("1")), 11)

    def test_searchBookById__InputThatReturnsNoMatches(self):
        self.assertEqual(len(self._service.search_book_by_id("100")), 0)

    def test_searchBookByTitle__CorrectInput(self):
        self.assertEqual(len(self._service.search_book_by_title("Ion")), 1)
    def test_searchBookByTitle_BookNotExist(self):
        self.assertEqual(len(self._service.search_book_by_title("Amer")), 0)

    def test_searchBookByAuthor__Corect(self):
        self.assertEqual(len(self._service.search_book_by_author("Mihail Sadoveanu")), 1)
    def test_searchBookByAuthor__AuthorNotExist(self):
        self.assertEqual(len(self._service.search_book_by_author("Mihnea")), 0)

    def test_searchClientById__CorrectInput(self):
        self.assertEqual(len(self._service.search_client_by_id("1")), 11)
    def test_searchClientById_WrongId(self):
        self.assertEqual(len(self._service.search_client_by_id("100")), 0)

    def test_searchClientByName__CorrectInput(self):
        self.assertEqual(len(self._service.search_client_by_name("Rares3")), 0)

    def test_createStatisticsForMostRentedBooks(self):
        self.assertIsInstance(self._service.create_statistics_for_most_rented_books(),dict)

    def test_createAndSortListOfStatisticsForMostRentedBooks(self):
        dictionary=self._service.create_statistics_for_most_rented_books()
        self.assertIsInstance(self._service.create_and_sort_list_of_statistics_for_most_rented_books(dictionary), list)

    def test_createStatisticsForMostActiveClients(self):
        self.assertIsInstance(self._service.create_statistics_for_most_active_clients(), dict)
    def test_createAndSortListOfStatisticsForMostActiveClients(self):
        dictionary = self._service.create_statistics_for_most_active_clients()
        self.assertIsInstance(self._service.create_and_sort_list_of_statistics_for_most_active_clients(dictionary),list)

    def test_createStatisticsForMostRentedAuthors(self):
        self.assertIsInstance(self._service.create_statistics_for_most_rented_authors(), dict)

    def test_createAndSortListOfStatisticsForMostRentedAuthors(self):
        dic=self._service.create_statistics_for_most_rented_authors()
        self.assertIsInstance(self._service.create_and_sort_list_of_statistics_for_most_rented_authors(dic),list)

    def test_undoNoOp(self):
        with self.assertRaises(UndoRedoException):
            self._service.undo()
    def test_redoNoOp(self):
        with self.assertRaises(UndoRedoException):
            self._service.redo()
    def test_undo_add(self):
        self._service.add_book("21", "Ana are mere", "Pavel Bartos")
        self._service.undo()
        self.assertEqual(len(self._service.book_repository),20)
        self._service.redo()
        self.assertEqual(len(self._service.book_repository), 21)
    def test_undo_remove(self):
        self._service.remove_book("1")
        self._service.undo()
        self.assertEqual(len(self._service.book_repository),20)
        self._service.redo()
        self.assertEqual(len(self._service.book_repository), 19)
    def test_undo_update(self):
        self._service.update_book("6", "Ana are mere", "Pavel Bartos")
        self._service.undo()
        self.assertEqual(self._service.data_from_books_repository()[5].title, "Fluturi 2")
        self._service.redo()
        self.assertEqual(self._service.data_from_books_repository()[5].title, "Ana are mere")

    def test_undoRedoAnAddClient_long(self):
        self._service.add_client("21", "Mingea")
        self._service.add_client("22", "Minge")
        self._service.undo()
        self._service.undo()
        self.assertEqual(len(self._service.client_repository), 20)
        self._service.redo()
        self.assertEqual(len(self._service.client_repository), 21)
        self._service.redo()
        self.assertEqual(len(self._service.client_repository), 22)
        self._service.undo()
        self.assertEqual(len(self._service.client_repository), 21)
    def teste_unodredo_removeClient(self):
        self._service.remove_client("5")
        self._service.undo()
        self.assertEqual(len(self._service.client_repository), 20)
        self._service.redo()
        self.assertEqual(len(self._service.client_repository), 19)
        self._service.undo()
        self.assertEqual(len(self._service.client_repository), 20)

    def teste_unodredo_updateClient(self):
        self._service.update_client("1", "Mihnea")
        self._service.undo()
        self.assertEqual(self._service.data_from_clients_repository()[0].name, "Anamaria")
        self._service.redo()
        self.assertEqual(self._service.data_from_clients_repository()[0].name, "Mihnea")
    def test_unodrode_RetunrBook(self):
        self._service.return_book("7", "17/10/2020")
        self._service.undo()
        self.assertEqual(self._service.data_from_rentals_repository()[6].returned_date, None)
        self._service.redo()
        self.assertEqual(self._service.data_from_rentals_repository()[6].returned_date, datetime.date(2020, 10, 17))

    def test_book_NotRented(self):
        self.assertEqual(self._service.was_book_rented("20"), (False, None))
    def test_clientsRentals(self):
        self.assertEqual(self._service.client_has_rentals("10123"), (False, None))
    def test_undoredo_stack(self):
        self._service.add_client("21", "Miahil")
        self.assertEqual(len(self._service._undo_redo_service.undo_stack), 1)
        self._service.add_client("22", "Mihnea")
        self._service.undo()
        self.assertEqual(len(self._service._undo_redo_service.undo_stack), 2)
        self._service.undo()
        self.assertEqual(len(self._service._undo_redo_service.undo_stack), 2)
        self._service.redo()
        self.assertEqual(len(self._service._undo_redo_service.undo_stack), 2)



    def test_GetID(self):
        self.assertEqual(self._book.book_id, self._correct_book_id)
    def test_Gettitle(self):
        self.assertEqual(self._book.title,self._correct_book_title)
    def test_GetAuthor(self):
        self.assertEqual(self._book.author,self._correct_book_author)
    def test_bookIDSET(self):
        self._book.book_id = 40
        self.assertEqual(self._book.book_id, 40)
    def test_titleSetter(self):
        self._book.title = "Ana has an apple"
        self.assertEqual(self._book.title, "Ana has an apple")
    def test_authorSetter(self):
        self._book.author = "Mircea Eliade"
        self.assertEqual(self._book.author, "Mircea Eliade")
    def test_bookString__NoInput__String(self):
        self.assertEqual(str(self._book), "Book ID: 1, Povestea lui Harap Alb written by Ion Creanga")
    def test_generate_books(self):
        self.assertIsInstance(generate_books(), dict)
        self.assertEqual(len(generate_books()), 20)



    def test_clientID(self):
        self.assertEqual(self._client.client_id, self._correct_client_id)
    def test_clientName(self):
        self.assertEqual(self._client.name, self._correct_name)
    def test_SetId(self):
        self._client.client_id = 2
        self.assertEqual(self._client.client_id, 2)

    def test_SetName(self):
        self._client.name = "Matei"
        self.assertEqual(self._client.name, "Matei")
    def test_ClientString(self):
        self.assertEqual(str(self._client), "Client id: 1, Name: Anamaria")



    def test_rentalIdSetter(self):
        self._rental.rental_id = 2
        self.assertEqual(self._rental.rental_id, 2)
    def test_bookIdSetter(self):
        self._rental.client_id = 2
        self.assertEqual(self._rental.client_id, 2)

    def test_rentedDateSetter(self):
        self._rental.returned_date = datetime.date(2021, 1, 1)
        self.assertEqual(self._rental.returned_date, datetime.date(2021, 1, 1))

    def test_rentalString(self):
        self.assertEqual(str(self._rental), "Rental ID: 1, Book ID: 1, Client ID: 1, Rented date: 2020-12-12, ""Returned date: 2020-12-15")
    def test_rentalLength(self):
        self.assertEqual(len(self._rental), 4)
    def test_rentalLength__RentalWithoutReturnDate(self):
        self.assertEqual(self._book_with_rentals.book, self._book)
    def test_numberOfRentalsForBookGetter(self):
        self.assertEqual(self._book_with_rentals.number_of_rentals, self._number_of_rentals_for_book)
    def test_booksWithRentalsString(self):
        self.assertEqual(str(self._book_with_rentals), "Book: Povestea lui Harap Alb written by Ion Creanga was rented 3 times")


    def test_clientGetter(self):
        self.assertEqual(self._client_with_rental_days.client, self._client)
    def test_numberOfRentalDaysGetter(self):
        self.assertEqual(self._client_with_rental_days.number_of_days_of_rentals, self._number_of_days_of_rentals)
    def test_clientWithRentalDaysString(self):
        self.assertEqual(str(self._client_with_rental_days), "Client: Anamaria with id: 1 has 10 days of book rentals")
    def test_authorGetter(self):
        self.assertEqual(self._author_with_rentals.author, self._author)
    def test_numberOfRentalsForAuthorGetter(self):
        self.assertEqual(self._author_with_rentals.number_of_rentals, self._number_of_rentals_for_author)
    def test_authorWithRentalsString(self):
        self.assertEqual(str(self._author_with_rentals), "Books by Ion Creanga were rented 3 times")
    def test_generateRentals(self):
        self.assertIsInstance(generate_rentals(), dict)
    def test_booksDataList(self):
        self.assertIsInstance(self._book_repository.books_data_list(), list)
    def test_setItem__KeyAndValue(self):
        self._book_repository.__setitem__("21", Book(21, "ABC", "ABC"))
        self.assertEqual(len(self._book_repository), 21)
    def test_delItem(self):
        self._book_repository.__delitem__(1)
        self.assertEqual(len(self._book_repository), 19)
    def test_addBook(self):
        self._book_repository.add_book(Book(21, "adv", "ret"))
        self.assertEqual(len(self._book_repository), 21)
    def test_removeBook__bookId(self):
        self._book_repository.remove_book("1")
        self.assertEqual(len(self._book_repository), 19)
    def test_updateBook(self):
        self._book_repository.update_book(Book(1, "abc", "abc"))
        self.assertEqual(self._book_repository.books_data_list()[0].title, "abc")




    def test_clientsDataList(self):
        self.assertIsInstance(self._client_repository.clients_data_list(), list)
    def test_setItem__KeyAndValue_ItemAddedToClientsData(self):
        self._client_repository.__setitem__("21", Client(21, "ABC"))
        self.assertEqual(len(self._client_repository), 21)
    def test_delItem__key__ItemDeletedFromClientsData(self):
        self._client_repository.__delitem__(1)
        self.assertEqual(len(self._client_repository), 19)
    def test_addClient__givenClient__ClientAddedToClientsData(self):
        self._client_repository.add_client(Client(21, "ABC"))
        self.assertEqual(len(self._client_repository), 21)
    def test_removeClient__clientId__ClientRemovedFromClientsData(self):
        self._client_repository.remove_client("1")
        self.assertEqual(len(self._client_repository), 19)
    def test_updateClient__UpdatedClient__ClientUpdatedInClientsData(self):
        self._client_repository.update_client(Client(1, "abc"))
        self.assertEqual(self._client_repository.clients_data_list()[0].name, "abc")


    def test_rentalsDataList(self):
        self.assertIsInstance(self._rental_repository.rentals_data_list(), list)
    def test_setItem__KeyAndValue__ItemAddedToRentalsData(self):
        self._rental_repository.__setitem__("21", Rental(21, 20, 1, datetime.date(2020, 11, 11)))
        self.assertEqual(len(self._rental_repository), 11)
    def test_lengthOfRental__RentalId__LengthOfRental(self):
        self._rental_repository.add_rental(Rental(21, 20, 1, datetime.date(2021, 12, 1), datetime.date(2021, 12, 3)))
        self.assertEqual(self._rental_repository.len_of_rental(21), 3)
    def test_delItem__key__ItemDeletedFromRentalsData(self):
        self._rental_repository.__delitem__(1)
        self.assertEqual(len(self._rental_repository), 9)
    def test_addRental__givenRental__RentalAddedToRentalsData(self):
        self._rental_repository.add_rental(Rental(21, 20, 1, datetime.date(2020, 11, 11)))
        self.assertEqual(len(self._rental_repository), 11)
    def test_deleteRental__RentalId__RentalRemovedFromRentalsData(self):
        self._rental_repository.delete_rental(1)
        self.assertEqual(len(self._rental_repository), 9)
    def test_returnBook__RentalIdAndReturnDate__RentalUpdatedInRentalsData(self):
        self._rental_repository.return_book("1", datetime.date(2021, 12, 1))
        self.assertEqual(self._rental_repository.rentals_data_list()[0].returned_date, datetime.date(2021, 12, 1))


    def test_IdExceptionString__message__string(self):
        self.assertEqual(str(IdException("Invalid Id")), "Invalid Id")
    def test_UndoRedoExceptionString__message__string(self):
        self.assertEqual(str(UndoRedoException("No operations to undo")), "No operations to undo")
    def test_DateExceptionString__message__string(self):
        self.assertEqual(str(DateException("Invalid date")), "Invalid date")
    def test_RepositoryExceptionString__message__string(self):
        self.assertEqual(str(RepositoryException("Client already in repository!")), "Client already in repository!")
    def test_RentalExceptionString__message__string(self):
        self.assertEqual(str(RentalException("Book already rented")), "Book already rented")
    def test_BookExceptionString__message__string(self):
        self.assertEqual(str(BookException("Invalid title")), "Invalid title")
    def test_BookValidatorExceptionsString__messageList__string(self):
        self.assertEqual(str(BookValidatorExceptions(["Invalid title", "Invalid id"])), "Invalid title\nInvalid id\n")
    def test_ClientExceptionString__message__string(self):
        self.assertEqual(str(ClientException("Invalid name")), "Invalid name")
    def test_ClientValidatorExceptions__messageList__string(self):
        self.assertEqual(str(ClientValidatorExceptions(["Invalid name", "Invalid id"])), "Invalid name\nInvalid id\n")


    def test_bookValidator_BookWithWrongIdTitleAndAuthor__BookValidatorException(self):
        with self.assertRaises(BookValidatorExceptions):
            self._book_validator.validate_book(self._wrong_book)
    def test_clientValidator__ClientWithWrongIdAndName__ClientValidatorException(self):
        with self.assertRaises(ClientValidatorExceptions):
            self._client_validator.validate_client(self._wrong_client)
    def test_rentalValidator__InvalidRentalDate__DateException(self):
        with self.assertRaises(DateException):
            self._rental_validator.is_rental_date_valid("120/10/2020")
    def test_rentalValidator__RentalDateAfterToday__DateException(self):
        with self.assertRaises(DateException):
            self._rental_validator.is_rental_date_valid("12/12/2023")
    def test_rentalValidator__InvalidReturnDate__DateException(self):
        with self.assertRaises(DateException):
            self._rental_validator.is_return_date_valid("120/12/2020", "12/11/2020")
    def test_rentalValidator__ReturnDateBeforeRentalDate__DateException(self):
        with self.assertRaises(DateException):
            self._rental_validator.is_return_date_valid("10/12/2020", datetime.date(2020, 12, 12))
