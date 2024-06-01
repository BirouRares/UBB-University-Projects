import express from 'express';
import mongoose from 'mongoose';
import morgan from 'morgan';
import bodyParser from 'body-parser';
import CarRouter from './routers/car.js';
import cors from 'cors';
import AuthRouter from './routers/user.js';
import http from 'http'; 
import dotenv from 'dotenv'; 

const mongoURI = "mongodb+srv://a:a@cluster0.qj8oc4y.mongodb.net/";
mongoose.connect(mongoURI, {
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


const PORT = 5000;
const server = http.createServer(app);
server.listen(PORT, () => {
    console.log('Server is running on port ${PORT}');
});

app.use('/', CarRouter);
app.use('/api', AuthRouter );