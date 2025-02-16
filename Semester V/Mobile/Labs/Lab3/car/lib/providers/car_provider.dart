import 'package:flutter/material.dart';
import '../models/car_model.dart';

class CarProvider with ChangeNotifier {
  final List<Car> _cars = [];

  List<Car> get cars => List.unmodifiable(_cars);

  void addCar(Car car) {
    _cars.add(car);
    notifyListeners();
  }

  void updateCar(int index, Car car) {
    _cars[index] = car;
    notifyListeners();
  }

  void deleteCar(int index) {
    _cars.removeAt(index);
    notifyListeners();
  }
}
