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

    public IfStmt(Exp exp,IStmt t, IStmt e) // constructor
    {
        this.expression = exp;
        this.thenS = t;
        this.elseS = e;
    }
    // getters and setters
    public Exp getExpression()
    {
        return expression;
    }

    public void setExpression(Exp expression)
    {
        this.expression = expression;
    }

    public IStmt getThenS()
    {
        return thenS;
    }

    public void setThenS(IStmt thenS)
    {
        this.thenS = thenS;
    }

    public IStmt getElseS()
    {
        return elseS;
    }

    public void setElseS(IStmt elseS) // set the else statement
    {
        this.elseS = elseS;
    }
    public String toString() //if (expression) then (thenS) else (elseS)
    {
        return "(IF("+ expression.toString()+") THEN(" +thenS.toString()
                +")ELSE("+elseS.toString()+"))";
    }

    @Override
    public PrgState execute(PrgState state) throws MyException  // execute the statement
    {
        MyIStack<IStmt> exeStack = state.getExeStack(); // get the execution stack
        MyIDictionary<String, Value> symTable = state.getSymTable(); // get the symbol table
        Value val = expression.evaluate(symTable); // evaluate the expression
        if(!val.getType().equals(new BoolType())) // if the expression is not a boolean
            throw new MyException("Conditional expression is not a boolean");
        else
        {
            BoolValue boolVal = (BoolValue) val;// cast the value to a boolean value
            if(boolVal.getValue())
                exeStack.push(thenS);
            else
                exeStack.push(elseS);
        }
        return state;
    }
}
