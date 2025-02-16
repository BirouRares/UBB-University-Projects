import 'package:flutter/material.dart';

import '../models/car_model.dart';

class CarCreateScreen extends StatefulWidget {
  @override
  _CarCreateScreenState createState() => _CarCreateScreenState();
}

class _CarCreateScreenState extends State<CarCreateScreen> {
  final _formKey = GlobalKey<FormState>();
  final _modelNameController = TextEditingController();
  final _brandController = TextEditingController();
  final _yearController = TextEditingController();
  final _priceController = TextEditingController();
  final _statusController = TextEditingController();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Create Car'),
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
                    final car = Car(
                      modelName: _modelNameController.text,
                      brand: _brandController.text,
                      year: int.parse(_yearController.text),
                      price: double.parse(_priceController.text),
                      availabilityStatus: _statusController.text,
                    );
                    Navigator.pop(context, car);
                  }
                },
                child: Text('Create'),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
