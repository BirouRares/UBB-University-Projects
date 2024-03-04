package model.statement;
import model.MyException;
import model.PrgState;
public class NopStmt implements IStmt
{
    public NopStmt()    {}  // constructor
    @Override
    public PrgState execute(PrgState state) throws MyException // execute the statement
    {
        return null;
    }
}
