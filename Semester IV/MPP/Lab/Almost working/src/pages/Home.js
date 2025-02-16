import React, { useState, useEffect } from "react";
import axios from "./axios.js";
import { Link } from "react-router-dom";
import { toast } from "react-toastify";
import "./Home.css";

const ITEMS_PER_PAGE = 5;

const Home = () => {
  const [cars, setCars] = useState([]);
  const [owners, setOwners] = useState([]);
  const [carPage, setCarPage] = useState(1);
  const [ownerPage, setOwnerPage] = useState(1);

  useEffect(() => {
    fetchData();
  }, [carPage, ownerPage]);

  const fetchData = async () => {
    try {
      const carsResponse = await axios.get("http://localhost:5000/cars");
      if (carsResponse.status === 200) {
        setCars(carsResponse.data.response);
      }

      const ownersResponse = await axios.get("http://localhost:5000/owners");
      if (ownersResponse.status === 200) {
        setOwners(ownersResponse.data.response);
      }
    } catch (error) {
      console.error("Error fetching data:", error);
      toast.error("An error occurred while fetching data");
    }
  };

  const onDeleteCar = async (id) => {
    if (window.confirm("Are you sure you want to delete?")) {
      try {
        const response = await axios.post("http://localhost:5000/deleteCar", { carID: id });
        if (response.status === 200) {
          toast.success(response.data.message);
          fetchData();
        }
      } catch (error) {
        console.error("Error deleting car:", error);
        toast.error("An error occurred while deleting the car");
      }
    }
  };

  const onDeleteOwner = async (id) => {
    if (window.confirm("Are you sure you want to delete?")) {
      try {
        const response = await axios.post("http://localhost:5000/deleteOwner", { ownerID: id });
        if (response.status === 200) {
          toast.success(response.data.message);
          fetchData();
        }
      } catch (error) {
        console.error("Error deleting owner:", error);
        toast.error("An error occurred while deleting the owner");
      }
    }
  };

  const renderCars = () => {
    const startIndex = (carPage - 1) * ITEMS_PER_PAGE;
    const endIndex = Math.min(startIndex + ITEMS_PER_PAGE, cars.length);
    return cars.slice(startIndex, endIndex).map((car, index) => (
      <tr key={car._id}>
        <td>{index + startIndex + 1}</td>
        <td>{car.name}</td>
        <td>{car.engine}</td>
        <td>{car.price}</td>
        <td>{car.owner.name}</td>
        <td>
          <Link to={`/update/${car._id}`}>
            <button className="btn btn-edit">Edit</button>
          </Link>
          <button className="btn btn-delete" onClick={() => onDeleteCar(car._id)}>Delete</button>
        </td>
      </tr>
    ));
  };

  const renderOwners = () => {
    const startIndex = (ownerPage - 1) * ITEMS_PER_PAGE;
    const endIndex = Math.min(startIndex + ITEMS_PER_PAGE, owners.length);
    return owners.slice(startIndex, endIndex).map((owner, index) => (
      <tr key={owner._id}>
        <td>{index + startIndex + 1}</td>
        <td>{owner.name}</td>
        <td>{owner.age}</td>
        <td>
          <Link to={`/updateOwner/${owner._id}`}>
            <button className="btn btn-edit">Edit</button>
          </Link>
          <button className="btn btn-delete" onClick={() => onDeleteOwner(owner._id)}>Delete</button>
        </td>
      </tr>
    ));
  };

  const handlePrevCarPage = () => {
    if (carPage > 1) {
      setCarPage(carPage - 1);
    }
  };

  const handleNextCarPage = () => {
    setCarPage(carPage + 1);
  };

  const handlePrevOwnerPage = () => {
    if (ownerPage > 1) {
      setOwnerPage(ownerPage - 1);
    }
  };

  const handleNextOwnerPage = () => {
    setOwnerPage(ownerPage + 1);
  };

  return (
    <div style={{ marginTop: "50px", textAlign: "center"}}>
      <h2>Cars</h2>
      <table className="styled-table">
        <thead>
          <tr>
            <th>No.</th>
            <th>Name</th>
            <th>Engine</th>
            <th>Price</th>
            <th>Owner</th>
            <th>Action</th>
          </tr>
        </thead>
        <tbody>
          {renderCars()}
        </tbody>
      </table>
      <button className="pagination-btn" onClick={handlePrevCarPage} disabled={carPage === 1}>Previous</button>
      <button className="pagination-btn" onClick={handleNextCarPage}>Next</button>


      <h2>Owners</h2>
      <table className="styled-table">
        <thead>
          <tr>
            <th>No.</th>
            <th>Name</th>
            <th>Age</th>
            <th>Action</th>
          </tr>
        </thead>
        <tbody>
          {renderOwners()}
        </tbody>
      </table>
      <button  className="pagination-btn" onClick={handlePrevOwnerPage} disabled={ownerPage === 1}>Previous</button>
      <button  className="pagination-btn" onClick={handleNextOwnerPage}>Next</button>
    </div>
  );
};

export default Home;
