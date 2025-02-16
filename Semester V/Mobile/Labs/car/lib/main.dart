import 'package:car/viewmodels/car_view_model.dart';
import 'package:car/views/car_create_screen.dart';
import 'package:car/views/car_update_screen.dart';
import 'package:flutter/material.dart';
import 'models/car_model.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Car CRUD App',
      home: CarListScreen(),
    );
  }
}

class CarListScreen extends StatefulWidget {
  @override
  _CarListScreenState createState() => _CarListScreenState();
}

class _CarListScreenState extends State<CarListScreen> {
  final CarViewModel viewModel = CarViewModel();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Car List'),
      ),
      body: ListView.builder(
        itemCount: viewModel.cars.length,
        itemBuilder: (context, index) {
          final car = viewModel.cars[index];
          return ListTile(
            title: Text(car.modelName),
            subtitle: Text('${car.brand} - \$${car.price}'),
            trailing: IconButton(
              icon: Icon(Icons.delete),
              onPressed: () async {
                final confirm = await showDialog<bool>(
                  context: context,
                  builder: (context) => AlertDialog(
                    title: Text('Delete Car'),
                    content: Text('Are you sure you want to delete this car?'),
                    actions: [
                      TextButton(
                        onPressed: () => Navigator.pop(context, false),
                        child: Text('Cancel'),
                      ),
                      TextButton(
                        onPressed: () => Navigator.pop(context, true),
                        child: Text('Delete'),
                      ),
                    ],
                  ),
                );
                if (confirm == true) {
                  setState(() {
                    viewModel.deleteCar(index);
                  });
                }
              },
            ),
            onTap: () async {
              final updatedCar = await Navigator.push<Car>(
                context,
                MaterialPageRoute(
                  builder: (context) => CarUpdateScreen(car: car),
                ),
              );
              if (updatedCar != null) {
                setState(() {
                  viewModel.updateCar(index, updatedCar);
                });
              }
            },
          );
        },
      ),
      floatingActionButton: FloatingActionButton(
        child: Icon(Icons.add),
        onPressed: () async {
          final newCar = await Navigator.push<Car>(
            context,
            MaterialPageRoute(builder: (context) => CarCreateScreen()),
          );
          if (newCar != null) {
            setState(() {
              viewModel.addCar(newCar);
            });
          }
        },
      ),
    );
  }
}
