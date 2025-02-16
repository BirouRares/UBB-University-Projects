import React, { useState, useEffect } from "react";
import { useNavigate, useParams } from "react-router-dom";
import axios from '../axios';
import './AddEdit.css';
import { toast } from "react-toastify";

const initialState = {
  name: "",
  engine: "",
  price: "",
  owner: ""
};

const AddEdit = () => {
  const [state, setState] = useState(initialState);
  const [owners, setOwners] = useState([]);
  const { name, engine, price, owner } = state;
  const navigate = useNavigate();
  const { id } = useParams();

  const getOwners = async () => {
    try {
      const response = await axios.get("http://localhost:5000/owners");
      if (response.status === 200) {
        setOwners(response.data.response);
      }
    } catch (error) {
      console.error("Error fetching owners data:", error);
      toast.error("An error occurred while fetching owners data");
    }
  };

  const getSingleCar = async (id) => {
    try {
      const response = await axios.post("http://localhost:5000/showCar", { carID: id });
      if (response.status === 200) {
        setState(response.data.response);
      }
    } catch (error) {
      console.error("Error fetching car data:", error);
      toast.error("An error occurred while fetching car data");
    }
  };

  useEffect(() => {
    getOwners();
    if (id) {
      getSingleCar(id);
    }
  }, [id]);

  const addCar = async (data) => {
    try {
      const response = await axios.post("http://localhost:5000/storeCar", data);
      if (response.status === 200) {
        toast.success(response.data.message);
      }
    } catch (error) {
      console.error("Error adding car:", error);
      toast.error("Error adding car");
    }
  };

  const updateCar = async (data) => {
    try {
      const response = await axios.post("http://localhost:5000/updateCar", { carID: id, ...data });
      if (response.status === 200) {
        toast.success(response.data.message);
      }
    } catch (error) {
      console.error("Error updating car:", error);
      toast.error("Error updating car");
    }
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    if (!name || !engine || !price || !owner) {
      toast.error("Please fill in all fields");
    } else {
      if (!id) {
        addCar(state);
      } else {
        updateCar(state);
      }
      setTimeout(() => navigate('/'), 500);
    }
  };

  const handleInputChange = (e) => {
    const { name, value } = e.target;
    setState({ ...state, [name]: value });
  };

  const handleInputChangeInt = (e) => {
    const { name, value } = e.target;
    setState({ ...state, [name]: parseInt(value) });
  };

  return (
    <div style={{ marginTop: "100px" }}>
      <form style={{ marginTop: "auto", padding: "15px", maxWidth: "400px", alignContent: "center" }} onSubmit={handleSubmit}>
        <label htmlFor="name">Name</label>
        <input type="text" id="name" name="name" placeholder="Enter Car Name" onChange={handleInputChange} value={name} />

        <label htmlFor="engine">Engine</label>
        <input type="text" id="engine" name="engine" placeholder="Engine" onChange={handleInputChange} value={engine} />

        <label htmlFor="price">Price</label>
        <input type="number" id="price" name="price" placeholder="Price" onChange={handleInputChangeInt} value={price} />

        <label htmlFor="owner">Owner</label>
        <select id="owner" name="owner" onChange={handleInputChange} value={owner}>
          <option value="">Select Owner</option>
          {owners.map((owner) => (
            <option key={owner._id} value={owner._id}>
              {owner.name}
            </option>
          ))}
        </select>

        <input type="submit" value={id ? "Update" : "Add"} />
      </form>
    </div>
  );
};

export default AddEdit;
