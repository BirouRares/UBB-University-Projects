import React, { useState, useEffect } from "react";
import { useNavigate, useParams } from "react-router-dom";
import axios from "axios";
import './AddEdit.css';
import { toast } from "react-toastify";

const initialState = {
  name: "",
  age: ""
};

const AddEditOwner = () => {
  const [state, setState] = useState(initialState);
  const { name, age } = state;
  const navigate = useNavigate();
  const { id } = useParams();

  const getSingleOwner = async (id) => {
    try {
      const response = await axios.post("http://localhost:5000/showOwner", { ownerID: id });
      if (response.status === 200) {
        setState(response.data.response);
      }
    } catch (error) {
      console.error("Error fetching owner data:", error);
      toast.error("Error fetching owner data");
    }
  };

  useEffect(() => {
    if (id) {
      getSingleOwner(id);
    }
  }, [id]);

  const addOwner = async (data) => {
    try {
      const response = await axios.post("http://localhost:5000/storeOwner", data);
      if (response.status === 200) {
        toast.success(response.data.message);
      }
    } catch (error) {
      console.error("Error adding owner:", error);
      toast.error("Error adding owner");
    }
  };

  const updateOwner = async (data) => {
    try {
      const response = await axios.post("http://localhost:5000/updateOwner", { ownerID: id, ...data });
      if (response.status === 200) {
        toast.success(response.data.message);
      }
    } catch (error) {
      console.error("Error updating owner:", error);
      toast.error("Error updating owner");
    }
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    if (!name || !age) {
      toast.error("Please fill in all fields");
    } else {
      if (!id) {
        addOwner(state);
      } else {
        updateOwner(state);
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
        <input type="text" id="name" name="name" placeholder="Enter Owner Name" onChange={handleInputChange} value={name} />

        <label htmlFor="age">Age</label>
        <input type="number" id="age" name="age" placeholder="Age" onChange={handleInputChangeInt} value={age} />

        <input type="submit" value={id ? "Update" : "Add"} />
      </form>
    </div>
  );
};

export default AddEditOwner;
