import express from 'express';
import * as CarController from '../controllers/CarController.js';
import auth from '../controllers/auth.js';

const router = express.Router();

router.get('/cars', auth, CarController.indexCar);
router.get('/owners', auth, CarController.indexOwner);
router.post('/showCar', auth, CarController.showCar);
router.post('/showOwner', auth, CarController.showOwner);
router.post('/storeCar', auth, CarController.storeCar);
router.post('/storeOwner', auth, CarController.storeOwner);
router.post('/updateCar', auth, CarController.updateCar);
router.post('/updateOwner', auth, CarController.updateOwner);
router.post('/deleteCar', auth, CarController.destroyCar);
router.post('/deleteOwner', auth, CarController.destroyOwner);
router.get('/carsCountByOwner', auth, CarController.getCarsCountByOwner);

export default router;
