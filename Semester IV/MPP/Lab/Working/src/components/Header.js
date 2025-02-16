import React, { useEffect, useState } from 'react';
import { Link, useLocation } from 'react-router-dom';
import './Header.css';

const Header = () => {
    const [activeTab, setActiveTab] = useState("Home");
    const [isAuthenticated, setIsAuthenticated] = useState(false);
    const location = useLocation();

    useEffect(() => {
        const token = localStorage.getItem('token');
        setIsAuthenticated(!!token);

        if (location.pathname === "/") {
            setActiveTab("Home");
        } else if (location.pathname === "/add") {
            setActiveTab("AddCar");
        } else if (location.pathname === "/addOwner") {
            setActiveTab("AddOwner");
        } else if (location.pathname === "/login") {
            setActiveTab("Login");
        } else if (location.pathname === "/register") {
            setActiveTab("Register");
        }
    }, [location]);

    const handleLogout = () => {
        localStorage.removeItem('token');
        setIsAuthenticated(false);
        setActiveTab("Login");
        window.location.href = '/login';
    };

    return (
        <div className="header">
            <p className="logo">User Management System</p>
            <div className="header-right">
                {isAuthenticated ? (
                    <>
                        <Link to="/">
                            <p className={`${activeTab === "Home" ? "active" : ""}`} onClick={() => setActiveTab("Home")}>
                                Home
                            </p>
                        </Link>
                        <Link to="/add">
                            <p className={`${activeTab === "AddCar" ? "active" : ""}`} onClick={() => setActiveTab("AddCar")}>
                                Add Car
                            </p>
                        </Link>
                        <Link to="/addOwner">
                            <p className={`${activeTab === "AddOwner" ? "active" : ""}`} onClick={() => setActiveTab("AddOwner")}>
                                Add Owner
                            </p>
                        </Link>
                        <p onClick={handleLogout} style={{ cursor: 'pointer' }}>
                          Logout
                        </p>

                    </>
                ) : (
                    <>
                        <Link to="/login">
                            <p className={`${activeTab === "Login" ? "active" : ""}`} onClick={() => setActiveTab("Login")}>
                                Login
                            </p>
                        </Link>
                        <Link to="/register">
                            <p className={`${activeTab === "Register" ? "active" : ""}`} onClick={() => setActiveTab("Register")}>
                                Register
                            </p>
                        </Link>
                    </>
                )}
            </div>
        </div>
    );
};

export default Header;
