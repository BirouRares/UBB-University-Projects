package model.type;
import model.value.Value;
import model.value.IntValue;
public class IntType implements Type
{
    public boolean equals(Object another) // check if two objects are equal
    {
        return another instanceof IntType;
    }

    @Override
    public String toString()
    {
        return "int";
    }  // return the string representation of the type
    @Override
    public Value defaultValue()  // return the default value of the type
    {
        return new IntValue(0);
    }
}
