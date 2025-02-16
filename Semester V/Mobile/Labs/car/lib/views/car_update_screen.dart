import 'package:flutter/material.dart';
import '../models/car_model.dart';

class CarUpdateScreen extends StatefulWidget {
  final Car car;

  CarUpdateScreen({required this.car});

  @override
  _CarUpdateScreenState createState() => _CarUpdateScreenState();
}

class _CarUpdateScreenState extends State<CarUpdateScreen> {
  final _formKey = GlobalKey<FormState>();
  late TextEditingController _modelNameController;
  late TextEditingController _brandController;
  late TextEditingController _yearController;
  late TextEditingController _priceController;
  late TextEditingController _statusController;

  @override
  void initState() {
    super.initState();
    _modelNameController = TextEditingController(text: widget.car.modelName);
    _brandController = TextEditingController(text: widget.car.brand);
    _yearController = TextEditingController(text: widget.car.year.toString());
    _priceController = TextEditingController(text: widget.car.price.toString());
    _statusController = TextEditingController(text: widget.car.availabilityStatus);
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Update Car'),
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Form(
          key: _formKey,
          child: Column(
            children: [
              TextFormField(
                controller: _modelNameController,
                decoration: InputDecoration(labelText: 'Model Name'),
                validator: (value) => value == null || value.isEmpty
                    ? 'Model name is required'
                    : null,
              ),
              TextFormField(
                controller: _brandController,
                decoration: InputDecoration(labelText: 'Brand'),
                validator: (value) => value == null || value.isEmpty
                    ? 'Brand is required'
                    : null,
              ),
              TextFormField(
                controller: _yearController,
                decoration: InputDecoration(labelText: 'Year'),
                keyboardType: TextInputType.number,
                validator: (value) =>
                int.tryParse(value ?? '') == null ? 'Valid year is required' : null,
              ),
              TextFormField(
                controller: _priceController,
                decoration: InputDecoration(labelText: 'Price'),
                keyboardType: TextInputType.number,
                validator: (value) =>
                double.tryParse(value ?? '') == null ? 'Valid price is required' : null,
              ),
              TextFormField(
                controller: _statusController,
                decoration: InputDecoration(labelText: 'Availability Status'),
                validator: (value) => value == null || value.isEmpty
                    ? 'Availability status is required'
                    : null,
              ),
              SizedBox(height: 16.0),
              ElevatedButton(
                onPressed: () {
                  if (_formKey.currentState?.validate() ?? false) {
                    final updatedCar = Car(
                      modelName: _modelNameController.text,
                      brand: _brandController.text,
                      year: int.parse(_yearController.text),
                      price: double.parse(_priceController.text),
                      availabilityStatus: _statusController.text,
                    );
                    Navigator.pop(context, updatedCar);
                  }
                },
                child: Text('Update'),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
