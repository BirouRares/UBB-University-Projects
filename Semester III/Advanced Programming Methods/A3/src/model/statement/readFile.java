package model.statement;
import model.adt.*;
import model.MyException;
import model.PrgState;
import model.type.*;
import model.value.*;
import model.expression.*;
import java.io.BufferedReader;
import java.io.IOException;
public class readFile implements IStmt
{
    private Exp exppression;
    private String variable_name;
    public readFile(Exp exppression, String variable_name)
    {
        this.exppression = exppression;
        this.variable_name = variable_name;
    }
    public Exp getExpression()
    {
        return this.exppression;
    }
    public void setVariableName(String variable_name)
    {
        this.variable_name = variable_name;
    }
    public void setExpression(Exp exppression)
    {
        this.exppression = exppression;
    }
    public String getVariableName()
    {
        return this.variable_name;
    }
    @Override
    public String toString()
    {
        return "ReadFileStatement(" +
                "expression=" + this.exppression.toString() +
                ", variable_name=" + this.variable_name +'\'' +
                ')';
    }

    @Override
    public PrgState execute(PrgState state) throws MyException
    {
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyIFileTable<String, BufferedReader> fileTable = state.getFileTable();
        MyIStack<IStmt> stack = state.getExeStack();

        if(symTable.isDefined(variable_name))
        {
            Value value = symTable.lookup(variable_name);
            Type type = value.getType();
            if(type.equals(new IntType()))
            {
                StringValue stringValue = (StringValue)exppression.evaluate(symTable);
                String filename = stringValue.getValue();
                BufferedReader bufferedReader = fileTable.lookup(filename);
                try
                {
                    String line = bufferedReader.readLine();
                    IntValue intValue;
                    if(line == null)
                    {
                        intValue = new IntValue(0);
                    }
                    else
                    {
                        intValue = new IntValue(Integer.parseInt(line));
                    }
                    symTable.update(variable_name, intValue);
                }
                catch(IOException e)
                {
                    throw new MyException(e.getMessage());
                }

            }
            else
            {
                throw new MyException("Variable name is not of type int");
            }
        }
        return null;
    }
}
