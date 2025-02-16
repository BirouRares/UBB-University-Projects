import { response } from 'express';
import { Car } from '../models/Car.js';
import { Owner } from '../models/Car.js';


const indexCar= (req,res,next)=>{
    Car.find().then(response=>{
        res.json({response})    
}).catch(err=>{
    res.json({message:'An error occured'})
})
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



const destroyOwner = (req, res, next) => {
    let ownerID = req.body.ownerID;
    Owner.deleteOne({ _id: ownerID }).then(() => {
        res.json({ message: 'Owner deleted successfully' });
    }).catch(err => {
        res.json({ message: 'An error occurred' });
    });
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

export  {getCarsCountByOwner,indexCar, indexOwner, showCar, showOwner, storeCar, storeOwner, updateCar, updateOwner, destroyCar, destroyOwner};