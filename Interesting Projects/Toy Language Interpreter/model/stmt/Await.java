package model.stmt;
import model.ADT.ILatchTable;
import model.ADT.MyIDictionary;
import model.MyException;
import model.PrgState;
import model.type.IntType;
import model.type.Type;
import model.value.IntValue;
import model.value.Value;
import view.Interpreter;
import java.util.ArrayList;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Await implements IStmt
{
    //Causes the current thread to wait until the latch has counted down to 0
    private String variable; //a variable from SymTable which is mapped to a number into the LatchTable
    private static Lock lock = new ReentrantLock(); // we need a lock for the await statement

    public Await(String var)// just a constructor
    {
        this.variable = var;
    }


    @Override
    public PrgState execute(PrgState state) throws MyException
    {
        lock.lock(); // we lock the await statement using the lock from java.util.concurrent.locks
        MyIDictionary<String, Value> symTable = state.getSymTable();
        ILatchTable latchTable = state.getLatchTable();

        if (symTable.isDefined(variable)) // if the variable is defined
        {
            IntValue index = (IntValue) symTable.lookup(variable);// look up for an index

            int foundIndex = index.getVal();
            if (latchTable.containsKey(foundIndex))
            {
                if (latchTable.get(foundIndex) != 0)//if the index is different from 0
                {
                    state.getExeStack().push(this);//push the statement again on the stack
                }//we must wait until the index becomes 0
            }
            else //if we did not find the index
            {
                throw new MyException("Index not found!");
            }
        }
        else // the variable is not defined
        {
            throw new MyException("Variable not defined!");
        }
        lock.unlock();// we unlock the await statement
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException
    {
        if (typeEnv.lookup(variable).equals(new IntType()))  // we check if the variable is of type int
        {
            return typeEnv;
        }
        else
        {
            throw new MyException("Variable must be of type int!");
        }
    }

    @Override
    public String toString() {
        return "Await(" + variable + ")";
    }
}
