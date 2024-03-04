package repository;
import model.PrgState;
import model.adt.MyIStack;
import model.MyException;
import model.PrgState;
import model.statement.IStmt;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.List;
import java.io.IOException;
public class Repository implements IRepository
{

    private List<PrgState> prgList;  // list of programs
    private String Path;
    public Repository(List<PrgState> p, String GivenPath)  // constructor
    {
        prgList = p;
        Path=GivenPath;
    }

    public void logPrgStateExec(PrgState program) throws MyException
    {
        try
        {
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(Path, true)));
            logFile.println("##############################");
            logFile.println("-----ExecutionStack-----");
            logFile.println(program.getExeStack().toString());
            logFile.println("-----SymbolTable-----");
            logFile.println(program.getSymTable().toString());
            logFile.println("-----Output-----");
            logFile.println(program.getOut().toString());
            logFile.println("-----FileTable-----");
            logFile.println(program.getFileTable().toString());
            logFile.println("##############################");
            logFile.println("\n");
            logFile.close();
        }
        catch (IOException e)
        {
            throw new MyException("Error!");
        }
    }

    @Override
    public List<PrgState> getPrgList()  // getter for the list of programs
    {
        return this.prgList;
    }

    @Override
    public PrgState getCrtPrg()  // getter for the current program
    {
        return this.prgList.get(0);
    }
    @Override
    public void addPrg(PrgState  program)  // add a program to the list
    {
        this.prgList.add( program);
    }
}
