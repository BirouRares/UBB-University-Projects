package model.type;
import model.value.Value;
import model.value.BoolValue;
public class BoolType implements Type
{
    @Override
    public Value defaultValue()
    {
        return new BoolValue(false);
    } // return the default value of the type

    @Override
    public boolean equals(Object another)
    {
        return another instanceof BoolType;
    }  // check if two objects are equal

    @Override
    public String toString()
    {
        return "boolean";
    }  // return the string representation of the type
}
