package model.statement;
import model.adt.MyIStack;
import model.adt.MyStack;
import model.MyException;
import model.PrgState;
import model.type.Type;
import model.adt.MyIDictionary;
//import


public class ForkStmt implements IStmt
{
    private IStmt stmt;

    public ForkStmt(IStmt stmt) {
        this.stmt = stmt;
    }

    public IStmt getStmt() {
        return stmt;
    }

    @Override
    public String toString() {
        return "fork(" + stmt.toString() + ")";
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> newStack = new MyStack<IStmt>();
        return new PrgState(newStack,state.getSymTable().deepCopy(),state.getOut(),state.getFileTable(),stmt,state.getHeap());

    }
    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        stmt.typecheck(typeEnv.deepCopy());
        return typeEnv;
    }
}