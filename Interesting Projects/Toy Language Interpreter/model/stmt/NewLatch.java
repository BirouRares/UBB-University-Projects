package model.stmt;


import model.ADT.IHeap;
import model.ADT.ILatchTable;
import model.ADT.MyIDictionary;
import model.MyException;
import model.PrgState;
import model.exp.Exp;
import model.type.IntType;
import model.type.Type;
import model.value.IntValue;
import model.value.Value;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class NewLatch implements IStmt{
    private String variable;
    private Exp expression;
    private static Lock lock = new ReentrantLock();

    public NewLatch(String var, Exp expression)// just a constructer
    {
        this.variable = var;
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException
    {
        lock.lock();
        MyIDictionary<String, Value> symTable = state.getSymTable();
        IHeap heap = state.getHeap();
        ILatchTable latchTable = state.getLatchTable();
        // evaluate the expression to get its value
        IntValue nb = (IntValue) expression.eval(symTable, heap);
        int number = nb.getVal();
        // we get the free address and put the value in it
        int freeAddress = latchTable.getFree();
        latchTable.put(freeAddress, number);

        if (symTable.isDefined(variable))// if var is defined we update its value
        {
            symTable.update(variable, new IntValue(freeAddress));
        }
        else
        {
            throw new MyException("Var is not defined!");
        }
        lock.unlock();
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException
    {
        // both variables must be of type int
        if (typeEnv.lookup(variable).equals(new IntType()))
        {
            if (expression.typeCheck(typeEnv).equals(new IntType()))
            {
                return typeEnv;
            }
            else {
                throw new MyException("Expression must have type int!");
            }
        }
        else
        {
            throw new MyException("Variabel must be of type int!");
        }
    }

    @Override
    public String toString()
    {
        return "NewLatch(" + variable + ", " + expression + ")";
    }
}
