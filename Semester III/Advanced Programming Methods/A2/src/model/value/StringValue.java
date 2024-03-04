package model.value;

public class StringValue implements Value
{
    String value;

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
            return ((StringValue) another).getValue().equals(value);
        else
            return false;
    }

    @Override
    public String toString()
    {
        return value;
    }

    @Override
    public Value deepCopy()
    {
        return new StringValue(value);
    }
}
