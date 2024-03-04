package model.value;
import model.type.Type;
import model.type.IntType;
public class IntValue  implements Value
{
    private int value;
    public IntValue(int val)
    {
        this.value =val;
    }
    public int getVal()
    {
        return this.value;
    }
    public void setVal(int val)
    {
        this.value =val;
    }

    @Override
    public boolean equals(Object obj)
    {
        return obj instanceof IntValue;
    }

    @Override
    public String toString()
    {
        return Integer.toString(this.value);
    }
    @Override
    public Type getType()
    {
        return new IntType();
    }
}
