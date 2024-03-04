package model.statement;
import model.adt.*;
import model.MyException;
import model.PrgState;
import model.type.Type;
import model.value.Value;
import model.expression.*;
import model.type.BoolType;
import model.value.BoolValue;
public class WhileStmt implements IStmt
{
    private IStmt statement;
    private Exp expression;
    public WhileStmt(Exp expression, IStmt statement){
        this.expression = expression;
        this.statement = statement;
    }
    public Exp getExpression()
    {
        return expression;
    }
    public IStmt getStatement(){
        return statement;
    }
    public void setExpression(Exp expression){
        this.expression = expression;
    }
    public void setStatement(IStmt statement){
        this.statement = statement;
    }
    @Override
    public String toString(){
        return "while(" + expression.toString() + ") " + statement.toString();
    }
    @Override
    public PrgState execute(PrgState state) throws MyException{
        MyIStack<IStmt> stack = state.getExeStack();
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyIHeap<Integer,Value> heap = state.getHeap();
        Value value = expression.eval(symTable, heap);
        if (value.getType() instanceof BoolType){
            BoolValue boolValue = (BoolValue)value;
            if (boolValue.getValue()){
                stack.push(this);
                stack.push(statement);
            }
        }
        else
            throw new MyException("Expression is not a boolean");
        return null;
    }


    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException
    {
        Type typexp=expression.typecheck(typeEnv);
        if (typexp.equals(new BoolType())) {
            statement.typecheck(typeEnv.deepCopy());
            return typeEnv;
        }
        else
            throw new MyException("The condition of WHILE has not the type bool");
    }
}
