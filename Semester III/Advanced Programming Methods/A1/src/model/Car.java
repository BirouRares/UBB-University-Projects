package model;

public class Car extends Vehicles
{
    public Car(String Name,String Color)
    {
        this.setColor(Color);
        this.setName(Name);
    }
    public Type getType()
    {
        return Type.CAR;
    }
}
