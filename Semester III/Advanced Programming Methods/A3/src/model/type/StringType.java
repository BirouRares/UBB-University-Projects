package model.type;
import model.value.StringValue;
import model.value.Value;

public class StringType implements Type
{
    @Override
    public boolean equals(Object another) // check if two objects are equal
    {
        return another instanceof StringType;
    }

    @Override
    public String toString()
    {
        return "string";
    }  // return the string representation of the type
    @Override
    public Value defaultValue()
    {
        return new model.value.StringValue("");
    }
}
