import React, { useState } from 'react';
import axios from './axios';
import { useNavigate } from 'react-router-dom';
import { toast } from 'react-toastify';

const Register = () => {
    const [username, setUsername] = useState('');
    const [password, setPassword] = useState('');
    const navigate = useNavigate();

    const handleSubmit = async (e) => {
        e.preventDefault();
        try {
            const response = await axios.post('http://localhost:5000/api/register', { username, password });
            if (response.status === 201) {
                toast.success('Registration successful! Please log in.');
                navigate('/login');
            }
        } catch (error) {
            toast.error('Registration failed. Please try again.');
        }
    };

    return (
        <div className="auth-container">
            <form onSubmit={handleSubmit}>
                <h2>Register</h2>
                <input type="text" placeholder="Username" value={username} onChange={(e) => setUsername(e.target.value)} required />
                <input type="password" placeholder="Password" value={password} onChange={(e) => setPassword(e.target.value)} required />
                <button type="submit">Register</button>
            </form>
        </div>
    );
};

export default Register;
