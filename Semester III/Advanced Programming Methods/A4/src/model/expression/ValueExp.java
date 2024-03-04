package model.expression;
import model.adt.MyIDictionary;
import model.MyException;
import model.type.Type;
import model.value.Value;
import model.adt.MyIHeap;
public class ValueExp implements Exp // implements the expression interface
{
    private Value e;
    public ValueExp(Value e){
        this.e = e;
    }
    public Value getE(){
        return this.e;
    }
    public void setE(Value e){
        this.e = e;
    }
    @Override
    public String toString()
    {
        return "ValueExp{"+
                "e="+e+
                '}';
    }

    @Override
    public Value eval(MyIDictionary<String, Value> tbl, MyIHeap<Integer,Value> heap) throws MyException {
        return e;
    }}
