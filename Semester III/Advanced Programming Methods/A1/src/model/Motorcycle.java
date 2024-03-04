package model;

public class Motorcycle extends Vehicles
{
    public Motorcycle(String Name,String Color)
    {
        this.setColor(Color);
        this.setName(Name);
    }
    public Type getType()
    {
        return Type.MOTORCYCLE;
    }
}
