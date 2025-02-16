const axios = require('axios');
const baseURL = 'http://localhost:5000';

describe('API Tests', () => {
  // Test case for the GET /cars endpoint to fetch all cars
  test('GET /cars should return an array of cars', async () => {
    const response = await axios.get(`${baseURL}/cars`);
    expect(response.status).toBe(200);
  });

  // Test case for the POST /cars endpoint to add a new car
  test('POST /cars should add a new car', async () => {
    const newCar = {
      name: 'Test Car',
      engine: 'Test Engine',
      price: 10000,
      owner: "662ace512d6e35dfc34de3d9" // Assuming valid owner ID
    };
    const response = await axios.post(`${baseURL}/storeCar`, newCar);
    expect(response.status).toBe(200);
    expect(response.data.message).toBe('Car added successfully');
  });

  // Test case for the GET /owners endpoint to fetch all owners
  test('GET /owners should return an array of owners', async () => {
    const response = await axios.get(`${baseURL}/owners`);
    expect(response.status).toBe(200);
  });

  // Test case for the POST /owners endpoint to add a new owner
  test('POST /owners should add a new owner', async () => {
    const newOwner = {
      name: 'John Doe',
      age: 30
    };
    const response = await axios.post(`${baseURL}/storeOwner`, newOwner);
    expect(response.status).toBe(200);
    expect(response.data.message).toBe('Owner added successfully');
  });

  // Test case for the PUT /updateOwner endpoint to update an existing owner
test('POST /updateOwner should update an existing owner', async () => {
  const ownerId = "662ace512d6e35dfc34de3d9"; // Assuming valid owner ID
  const updatedOwner = {
    name: 'Updated John Doe',
    age: 35
  };
  const response = await axios.post(`${baseURL}/updateOwner`, { ownerID: ownerId, ...updatedOwner });
  expect(response.status).toBe(200);
  expect(response.data.message).toBe('Owner updated successfully');
});

test('POST /updateCar should update an existing car', async () => {
  const carId = "662ad2bf6fcc0f25910ff7f5"; // Assuming valid car ID
  const updatedCar = {
    name: 'Updated Audi&VW',
    engine: '4000cc',
    price: 50000,
    owner: "662ace512d6e35dfc34de3d9" // Assuming valid owner ID
  };
  const response = await axios.post(`${baseURL}/updateCar`, { carID: carId, ...updatedCar });
  expect(response.status).toBe(200);
  expect(response.data.message).toBe('Car updated successfully');
});

  // Test case for handling invalid endpoint
  test('GET invalid endpoint should return 404', async () => {
    try {
      await axios.get(`${baseURL}/invalid-endpoint`);
    } catch (error) {
      expect(error.response.status).toBe(404);
    }
  });

  // Test case for handling invalid request body for POST /storeCar
  test('POST /storeCar with invalid request body should return 400', async () => {
    try {
      await axios.post(`${baseURL}/storeCar`, {});
    } catch (error) {
      expect(error.response.status).toBe(400);
    }
  });

  // Test case for handling invalid request body for POST /storeOwner
  test('POST /storeOwner with invalid request body should return 400', async () => {
    try {
      await axios.post(`${baseURL}/storeOwner`, {});
    } catch (error) {
      expect(error.response.status).toBe(400);
    }
  });

  // Test case for handling invalid owner ID for DELETE /deleteOwner
  test('POST /deleteOwner with invalid owner ID should return 404', async () => {
    const invalidOwnerId = "invalid-id";
    try {
      await axios.post(`${baseURL}/deleteOwner`, { ownerID: invalidOwnerId });
    } catch (error) {
      expect(error.response.status).toBe(404);
    }
  });
});

// Test case for the GET /carsCountByOwner endpoint to retrieve the number of cars each owner has
test('GET /carsCountByOwner should return the number of cars each owner has', async () => {
  const response = await axios.get(`${baseURL}/carsCountByOwner`);
  expect(response.status).toBe(200);
  expect(Array.isArray(response.data.result)).toBe(true);
  response.data.result.forEach(owner => {
    expect(owner).toHaveProperty('ownerName');
    expect(owner).toHaveProperty('carCount');
    expect(typeof owner.carCount).toBe('number');
  });
});

