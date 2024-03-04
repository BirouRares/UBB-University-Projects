package model.statement;
import model.adt.*;
import model.MyException;
import model.PrgState;
import model.type.Type;
import model.value.Value;
public class VarDeclStmt implements IStmt
{
    private String name;
    private Type type;
    public VarDeclStmt(String name, Type type)
    {
        this.name = name;
        this.type = type;
    }
    // getters and setters
    public String getName()
    {
        return name;
    }
    public void setName(String name)
    {
        this.name = name;
    }

    public Type getType()
    {
        return type;
    }
    public void setType(Type type)
    {
        this.type = type;
    }
    @Override
    public String toString()
    {
        return type.toString() + " " + name;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException // execute the statement
    {
        MyIStack<IStmt> exeStack = state.getExeStack(); // get the execution stack
        MyIDictionary<String, Value> symTable = state.getSymTable(); // get the symbol table
        if(symTable.isDefined(name)) // if the variable is already defined
        {
            throw new MyException("Variable already declared");
        }
        else
        {
            symTable.add(name, type.defaultValue()); // add the variable to the symbol table
        }
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        typeEnv.add(name, type);
        return typeEnv;
    }
}

