from src.domain.rental_class import generate_rentals
import datetime

class RentalRepo:
    def __init__(self):
        self._rentals_data=generate_rentals()
    def __setitem__(self, key, value):
        self._rentals_data[key]=value
    def __delitem__(self, key):
        del self._rentals_data[key]
    def __len__(self):
        return len(self._rentals_data)
    def rentals_data_list(self):
        return list(self._rentals_data.values())
    def add_rental(self, rental):
        self._rentals_data[int(rental.rental_id)]=rental
    def delete_rental(self, rental_id):
        del self._rentals_data[int(rental_id)]
    def return_book(self, rental_id, return_date):
        self._rentals_data[int(rental_id)].returned_date=return_date
    def len_of_rental(self, rental_id):
        if self._rentals_data[int(rental_id)].returned_date is None:
            t=datetime.date.today()
            rental_date=self._rentals_data[int(rental_id)].rented_date
            return (t-rental_date).days+1
        return_date=self._rentals_data[int(rental_id)].returned_date
        rental_date=self._rentals_data[int(rental_id)].rented_date
        return (return_date-rental_date).days+1