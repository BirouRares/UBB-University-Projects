package model.statement;
import model.MyException;
import model.PrgState;
import model.adt.MyIStack;
import model.type.Type;
import model.adt.MyIDictionary;

public class CompStmt implements IStmt
{
    private IStmt first;
    private IStmt second;
    public CompStmt(IStmt v, IStmt v2){
        first=v;
        second =v2;
    }
    public IStmt getFirst() {
        return first;
    }
    public void setFirst(IStmt first) {
        this.first = first;
    }
    public IStmt getSecond() {
        return second;
    }
    public void setSecond(IStmt second) {
        this.second = second;
    }
    public String toString(){
        return "("+first.toString()+";"+ second.toString()+")";
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> exeStack=state.getExeStack();
        exeStack.push(second);
        exeStack.push(first);
        return null;
    }
    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        return second.typecheck(first.typecheck(typeEnv));
    }

}
