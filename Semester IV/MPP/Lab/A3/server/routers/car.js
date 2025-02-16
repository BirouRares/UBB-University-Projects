import express from 'express';
import { Router } from 'express';
import * as CarController from '../controllers/CarController.js';


const router = Router();

router.get('/cars', CarController.indexCar);
router.get('/owners', CarController.indexOwner);
router.post('/showCar', CarController.showCar);
router.post('/showOwner', CarController.showOwner);
router.post('/storeCar', CarController.storeCar);
router.post('/storeOwner', CarController.storeOwner);
router.post('/updateCar', CarController.updateCar);  
router.post('/updateOwner', CarController.updateOwner);
router.post('/deleteCar', CarController.destroyCar);
router.post('/deleteOwner', CarController.destroyOwner);
router.get('/carsCountByOwner', CarController.getCarsCountByOwner);

export default router;
