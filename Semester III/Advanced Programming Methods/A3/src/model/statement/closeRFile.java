package model.statement;
import model.PrgState;
import model.adt.MyIDictionary;
import model.adt.MyIStack;
import model.adt.MyIFileTable;
import model.expression.Exp;
import model.value.Value;
import model.value.StringValue;
import model.MyException;
import model.type.Type;
import model.type.StringType;

import java.io.BufferedReader;
import java.io.IOException;
public class closeRFile implements IStmt
{
    private Exp expression;
    public closeRFile(Exp expression)
    {
        this.expression = expression;
    }
    public Exp getExpression()
    {
        return expression;
    }
    public void setExpression(Exp expression)
    {
        this.expression = expression;
    }
    public String toString() {
        return "closeRFile(" +
                "expression=" + expression +
                ')';
    }

    @Override
    public PrgState execute(PrgState state) throws MyException
    {
        MyIDictionary<String,Value> symbolTable = state.getSymTable();
        MyIFileTable<String, BufferedReader> fileTable = state.getFileTable();
        MyIStack<IStmt> stack = state.getExeStack();


        Value value = expression.evaluate(symbolTable);
        if(value.getType().equals(new StringType()))
        {
            StringValue stringValue = (StringValue)value;
            String filename = stringValue.getValue();
            BufferedReader bufferedReader = fileTable.lookup(filename);
            try
            {
                bufferedReader.close();
            }
            catch (IOException e)
            {
                throw new MyException("File "+filename+" cannot be closed");

            }
            fileTable.remove(filename);
        }
        else
        {
            throw new MyException("Invalid type");
        }
        return null;
    }
}
