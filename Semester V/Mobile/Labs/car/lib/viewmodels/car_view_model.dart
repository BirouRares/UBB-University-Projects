import '../models/car_model.dart';


class CarViewModel {
  List<Car> _cars = [];

  CarViewModel() {
    // Prepopulate the list with two car elements
    _cars = [
      Car(
        modelName: 'Model S',
        brand: 'Tesla',
        year: 2022,
        price: 79999.99,
        availabilityStatus: 'Available',
      ),
      Car(
        modelName: 'Mustang',
        brand: 'Ford',
        year: 2021,
        price: 55999.99,
        availabilityStatus: 'Sold Out',
      ),
    ];
  }

  List<Car> get cars => _cars;

  void addCar(Car car) {
    _cars.add(car);
  }

  void updateCar(int index, Car updatedCar) {
    _cars[index] = updatedCar;
  }

  void deleteCar(int index) {
    _cars.removeAt(index);
  }
}