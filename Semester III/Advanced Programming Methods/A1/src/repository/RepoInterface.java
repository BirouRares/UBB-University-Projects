package repository;

import exception.MyException;
import model.Vehicles;
public interface RepoInterface
{
    void addVehicle( Vehicles x) throws MyException;
    void deleteVehicle(Vehicles x) throws MyException;
    int getSize();
    Vehicles[] getVehicles();
}
