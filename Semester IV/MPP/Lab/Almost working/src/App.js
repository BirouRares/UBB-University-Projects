import React from 'react';
import { BrowserRouter, Route, Routes } from 'react-router-dom';
import { ToastContainer } from 'react-toastify';
import 'react-toastify/dist/ReactToastify.css';
import "./App.css";
import Home from './pages/Home';
import AddEdit from './pages/AddEdit';
import Header from './components/Header';
import AddEditOwner from './pages/AddEditOwner';
import Login from './pages/Login';
import Register from './pages/Register';
import PrivateRoute from './components/PrivateRoute';

function App() {
    return (
        <BrowserRouter>
            <div className="App">
                <Header />
                <ToastContainer position="top-center" />
                <Routes>
                    <Route path="/login" element={<Login />} />
                    <Route path="/register" element={<Register />} />
                    <Route
                        path="/"
                        element={
                            <PrivateRoute>
                                <Home />
                            </PrivateRoute>
                        }
                    />
                    <Route
                        path="/add"
                        element={
                            <PrivateRoute>
                                <AddEdit />
                            </PrivateRoute>
                        }
                    />
                    <Route
                        path="/addOwner"
                        element={
                            <PrivateRoute>
                                <AddEditOwner />
                            </PrivateRoute>
                        }
                    />
                    <Route
                        path="/update/:id"
                        element={
                            <PrivateRoute>
                                <AddEdit />
                            </PrivateRoute>
                        }
                    />
                    <Route
                        path="/updateOwner/:id"
                        element={
                            <PrivateRoute>
                                <AddEditOwner />
                            </PrivateRoute>
                        }
                    />
                </Routes>
            </div>
        </BrowserRouter>
    );
}

export default App;
