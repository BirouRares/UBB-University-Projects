package com.example.lab1native.repository

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import com.example.lab1native.model.Car
import java.util.UUID

class CarRepository private constructor() {

    private val cars = mutableListOf<Car>()
    private val _carsLiveData = MutableLiveData<List<Car>>(cars)
    val carsLiveData: LiveData<List<Car>> get() = _carsLiveData

    init {
        initializeCars()
    }

    private fun initializeCars() {
        cars.add(Car("1", "Toyota Corolla", "Toyota", 2023, 25000.0, "Available"))
        cars.add(Car("2", "Honda Civic", "Honda", 2023, 23000.0, "Sold"))
        _carsLiveData.value = cars.toList()
    }

    companion object {
        @Volatile
        private var INSTANCE: CarRepository? = null

        fun getInstance(): CarRepository {
            return INSTANCE ?: synchronized(this) {
                INSTANCE ?: CarRepository().also { INSTANCE = it }
            }
        }
    }

    fun addCar(modelName: String, brand: String, year: Int, price: Double, availabilityStatus: String) {
        val car = Car(UUID.randomUUID().toString(), modelName, brand, year, price, availabilityStatus)
        cars.add(car)
        _carsLiveData.value = cars.toList()
    }

    fun deleteCar(id: String) {
        cars.removeAll { it.id == id }
        _carsLiveData.value = cars.toList()
    }

    fun updateCar(id: String, modelName: String, brand: String, year: Int, price: Double, availabilityStatus: String) {
        val carIndex = cars.indexOfFirst { it.id == id }
        if (carIndex != -1) {
            val updatedCar = cars[carIndex].copy(modelName = modelName, brand = brand, year = year, price = price, availabilityStatus = availabilityStatus)
            cars[carIndex] = updatedCar
            _carsLiveData.value = cars.toList()
        }
    }

    fun getAllCars(): List<Car> = cars.toList()
}
