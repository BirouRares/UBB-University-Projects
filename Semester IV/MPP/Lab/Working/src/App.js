// App.js
import React from 'react';
import { BrowserRouter, Route, Routes, Navigate } from 'react-router-dom';
import { ToastContainer } from 'react-toastify';
import 'react-toastify/dist/ReactToastify.css';
import './App.css';
import Home from './pages/Home';
import AddEdit from './pages/AddEdit';
import Header from './components/Header';
import AddEditOwner from './pages/AddEditOwner';
import Login from './pages/Login';
import Register from './pages/Register';
import ProtectedRoute from './components/PrivateRoute';

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
                        path="*"
                        element={<Navigate to="/login" />}
                    />
                    <Route
                        path="/"
                        element={
                            <ProtectedRoute>
                                <Home />
                            </ProtectedRoute>
                        }
                    />
                    <Route
                        path="/add"
                        element={
                            <ProtectedRoute>
                                <AddEdit />
                            </ProtectedRoute>
                        }
                    />
                    <Route
                        path="/addOwner"
                        element={
                            <ProtectedRoute>
                                <AddEditOwner />
                            </ProtectedRoute>
                        }
                    />
                    <Route
                        path="/update/:id"
                        element={
                            <ProtectedRoute>
                                <AddEdit />
                            </ProtectedRoute>
                        }
                    />
                    <Route
                        path="/updateOwner/:id"
                        element={
                            <ProtectedRoute>
                                <AddEditOwner />
                            </ProtectedRoute>
                        }
                    />
                </Routes>
            </div>
        </BrowserRouter>
    );
}

export default App;
