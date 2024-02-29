from src.domain.book_class import generate_books

class BookRepo:
    def __init__(self):
        self._books_data=generate_books()
    def __setitem__(self, key, value):
        self._books_data[key]=value
    def __delitem__(self, key):
        del self._books_data[key]
    def __len__(self):
        return len(self._books_data)
    def books_data_list(self):
        return list(self._books_data.values())
    def add_book(self, book):
        self._books_data[int(book.book_id)]=book
    def remove_book(self, book_id):
        del self._books_data[int(book_id)]
    def update_book(self, book):
        self._books_data[int(book.book_id)]=book
