package com.example.lab1native

import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity
import com.example.lab1native.repository.CarRepository

class UpdateActivity : AppCompatActivity() {
    private lateinit var carRepository: CarRepository
    private lateinit var carId: String

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_update_car)

        carRepository = CarRepository.getInstance()
        carId = intent.getStringExtra("CAR_ID") ?: ""

        val car = carRepository.getAllCars().find { it.id == carId }

        car?.let {
            findViewById<EditText>(R.id.model_name_input2).setText(it.modelName)
            findViewById<EditText>(R.id.brand_input2).setText(it.brand)
            findViewById<EditText>(R.id.year_input2).setText(it.year.toString())
            findViewById<EditText>(R.id.price_input2).setText(it.price.toString())
            findViewById<EditText>(R.id.availability_input2).setText(it.availabilityStatus)
        }

        val updateButton = findViewById<Button>(R.id.update_car_button)
        updateButton.setOnClickListener {
            val modelName = findViewById<EditText>(R.id.model_name_input2).text.toString().trim()
            val brand = findViewById<EditText>(R.id.brand_input2).text.toString().trim()
            val yearString = findViewById<EditText>(R.id.year_input2).text.toString().trim()
            val priceString = findViewById<EditText>(R.id.price_input2).text.toString().trim()
            val availabilityStatus = findViewById<EditText>(R.id.availability_input2).text.toString().trim()

            if (modelName.isEmpty() || brand.isEmpty() || availabilityStatus.isEmpty()) {
                Toast.makeText(this, "All fields are required", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            val year = yearString.toIntOrNull()
            val price = priceString.toDoubleOrNull()
            if (year == null || price == null) {
                Toast.makeText(this, "Please enter valid year and price", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            carRepository.updateCar(carId, modelName, brand, year, price, availabilityStatus)
            Toast.makeText(this, "Car updated successfully", Toast.LENGTH_SHORT).show()
            finish()
        }

        val deleteButton = findViewById<Button>(R.id.delete_car_button)
        deleteButton.setOnClickListener {
            showDeleteConfirmationDialog()
        }
    }

    private fun showDeleteConfirmationDialog() {
        AlertDialog.Builder(this)
            .setTitle("Delete Car")
            .setMessage("Are you sure you want to delete this car?")
            .setPositiveButton("Yes") { _, _ ->
                carRepository.deleteCar(carId)
                Toast.makeText(this, "Car deleted successfully", Toast.LENGTH_SHORT).show()
                finish()
            }
            .setNegativeButton("No", null)
            .show()
    }
}
