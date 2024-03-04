package model.value;

import model.type.Type;

public class StringValue implements Value
{
    private String value;

    public StringValue(String value)
    {
        this.value = value;
    }

    public String getValue()
    {
        return value;
    }

    @Override
    public boolean equals(Object another)
    {
        if (another instanceof StringValue)
            return true;
        else
            return false;
    }

    /*@Override
    public String toString()
    {
        return value;
    }

    @Override
    public Value deepCopy()
    {
        return new StringValue(value);
    }*/

    public void setValue(String value)
    {
        this.value = value;
    }
    @Override
    public Type getType()
    {
        return new model.type.StringType();
    }  // return the type of the value
}
