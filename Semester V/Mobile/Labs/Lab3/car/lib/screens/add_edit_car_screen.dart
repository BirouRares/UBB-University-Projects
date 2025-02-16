import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../models/car_model.dart';
import '../providers/car_provider.dart';

class AddEditCarScreen extends StatefulWidget {
  final Car? car;
  final int? index;

  const AddEditCarScreen({Key? key, this.car, this.index}) : super(key: key);

  @override
  State<AddEditCarScreen> createState() => _AddEditCarScreenState();
}

class _AddEditCarScreenState extends State<AddEditCarScreen> {
  final _formKey = GlobalKey<FormState>();
  final _modelNameController = TextEditingController();
  final _brandController = TextEditingController();
  final _yearController = TextEditingController();
  final _priceController = TextEditingController();
  String _availabilityStatus = 'Available';

  @override
  void initState() {
    super.initState();
    if (widget.car != null) {
      _modelNameController.text = widget.car!.modelName;
      _brandController.text = widget.car!.brand;
      _yearController.text = widget.car!.year.toString();
      _priceController.text = widget.car!.price.toString();
      _availabilityStatus = widget.car!.availabilityStatus;
    }
  }

  @override
  Widget build(BuildContext context) {
    final carProvider = Provider.of<CarProvider>(context);

    return Scaffold(
      appBar: AppBar(
        title: Text(widget.car == null ? 'Add Car' : 'Edit Car'),
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Form(
          key: _formKey,
          child: ListView(
            children: [
              TextFormField(
                controller: _modelNameController,
                decoration: const InputDecoration(labelText: 'Model Name'),
                validator: (value) =>
                    value == null || value.isEmpty ? 'Enter model name' : null,
              ),
              TextFormField(
                controller: _brandController,
                decoration: const InputDecoration(labelText: 'Brand'),
                validator: (value) =>
                    value == null || value.isEmpty ? 'Enter brand' : null,
              ),
              TextFormField(
                controller: _yearController,
                decoration: const InputDecoration(labelText: 'Year'),
                keyboardType: TextInputType.number,
                validator: (value) =>
                    value == null || int.tryParse(value) == null
                        ? 'Enter a valid year'
                        : null,
              ),
              TextFormField(
                controller: _priceController,
                decoration: const InputDecoration(labelText: 'Price'),
                keyboardType: TextInputType.number,
                validator: (value) =>
                    value == null || double.tryParse(value) == null
                        ? 'Enter a valid price'
                        : null,
              ),
              DropdownButtonFormField(
                value: _availabilityStatus,
                items: const [
                  DropdownMenuItem(value: 'Available', child: Text('Available')),
                  DropdownMenuItem(value: 'Sold', child: Text('Sold')),
                ],
                onChanged: (value) {
                  setState(() {
                    _availabilityStatus = value!;
                  });
                },
                decoration:
                    const InputDecoration(labelText: 'Availability Status'),
              ),
              const SizedBox(height: 20),
              ElevatedButton(
                onPressed: () {
                  if (_formKey.currentState!.validate()) {
                    final car = Car(
                      modelName: _modelNameController.text,
                      brand: _brandController.text,
                      year: int.parse(_yearController.text),
                      price: double.parse(_priceController.text),
                      availabilityStatus: _availabilityStatus,
                    );

                    if (widget.car == null) {
                      carProvider.addCar(car);
                    } else {
                      carProvider.updateCar(widget.index!, car);
                    }

                    Navigator.pop(context);
                  }
                },
                child: Text(widget.car == null ? 'Add' : 'Update'),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
