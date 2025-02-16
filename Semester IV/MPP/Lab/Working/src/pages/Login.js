import React, { useState } from 'react';
import axios from 'axios';
import { toast } from 'react-toastify';
import { useNavigate } from 'react-router-dom';
import './LoginRegister.css';

const Login = () => {
    const [state, setState] = useState({ username: '', password: '' });
    const navigate = useNavigate();

    const handleInputChange = (e) => {
        const { name, value } = e.target;
        setState({ ...state, [name]: value });
    };

    const handleSubmit = async (e) => {
        e.preventDefault();
        try {
            const response = await axios.post('http://localhost:5000/api/login', state);
            if (response.status === 200) {
                localStorage.setItem('token', response.data.token);
                toast.success('Login successful');
                navigate('/');
            }
        } catch (error) {
            toast.error('Login failed');
        }
    };

    return (
        <div className="form-container">
            <form className="form" onSubmit={handleSubmit}>
                <input className="input" type="text" name="username" placeholder="Username" onChange={handleInputChange} value={state.username} required />
                <input className="input" type="text" name="password" placeholder="Password" onChange={handleInputChange} value={state.password} required />
                <button className="button" type="submit">Login</button>
            </form>
        </div>
    );
};

export default Login;
