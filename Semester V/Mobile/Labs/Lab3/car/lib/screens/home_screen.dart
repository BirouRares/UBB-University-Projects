import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../providers/car_provider.dart';
import './add_edit_car_screen.dart';

class HomeScreen extends StatelessWidget {
  const HomeScreen({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    final carProvider = Provider.of<CarProvider>(context);

    return Scaffold(
      appBar: AppBar(title: const Text('Car CRUD App')),
      body: ListView.builder(
        itemCount: carProvider.cars.length,
        itemBuilder: (context, index) {
          final car = carProvider.cars[index];
          return ListTile(
            title: Text('${car.brand} ${car.modelName}'),
            subtitle: Text('${car.year} - \$${car.price}'),
            trailing: Text(car.availabilityStatus),
            onTap: () => Navigator.push(
              context,
              MaterialPageRoute(
                builder: (_) => AddEditCarScreen(
                  car: car,
                  index: index,
                ),
              ),
            ),
          );
        },
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () => Navigator.push(
          context,
          MaterialPageRoute(
            builder: (_) => const AddEditCarScreen(),
          ),
        ),
        child: const Icon(Icons.add),
      ),
    );
  }
}
