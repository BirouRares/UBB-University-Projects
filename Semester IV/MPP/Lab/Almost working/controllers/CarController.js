import { response } from 'express';
import { Car } from '../models/Car.js';
import { Owner } from '../models/Car.js';
import User from '../models/Car.js';
import bcrypt from 'bcrypt';
import jwt from 'jsonwebtoken';
import express from 'express';

const indexCar = (req, res, next) => {
    Car.find()
        .populate('owner', 'name') // Populate the 'owner' field with the 'name' attribute
        .then(response => {
            res.json({ response });
        })
        .catch(err => {
            res.json({ message: 'An error occurred' });
        });
};

const indexOwner= (req,res,next)=>{
    Owner.find().then(response=>{
        res.json({response})    
    }).catch(err=>{
        res.json({message:'An error occured'})
    })
};

const showCar = (req,res,next)=>{
    let carID= req.body.carID;
    Car.findById(carID).then(response=>{
        res.json({response})})
    .catch(err=>{
        res.json({message:'An error occured'})
    })
}

const showOwner = (req,res,next)=>{
    let ownerID= req.body.ownerID;
    Owner.findById(ownerID).then(response=>{
        res.json({response})})
    .catch(err=>{
        res.json({message:'An error occured'})
    })
}

const storeCar = (req,res,next)=>{
    let car = new Car({
        name:req.body.name,
        engine:req.body.engine,
        price:req.body.price,
        owner:req.body.owner
    });
    car.save().then(response=>{
        res.json({message:'Car added successfully'})
    }).catch(err=>{
        res.json({message:'An error occured'})
    })
};

const storeOwner = (req,res,next)=>{
    let owner = new Owner({
        name:req.body.name,
        age:req.body.age
    });
    owner.save().then(response=>{
        res.json({message:'Owner added successfully'})
    }).catch(err=>{
        res.json({message:'An error occured'})
    })
};

const updateCar = (req,res,next)=>{
    let carID= req.body.carID;
    let updatedCar = {
        name:req.body.name,
        engine:req.body.engine,
        price:req.body.price,
        owner:req.body.owner
    };
    Car.findByIdAndUpdate(carID, {$set: updatedCar}).then(response=>{
        res.json({message:'Car updated successfully'})
    }).catch(err=>{
        res.json({message:'An error occured'})
    })
};


const updateOwner = (req,res,next)=>{
    let ownerID= req.body.ownerID;
    let updatedOwner = {
        name:req.body.name,
        age:req.body.age
    };
    Owner.findByIdAndUpdate(ownerID, {$set: updatedOwner}).then(response=>{
        res.json({message:'Owner updated successfully'})
    }).catch(err=>{
        res.json({message:'An error occured'})
    })
};

const destroyCar = (req, res, next) => {
    let carID = req.body.carID;
    Car.deleteOne({ _id: carID }).then(() => {
        res.json({ message: 'Car deleted successfully' });
    }).catch(err => {
        res.json({ message: 'An error occurred' });
    });
};



const destroyOwner = async (req, res, next) => {
    try {
        const ownerID = req.body.ownerID;

        // Check if the owner has associated cars
        const carsCount = await Car.countDocuments({ owner: ownerID });

        if (carsCount > 0) {
            // User has associated cars, prevent deletion
            return res.status(400).json({ message: 'Cannot delete owner because they still have associated cars.' });
        }

        // If the owner has no associated cars, proceed with deletion
        await Owner.deleteOne({ _id: ownerID });
        res.json({ message: 'Owner deleted successfully' });
    } catch (error) {
        console.error('Error deleting owner:', error);
        res.status(500).json({ message: 'An error occurred' });
    }
};


const getCarsCountByOwner = (req, res, next) => {
    Owner.aggregate([
        {
            $lookup: {
                from: "cars",
                localField: "_id",
                foreignField: "owner",
                as: "cars"
            }
        },
        {
            $project: {
                _id: 1,
                name: 1,
                carCount: { $size: "$cars" } 
            }
        },
        {
            $project: {
                ownerName: "$name",
                carCount: { $ifNull: ["$carCount", 0] } 
            }
        }
    ]).then(result => {
        res.json({ result });
    }).catch(err => {
        res.json({ message: 'An error occurred' });
    });
};

const register = async (req, res) => {
    try {
        const { username, password } = req.body;
        const hashedPassword = await bcrypt.hash(password, 10);
        const newUser = new User({ username, password: hashedPassword });
        await newUser.save();
        res.status(201).json({ message: 'User registered successfully' });
    } catch (error) {
        res.status(500).json({ message: 'An error occurred', error });
    }
};

const login = async (req, res) => {
    try {
        const { username, password } = req.body;
        const user = await User.findOne({ username });
        if (!user) return res.status(400).json({ message: 'Invalid credentials' });

        const isMatch = await bcrypt.compare(password, user.password);
        if (!isMatch) return res.status(400).json({ message: 'Invalid credentials' });

        const token = jwt.sign({ id: user._id }, 'your_jwt_secret', { expiresIn: '1h' });
        res.json({ token });
    } catch (error) {
        res.status(500).json({ message: 'An error occurred', error });
    }
};



export  {register, login,getCarsCountByOwner,indexCar, indexOwner, showCar, showOwner, storeCar, storeOwner, updateCar, updateOwner, destroyCar, destroyOwner};