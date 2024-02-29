class Book:
    def __init__(self, book_id: int, title: str, author: str):
        self._book_id=book_id
        self._title=title
        self._author=author
    @property
    def book_id(self):
        return self._book_id
    @book_id.setter
    def  book_id(self, book_id):
        self._book_id=book_id
    @property
    def title(self):
        return self._title
    @title.setter
    def title(self, title):
        self._title=title
    @property
    def author(self):
        return  self._author
    @author.setter
    def author(self,author):
        self._author=author
    def __str__(self):
        return "Book ID: "+ str(self._book_id) + ", " + self._title + " written by " + self._author

def generate_books():
    books = [{"title": "Povestea lui Harap Alb", "author": "Ion Creanga"},
             {"title": "Amintiri din copilarie", "author": "Ion Creanga"},
             {"title": "Capra cu trei iezi", "author": "Ion Creanga"},
             {"title": "Punguta cu doi bani", "author": "Ion Creanga"},
             {"title": "Fluturi 1", "author": "Irina Binder"},
             {"title": "Fluturi 2", "author": "Irina Binder"},
             {"title": "Ion", "author": "Liviu Rebreanu"},
             {"title": "Padurea spanzuratilor", "author": "Liviu Rebreanu"},
             {"title": "Fluturi 3", "author": "Irina Binder"},
             {"title": "Tata bogat, tata sarac", "author": "Robert T. Kiyosaki"},
             {"title": "Harry Potter and the Sorcerer’s Stone", "author": "JK Rowling"},
             {"title": "Harry Potter and the Chamber of Secrets", "author": "JK Rowling"},
             {"title": "Enigma Otiliei", "author": "George Calinescu"},
             {"title": "Acolo unde canta racii", "author": "Delia Owens"},
             {"title": "Baltagul", "author": "Mihail Sadoveanu"},
             {"title": "Mortal Engines", "author": "Philip Reeve"},
             {"title": "Fiecare moare singur", "author": "Hans Fallada"},
             {"title": "Viata este o poveste", "author": "Florin Piersic"},
             {"title": "Morometii ", "author": "Marin Preda"},
             {"title": "Alice in tara minunilor", "author": "Lewis Carroll"}]
    books_data = {}
    for i in range(1, 21):
        book_id=i
        book=books[i-1]
        book_title = book["title"]
        book_author = book["author"]
        generated_book = Book(book_id, book_title, book_author)
        books_data[book_id] = generated_book
    return books_data