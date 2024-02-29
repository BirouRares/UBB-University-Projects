from src.services.services_class import Service
class UI:
    def __init__(self, service=None):
        if service is None:
            service = Service()
        self._service = service

    def list_books(self):
        print("\n The Books are:")
        books_list=self._service.data_from_books_repository()
        for i in books_list:
            print(i)
        print("\n")

    def add_book_ui(self):
        id=input("Book ID: ")
        title=input("Book title: ")
        author=input("Book author: ")
        try:
            self._service.add_book(id, title, author)
        except Exception as mes:
            print(str(mes))

    def remove_book_ui(self):
        book_id = input("Write the ID of the book you want to remove: ")
        try:
            self._service.remove_book(book_id)
            print("Book removed successfully!")
        except Exception as message:
            print(str(message))
    def update_book_ui(self):
        id= input("ID of the book you want to update: ")
        new_title = input("New title: ")
        new_author = input("New author: ")
        try:
            self._service.update_book(id, new_title, new_author)
            print("Book updated successfully!")
        except Exception as message:
            print(str(message))
    def search_book_ui(self):
        print("By which field do you want to search? ")
        print("a. Search by id")
        print("b. Search by title")
        print("c. Search by author")
        user_input = input("Write the letter of your option: ")
        if user_input.strip() == "a":
            id_to_search = input("Write the id of the book you want to search: ").strip()
            book_matches_list = self._service.search_book_by_id(id_to_search)
            if len(book_matches_list) == 0:
                print("There are no results!")
            else:
                print("These are the results: ")
                for book in book_matches_list:
                    print(book)
        elif user_input.strip() == "b":
            title_to_search = input("Write the title of the book you want to search: ").strip()
            book_matches_list = self._service.search_book_by_title(title_to_search)
            if len(book_matches_list) == 0:
                print("There are no results!")
            else:
                print("These are the results: ")
                for book in book_matches_list:
                    print(book)
        elif user_input.strip() == "c":
            author_to_search = input("Write the author of the book you want to search: ").strip()
            book_matches_list = self._service.search_book_by_author(author_to_search)
            if len(book_matches_list) == 0:
                print("There are no results!")
            else:
                print("These are the results: ")
                for book in book_matches_list:
                    print(book)
        else:
            print("This option does not exist! ")
    def list_clients(self):
        print("\n The Clients are:")
        clients_list = self._service.data_from_clients_repository()
        for client in clients_list:
            print(client)
        print("\n")
    def add_client_ui(self):
        client_id = input("Client ID: ")
        name = input("Client's name: ")
        try:
            self._service.add_client(client_id, name)
            print("Client added successfully!")
        except Exception as message:
            print(str(message))
    def remove_client_ui(self):
        client_id = input("Write the ID of the client you want to remove: ")
        try:
            self._service.remove_client(client_id)
            print("Client removed successfully!")
        except Exception as message:
            print(str(message))
    def update_client_ui(self):
        client_id = input("Write the ID of the client you want to update: ")
        new_name = input("Write the new name: ")
        try:
            self._service.update_client(client_id, new_name)
            print("Client updated successfully!")
        except Exception as message:
            print(str(message))
    def search_client_ui(self):
        print("By which field do you want to search? ")
        print("a. Search by id")
        print("b. Search by name")
        user_input = input("Write the letter of your option: ")
        if user_input.strip() == "a":
            id_to_search = input("Write the id of the client you want to search: ").strip()
            client_matches_list = self._service.search_client_by_id(id_to_search)
            if len(client_matches_list) == 0:
                print("There are no results for this search!")
            else:
                print("These are the results: ")
                for client in client_matches_list:
                    print(client)
        elif user_input.strip() == "b":
            name_to_search = input("Write the name of the client you want to search: ").strip()
            client_matches_list = self._service.search_client_by_name(name_to_search)
            if len(client_matches_list) == 0:
                print("There are no results for this search!")
            else:
                print("These are the results: ")
                for client in client_matches_list:
                    print(client)
        else:
            print("This option does not exist! ")
    def list_rentals(self):
        print("These are the rentals: ")
        rentals_list = self._service.data_from_rentals_repository()
        for rental in rentals_list:
            if rental.returned_date is None:
                print(rental)
        print("\n")

    def rent_book_ui(self):
        rental_id = input("Write the ID of the rental: ")
        book_id = input("Write the ID of the book you wanna rent: ")
        client_id = input("Write the client's ID: ")
        rented_date = input("Write the date of the rent in format dd/mm/yyyy: ")
        try:
            self._service.rent_book(rental_id, book_id, client_id, rented_date)
            print("Book rented successfully!")
        except Exception as message:
            print(str(message))
    def return_book_ui(self):
        self.list_rentals()
        rental_id = input("Which book do you want to return ?  Write the rental ID: ")
        return_date = input("Write the date of the return: ")
        try:
            self._service.return_book(rental_id, return_date)
            print("Book returned successfully!")
        except Exception as message:
            print(str(message))
    def print_statistics_for_most_rented_books(self):
        most_rented_books_dictionary = self._service.create_statistics_for_most_rented_books()
        most_rented_books_list = self._service.create_and_sort_list_of_statistics_for_most_rented_books(most_rented_books_dictionary)
        for book_with_rentals in most_rented_books_list:
            print(book_with_rentals)

    def print_statistics_for_most_active_clients(self):
        most_active_clients_dictionary = self._service.create_statistics_for_most_active_clients()
        most_active_clients_list = self._service.create_and_sort_list_of_statistics_for_most_active_clients(
            most_active_clients_dictionary)
        for client_with_rental_days in most_active_clients_list:
            print(client_with_rental_days)

    def print_statistics_for_most_rented_authors(self):
        most_rented_author_dictionary = self._service.create_statistics_for_most_rented_authors()
        most_rented_author_list = self._service.create_and_sort_list_of_statistics_for_most_rented_authors(
            most_rented_author_dictionary)
        for author_with_rentals in most_rented_author_list:
            print(author_with_rentals)
    def undo_ui(self):
        #   This function undoes the last operation executed.
        try:
            self._service.undo()
            print("Operation undone successfully !")
        except Exception as message:
            print(str(message))
    def redo_ui(self):
        #   This function redoes the last operation undone.
        try:
            self._service.redo()
            print("Operation redone successfully !")
        except Exception as message:
            print(str(message))

    @staticmethod
    def print_menu():
        print("\n")
        print("You have the next options:  ")
        print("1. Add client")
        print("2. Add book")
        print("3. Remove client")
        print("4. Remove book")
        print("5. Update client")
        print("6. Update book")
        print("7. List clients")
        print("8. List books")
        print("9. List rentals")
        print("10. Rent book")
        print("11. Return book")
        print("12. Search client")
        print("13. Search book")
        print("14. Statistics for most rented books")
        print("15. Statistics for most active clients")
        print("16. Statistics for most rented author")
        print("17. Undo")
        print("18. Redo")
        print("19. Exit")
        print("\n")
    def start(self):
        while True:
            UI.print_menu()
            opt=input(">").strip()
            print("\n")
            if opt == "1":
                self.add_client_ui()
            elif opt == "2":
                self.add_book_ui()
            elif opt == "3":
                self.remove_client_ui()
            elif opt == "4":
                self.remove_book_ui()
            elif opt == "5":
                self.update_client_ui()
            elif opt == "6":
                self.update_book_ui()
            elif opt == "7":
                self.list_clients()
            elif opt == "8":
                self.list_books()
            elif opt == "9":
                self.list_rentals()
            elif opt == "10":
                self.rent_book_ui()
            elif opt == "11":
                self.return_book_ui()
            elif opt == "12":
                self.search_client_ui()
            elif opt == "13":
                self.search_book_ui()
            elif opt == "14":
                self.print_statistics_for_most_rented_books()
            elif opt == "15":
                self.print_statistics_for_most_active_clients()
            elif opt == "16":
                self.print_statistics_for_most_rented_authors()
            elif opt == "17":
                self.undo_ui()
            elif opt == "18":
                self.redo_ui()
            elif opt == "19":
                print("Take care!\n")
                return
            else:
                print("Wrong commnad! Try again!")
ui=UI()
ui.start()
