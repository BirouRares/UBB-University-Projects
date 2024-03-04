package model.type;

public class StringType implements Type
{
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
    public Value defaultValue()  // return the default value of the type
    {
        return new StringValue("");
    }
}
