package controller;

import exception.MyException;
import repository.RepoInterface;
import repository.Repository;
import model.Vehicles;
import java.util.ArrayList;
import java.util.List;
public class Controller
{
    private RepoInterface repository;
    public Controller(RepoInterface repository)
    {
        this.repository=repository;
    }
    public void addToRepo(Vehicles x)
    {
        try
        {
            repository.addVehicle(x);
        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
        }
    }
    public void removeFromRepo(Vehicles x) throws MyException
    {
        try
        {
            repository.deleteVehicle(x);
        }
        catch (Exception e)
        {
            //System.out.println(e.getMessage());
            throw new MyException(e.getMessage());
        }
    }
    public Vehicles[] getAll()
    {
        return repository.getVehicles();
    }
    public List<Vehicles> filterRepo(String color)
    {
        List<Vehicles> result = new ArrayList<>();
        Vehicles[] all = repository.getVehicles();
        for(int i = 0; i < repository.getSize(); i++)
        {
            Vehicles item = all[i];
            if(item.getColor().equals(color))
                result.add(item);
        }
        return result;
    }
}
