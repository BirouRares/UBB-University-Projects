package model.expression;
import model.adt.MyIDictionary;
import model.MyException;
import model.type.Type;
import model.value.Value;
public class VarExp implements Exp
{
    private String id;
    public VarExp(String i)
    {
        id=i;
    }
    public String getId()
    {
        return id;
    }
    public String setId(String i)
    {
        return id=i;
    }
    public String toString()
    {
        return "VarExp{" +
                "id='" + id + '\'' +
                '}';
    }

    @Override
    public Value evaluate(MyIDictionary<String, Value> tbl) throws MyException
    {
        return tbl.lookup(id);
    }
}
