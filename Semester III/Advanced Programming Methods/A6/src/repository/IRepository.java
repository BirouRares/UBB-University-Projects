package repository;
import model.PrgState;
import java.util.List;
import model.MyException;
public interface IRepository
{
   // void logPrgStateExec() throws MyException;
   public List<PrgState> getPrgList();
   public void setPrgList(List<PrgState> prgList);


    void addPrg(PrgState prg);
    void logPrgStateExec(PrgState program) throws MyException;
}
