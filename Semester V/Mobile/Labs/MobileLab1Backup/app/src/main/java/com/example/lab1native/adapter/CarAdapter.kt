package com.example.lab1native.adapter

import android.annotation.SuppressLint
import android.content.Intent
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.example.lab1native.R
import com.example.lab1native.UpdateActivity
import com.example.lab1native.model.Car

class CarAdapter(private var cars: List<Car>) : RecyclerView.Adapter<CarAdapter.CarViewHolder>() {

    class CarViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
        val modelNameTextView: TextView = itemView.findViewById(R.id.car_model_name)
        val brandTextView: TextView = itemView.findViewById(R.id.car_brand)
        val yearTextView: TextView = itemView.findViewById(R.id.car_year)
        val priceTextView: TextView = itemView.findViewById(R.id.car_price)
        val availabilityStatusTextView: TextView = itemView.findViewById(R.id.car_availability_status)
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): CarViewHolder {
        val view = LayoutInflater.from(parent.context).inflate(R.layout.item_car, parent, false)
        return CarViewHolder(view)
    }

    @SuppressLint("SetTextI18n")
    override fun onBindViewHolder(holder: CarViewHolder, position: Int) {
        val car = cars[position]
        holder.modelNameTextView.text = car.modelName
        holder.brandTextView.text = car.brand
        holder.yearTextView.text = car.year.toString()
        holder.priceTextView.text = "$${car.price}"
        holder.availabilityStatusTextView.text = car.availabilityStatus

        holder.itemView.setOnClickListener {
            val context = holder.itemView.context
            val intent = Intent(context, UpdateActivity::class.java).apply {
                putExtra("CAR_ID", car.id)
            }
            context.startActivity(intent)
        }
    }

    override fun getItemCount(): Int = cars.size

    @SuppressLint("NotifyDataSetChanged")
    fun updateCars(newCars: List<Car>) {
        cars = newCars
        notifyDataSetChanged()
    }
}
