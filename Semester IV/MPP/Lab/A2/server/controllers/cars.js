import {v4 as uuid} from "uuid";

let cars = [];

export const getCars = (req, res) => 
{
    res.send(cars);
};

export const createCar = (req, res) => 
{
    const car = req.body;
    cars.push({...car, id: uuid() });
    res.send("Car added successfully");
};


export const getCar = (req, res) => 
{
    const singleCar= cars.filter((car) => car.id === req.params.id);
    res.send(singleCar);
    
};


export const deleteCar = (req, res) => 
{
    cars = cars.filter((car) => car.id !== req.params.id);
    res.send("Car deleted successfully");
};

export const updateCar = (req, res) => 
{
    const car = cars.find((car) => car.id === req.params.id);
    
    car.name = req.body.name;
    car.engine = req.body.engine;
    car.price = req.body.price;
    res.send("Car updated successfully");
};

