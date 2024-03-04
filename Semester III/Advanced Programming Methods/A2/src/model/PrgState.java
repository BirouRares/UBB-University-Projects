package model;
import model.adt.*;
import model.statement.IStmt;
import model.value.Value;
public class PrgState
{
    MyIStack<IStmt> exeStack;  //here the execution stack is a stack of statements
    MyIDictionary<String, Value> symTable;  //here the symbol table is a dictionary of strings and values
    MyIList<Value> out; //here the output is a list of values
    IStmt originalProgram; //optional field, but good to have
    public PrgState(MyIStack<IStmt> stk, MyIDictionary<String, Value> symtbl, MyIList<Value> ot, IStmt prg)  //constructor
    {
        exeStack=stk;
        symTable=symtbl;
        out = ot;
        originalProgram=prg;
        stk.push(prg);
    }

    @Override  // returns the string representation of the program state
    public String toString()
    {
        return "PrgState{" +
                "exeStack=" + exeStack +
                ", symTable=" + symTable +
                ", out=" + out +
                '}';
    }

    public MyIStack<IStmt> getExeStack()
    {
        return exeStack;
    } // getter for the execution stack
    public MyIDictionary<String, Value> getSymTable()
    {
        return symTable;
    }  // getter for the symbol table
    public MyIList<Value> getOut()
    {
        return out;
    }  // getter for the output

    public void setExeStack(MyIStack<IStmt> exeStack)
    {
        this.exeStack = exeStack;
    }  // setter for the execution stack

    public void setSymTable(MyIDictionary<String, Value> symTable)
    {
        this.symTable = symTable;
    }
    public void setOut(MyIList<Value> out)
    {
        this.out = out;
    }
    public boolean isNotCompleted()
    {
        return !exeStack.isEmpty();
    }
    public PrgState oneStep() throws Exception  // execute one step
    {
        if(exeStack.isEmpty()) throw new Exception("Program state stack is empty");
        IStmt crtStmt = exeStack.pop();
        return crtStmt.execute(this);
    }
    public IStmt getOriginalProgram()
    {
        return originalProgram;
    }
}
