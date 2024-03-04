package repository;
import model.PrgState;
import java.util.List;
import model.MyException;
public interface IRepository
{
   // void logPrgStateExec() throws MyException;
    public List<PrgState> getPrgList(); // get the list of programs
    PrgState getCrtPrg();  // get the current program
    void addPrg(PrgState program);  // add a program to the list
    void logPrgStateExec(PrgState program) throws MyException;
}
