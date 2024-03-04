package model.expression;
import model.adt.MyIDictionary;
import model.MyException;
import model.type.Type;
import model.value.Value;
public class ValueExp implements Exp // implements the expression interface
{
    private Value value;
    public ValueExp(Value e)
    {
        this.value = e;
    }
    public Value getE()
    {
        return this.value;
    }
    public void setE(Value e)
    {
        this.value = e;
    }
    @Override
    public String toString() // returns the string representation of the expression
    {
        return "ValueExp{"+
                "e="+value+
                '}';
    }

    @Override
    public Value evaluate(MyIDictionary<String, Value> tbl) throws MyException // returns the value of the expression
    {
        return value;
    }
}
