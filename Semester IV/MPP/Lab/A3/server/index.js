import express from 'express';
import mongoose from 'mongoose';
import morgan from 'morgan';
import bodyParser from 'body-parser';
import CarRouter from './routers/car.js';
import cors from 'cors';


mongoose.connect('mongodb://localhost:27017/MPP', {
  useNewUrlParser: true,
  useUnifiedTopology: true
});

const db = mongoose.connection;
const app = express();
app.use(cors());

db.on('error', (err) => {
  console.log(err); 
});
db.once('open', () => {
  console.log('Database Connection Established!');
});

app.use(morgan('dev'));
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

app.listen(5000, () => {
  console.log('Server is running on port 5000');
});


app.use('/', CarRouter)
