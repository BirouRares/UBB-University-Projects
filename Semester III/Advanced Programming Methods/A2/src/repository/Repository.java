package repository;
import model.PrgState;
import java.util.List;
public class Repository implements IRepository
{
    private List<PrgState> prgList;  // list of programs
    public Repository(List<PrgState> p)  // constructor
    {
        prgList = p;
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
