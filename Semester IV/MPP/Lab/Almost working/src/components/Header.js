import React, { useEffect, useState } from "react";
import { Link, useLocation, useNavigate } from "react-router-dom";
import "./Header.css";

const Header = () => {
    const [activeTab, setActiveTab] = useState("Home");
    const location = useLocation();
    const navigate = useNavigate();

    useEffect(() => {
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
        navigate('/login');
    };

    return (
        <div className="header">
            <p className="logo">User Management System</p>
            <div className="header-right">
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
                <p className="logout" onClick={handleLogout}>Logout</p>
            </div>
        </div>
    );
};

export default Header;
