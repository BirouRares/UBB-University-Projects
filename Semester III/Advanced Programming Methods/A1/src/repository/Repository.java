package repository;

import exception.MyException;
import model.Vehicles;

public class Repository implements RepoInterface
{
    Vehicles[] vehicles;
    int size;

    public Repository()
    {
        size=0;
        vehicles = new Vehicles[100];
    }
    @Override
    public void addVehicle( Vehicles x) throws MyException
    {
        for(int i=0;i<size;i++)
        {
            if(this.vehicles[i]!=null  &&  this.vehicles[i].getName().equals(x.getName()) && this.vehicles[i].getColor().equals(x.getColor()))
            {
                throw new MyException("The vehicle already exists!");
            }
        }
        vehicles[size] = x;
        size++;
    }
    @Override
    public void deleteVehicle(Vehicles x) throws MyException
    {
        boolean ok=false;
        for(int i=0;i<size;i++)
        {
            if(this.vehicles[i]!=null  &&  this.vehicles[i].getName().equals(x.getName()))
            {

                for(int j=i; j<size-1;j++)
                {
                    vehicles[j]=vehicles[j+1];
                }
                vehicles[size-1]=null;
                size--;
                ok=true;
            }
        }
        if(ok==false)
            throw new MyException("The vehicle does not exist!");
    }
    @Override
    public int getSize()
    {
        return size;
    }
    @Override
    public Vehicles[] getVehicles()
    {
        return vehicles;
    }
}
