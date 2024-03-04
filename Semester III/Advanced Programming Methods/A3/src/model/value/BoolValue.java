package model.value;
import model.type.Type;
import model.type.BoolType;
public class BoolValue implements Value
{
    private boolean value;

    public BoolValue(boolean value)
    {
        this.value = value;
    } // constructor

    public boolean getValue()
    {
        return value;
    } // getter

    public void setValue(boolean value)
    {
        this.value = value;
    }   // setter

    @Override
    public Type getType()
    {
        return new BoolType();
    }  // return the type of the value

    @Override
    public String toString()
    {
        return Boolean.toString(value);
    }

    @Override
    public boolean equals(Object another)
    {
        return another instanceof BoolValue;
    } // check if two objects are equal

    public boolean getVal()
    {
        return value;
    }  // getter
}
