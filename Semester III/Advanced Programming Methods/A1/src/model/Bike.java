package model;

public class Bike extends Vehicles
{
    public Bike(String Name,String Color)
    {
        this.setColor(Color);
        this.setName(Name);
    }
    public Type getType()
    {
        return Type.BIKE;
    }
}
