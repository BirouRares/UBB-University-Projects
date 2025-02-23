package model.statement;
import model.adt.*;
import model.MyException;
import model.PrgState;
import model.expression.Exp;
import model.type.BoolType;
import model.value.Value;
import model.value.BoolValue;
public class IfStmt implements IStmt
{
    // if (expression) then (thenS) else (elseS)
    private Exp expression;
    IStmt thenS;
    IStmt elseS;

    public IfStmt(Exp exp,IStmt t, IStmt e)
    {
        this.expression = exp;
        this.thenS = t;
        this.elseS = e;
    }
    public Exp getExpression() {
        return expression;
    }

    public void setExpression(Exp expression) {
        this.expression = expression;
    }

    public IStmt getThenS() {
        return thenS;
    }

    public void setThenS(IStmt thenS) {
        this.thenS = thenS;
    }

    public IStmt getElseS() {
        return elseS;
    }

    public void setElseS(IStmt elseS) {
        this.elseS = elseS;
    }
    public String toString(){
        return "(IF("+ expression.toString()+") THEN(" +thenS.toString()
                +")ELSE("+elseS.toString()+"))";}

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> exeStack = state.getExeStack();
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyIHeap heap = state.getHeap();
        Value val = expression.eval(symTable,heap);
        if(!val.getType().equals(new BoolType()))
            throw new MyException("Conditional expression is not a boolean");
        else{
            BoolValue boolVal = (BoolValue) val;
            if(boolVal.getValue())
                exeStack.push(thenS);
            else
                exeStack.push(elseS);
        }
        return state;
    }
}
