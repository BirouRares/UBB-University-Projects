import React, { useState } from 'react';
import axios from './axios.js';
import { useNavigate } from 'react-router-dom';
import { toast } from 'react-toastify';

const Login = () => {
    const [username, setUsername] = useState('');
    const [password, setPassword] = useState('');
    const navigate = useNavigate();

    const handleSubmit = async (e) => {
        e.preventDefault();
        try {
            const response = await axios.post('http://localhost:5000/api/login', { username, password });
            if (response.status === 200) {
                localStorage.setItem('token', response.data.token);
                toast.success('Login successful!');
                navigate('/');
            }
        } catch (error) {
            toast.error('Login failed. Please check your credentials.');
        }
    };

    return (
        <div className="auth-container">
            <form onSubmit={handleSubmit}>
                <h2>Login</h2>
                <input type="text" placeholder="Username" value={username} onChange={(e) => setUsername(e.target.value)} required />
                <input type="password" placeholder="Password" value={password} onChange={(e) => setPassword(e.target.value)} required />
                <button type="submit">Login</button>
            </form>
        </div>
    );
};

export default Login;
