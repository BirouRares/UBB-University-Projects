import mongoose from "mongoose";
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

const Owner = mongoose.model('Owner', ownersSchema);
const Car = mongoose.model('Car', carSchema);

export {Owner, Car};