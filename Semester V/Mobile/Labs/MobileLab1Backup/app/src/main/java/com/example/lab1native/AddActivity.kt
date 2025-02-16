package com.example.lab1native

import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import com.example.lab1native.repository.CarRepository

class AddActivity : AppCompatActivity() {
    private lateinit var carRepository: CarRepository

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_add_car)

        carRepository = CarRepository.getInstance()

        val modelNameInput = findViewById<EditText>(R.id.model_name_input)
        val brandInput = findViewById<EditText>(R.id.brand_input)
        val yearInput = findViewById<EditText>(R.id.year_input)
        val priceInput = findViewById<EditText>(R.id.price_input)
        val availabilityInput = findViewById<EditText>(R.id.availability_input)
        val addButton = findViewById<Button>(R.id.add_new_car_button)

        addButton.setOnClickListener {
            val modelName = modelNameInput.text.toString().trim()
            val brand = brandInput.text.toString().trim()
            val yearString = yearInput.text.toString().trim()
            val priceString = priceInput.text.toString().trim()
            val availabilityStatus = availabilityInput.text.toString().trim()

            if (modelName.isEmpty()) {
                Toast.makeText(this, "Model name cannot be empty", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            if (brand.isEmpty()) {
                Toast.makeText(this, "Brand cannot be empty", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            val year = yearString.toIntOrNull()
            if (year == null || year <= 0) {
                Toast.makeText(this, "Please enter a valid year", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            val price = priceString.toDoubleOrNull()
            if (price == null || price <= 0) {
                Toast.makeText(this, "Please enter a valid price", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            carRepository.addCar(modelName, brand, year, price, availabilityStatus)

            Toast.makeText(this, "Car added successfully", Toast.LENGTH_SHORT).show()
            finish()
        }
    }
}
