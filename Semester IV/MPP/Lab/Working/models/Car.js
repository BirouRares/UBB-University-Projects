import mongoose from "mongoose";
import bcrypt from 'bcrypt';
const Schema = mongoose.Schema;

const ownersSchema = new Schema({
    name:{
        type:String,
        required:true
    },
    age:{
        type:Number,
        required:true
    }
}, {timestamps:true});

const carSchema = new Schema({
    name:{
        type:String,
        required:true
    },
    engine:{
        type:String,
        required:true
    },
    price:{
        type:Number,
        required:true
    },
    owner:{
        type:Schema.Types.ObjectId,
        ref:'Owner'
    }
}, {timestamps:true});

const userSchema = new Schema({
    username: {
        type: String,
        required: true,
        unique: true
    },
    password: {
        type: String,
        required: true
    }
}, { timestamps: true });

const User = mongoose.model('User', userSchema);

const Owner = mongoose.model('Owner', ownersSchema);
const Car = mongoose.model('Car', carSchema);


export {Owner, Car,User};