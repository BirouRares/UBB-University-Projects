package model.statement;
import model.adt.*;
import model.MyException;
import model.PrgState;
import model.expression.Exp;
import model.type.Type;
import model.value.Value;
public class AssignStmt implements IStmt
{
    private Exp expression; // expression to be evaluated
    private String id;
    public AssignStmt(String id, Exp exp)
    {  // constructor
        this.expression = exp;
        this.id = id;
    }
    public Exp getExpression()
    {
        return expression;
    }
    public String getId()
    {
        return id;
    }
    public void setExpression(Exp expression)
    {
        this.expression = expression;
    }
    public void setId(String id)
    {
        this.id = id;
    }
    public String toString()
    {
        return id + "=" + expression.toString();
    }

    @Override
    public PrgState execute(PrgState state) throws MyException // execute the statement
    {
        MyIStack<IStmt> exeStack = state.getExeStack();
        MyIDictionary<String, Value> symTable = state.getSymTable();
        if(symTable.isDefined(id))
        {
            Value val = expression.evaluate(symTable);
            Type typId = (symTable.lookup(id)).getType();
            if(val.getType().equals(typId))
                symTable.update(id, val);
            else
                throw new MyException("declared type of variable" + id + " and type of the assigned expression do not match");
        }
        else
            throw new MyException("the used variable" + id + " was not declared before");
        return state;
    }
}
