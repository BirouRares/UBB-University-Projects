package model.statement;
import model.MyException;
import model.PrgState;
import model.adt.MyIStack;
public class CompStmt implements IStmt
{
    private IStmt first;  //first statement
    private IStmt second; //second statement
    public CompStmt(IStmt v, IStmt v2)
    { //constructor
        first=v;
        second =v2;
    }
    // getters and setters
    public IStmt getFirst()
    {
        return first;
    }
    public void setFirst(IStmt first)
    {
        this.first = first;
    }
    public IStmt getSecond()
    {
        return second;
    }
    public void setSecond(IStmt second)
    {
        this.second = second;
    }
    public String toString() // string representation
    {
        return "("+first.toString()+";"+ second.toString()+")";
    }

    @Override
    public PrgState execute(PrgState state) throws MyException // execute the statement
    {
        MyIStack<IStmt> exeStack=state.getExeStack(); // get the execution stack
        exeStack.push(second); // push the second statement
        exeStack.push(first); // push the first statement
        return state;  //   return the program state
    }
}
