package controller;
import java.util.List;
import model.adt.MyIList;
import model.value.Value;
import repository.IRepository;
import model.MyException;
import model.PrgState;
import model.adt.MyIStack;
import model.statement.IStmt;
public class Controller
{
    private IRepository repository; // the repository field
    public Controller(IRepository repository)
    {
        this.repository = repository;
    }  // constructor
    public IRepository getRepository()
    {
        return repository;
    }  //  getter for the repository field
    public void setRepository(IRepository repository)
    {
        this.repository = repository;
    }  // setter for the repository field
    public List<PrgState> getProgramStates()
    {
        return repository.getPrgList();
    }// getter for the list of programs
    public PrgState oneStep(PrgState state) throws MyException  // execute one step
    {
        MyIStack<IStmt> exeStack = state.getExeStack(); // get the execution stack
        if (exeStack.isEmpty()) throw new MyException("prgstate stack is empty"); // if the stack is empty throw an exception
        IStmt crtStmt = exeStack.pop(); // get the current statement
        return crtStmt.execute(state);  // execute the current statement
    }

    public void allStep() throws MyException // execute all steps
    {

        PrgState prg = repository.getCrtPrg();// get the current program
        //displayPrgState(prg);
        repository.logPrgStateExec(prg);
        while (!prg.getExeStack().isEmpty())  // while the execution stack is not empty
        {
            oneStep(prg);
            //displayPrgState(prg);
            repository.logPrgStateExec(prg);
        }
    }
    public MyIList<Value> getOutput(PrgState state)
    {
        return state.getOut();
    }
    public void displayPrgState(PrgState state)  // print the current program
    {
        System.out.println(state);
    }

    private void printTitles()
    {
        PrgState programState = repository.getCrtPrg();
        System.out.print("------------------------------------------------------\n");

        System.out.print("*****ExecutionStack*****\n");
        System.out.print(programState.getExeStack().toString() + "\n");

        System.out.print("*****OutputList*****\n");
        System.out.print(programState.getOut() + "\n");

        System.out.print("*****SymbolTable*****\n");
        System.out.print(programState.getSymTable().toString() + "\n");


        System.out.print("*****FileTable*****\n");
        System.out.print(programState.getFileTable().toString() + "\n");

        System.out.print("------------------------------------------------------\n");
    }
}
