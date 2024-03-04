package model.expression;
import model.adt.MyIDictionary;
import model.MyException;
import model.type.Type;
import model.value.Value;
import model.adt.MyIHeap;
public interface Exp
{
    Value eval(MyIDictionary<String,Value> tbl, MyIHeap<Integer, Value> hp) throws MyException;
    //Type typecheck(MyIDictionary<Int,Type> typeEnv) throws MyException;

    Type typecheck(MyIDictionary<String,Type> typeEnv) throws MyException;
}
