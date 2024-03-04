package model;

public abstract class Vehicles {
    private String name;
    private String color;
    public abstract Type getType();

    public void setName(String name)
    {
        this.name = name;
    }
    public String getName()
    {
        return name;
    }
    public void setColor(String color)
    {
        this.color =color;
    }
    public String getColor()
    {
        return color;
    }
}
