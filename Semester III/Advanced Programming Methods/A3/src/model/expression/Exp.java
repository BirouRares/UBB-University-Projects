package model.expression;
import model.adt.MyIDictionary;
import model.MyException;
import model.type.Type;
import model.value.Value;
public interface Exp
{
    Value evaluate(MyIDictionary<String,Value> symTbl) throws MyException; // evaluates the expression
}
