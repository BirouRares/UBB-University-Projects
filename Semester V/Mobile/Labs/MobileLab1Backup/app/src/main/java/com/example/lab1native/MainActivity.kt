package com.example.lab1native

import android.content.Intent
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.Observer
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.lab1native.adapter.CarAdapter
import com.example.lab1native.repository.CarRepository
import com.google.android.material.floatingactionbutton.FloatingActionButton

@Suppress("DEPRECATION")
class MainActivity : AppCompatActivity() {
    private lateinit var carRepository: CarRepository
    private lateinit var carAdapter: CarAdapter

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        carRepository = CarRepository.getInstance()

        val recyclerView = findViewById<RecyclerView>(R.id.recyclerView)
        carAdapter = CarAdapter(emptyList())
        recyclerView.adapter = carAdapter
        recyclerView.layoutManager = LinearLayoutManager(this)

        carRepository.carsLiveData.observe(this, Observer { cars ->
            carAdapter.updateCars(cars)
        })

        val addButton = findViewById<FloatingActionButton>(R.id.add_button)
        addButton.setOnClickListener {
            val intent = Intent(this, AddActivity::class.java)
            startActivityForResult(intent, ADD_CAR_REQUEST)
        }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if (requestCode == ADD_CAR_REQUEST && resultCode == RESULT_OK) {
            carRepository.carsLiveData.value?.let {
                carAdapter.updateCars(it)
            }
        }
    }

    companion object {
        private const val ADD_CAR_REQUEST = 1
    }
}
