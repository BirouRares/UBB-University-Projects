package controller;
import java.util.*;

import model.adt.MyIList;
import model.value.Value;
import repository.IRepository;
import model.MyException;
import model.PrgState;
import model.adt.MyIStack;
import model.statement.IStmt;
import model.value.Value;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import model.*;
import model.adt.*;
import model.statement.*;
import model.value.*;
public class Controller
{
    private IRepository repository;
    public Controller(IRepository repository) {
        this.repository = repository;
    }
    public IRepository getRepository()
    {
        return repository;
    }
    public void setRepository(IRepository repository) {
        this.repository = repository;
    }
    public List<PrgState> getProgramStates(){
        return repository.getPrgList();
    }

    public MyIList<Value> getOut(PrgState state)
    {
        return state.getOut();
    }

    public List<Integer> getAddressFromSymTable(Collection<Value> symTableValues)
    {
        return symTableValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {RefValue v1 = (RefValue)v; return v1.getAddress();})
                .collect(Collectors.toList());
    }



    private List<Integer> getAddrFromHeap(Collection<Value> heapValues)
    {
        return heapValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {RefValue v1 = (RefValue)v; return v1.getAddress();})
                .collect(Collectors.toList());
    }


    HashMap<Integer, Value> unsafeGarbageCollector(List<Integer> symbolTableAddresses, Map<Integer,Value> heap)
    {
        return heap.entrySet().stream()
                .filter(e->symbolTableAddresses.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue, (v1, v2)->v2, HashMap::new));
    }
    private HashMap<Integer, Value> safeGarbageCollector(List<Integer> symTableAddr, Map<Integer, Value> heap)
    {
        List<Integer> heapAddr = getAddrFromHeap(heap.values());
        return heap.entrySet().stream()
                .filter(e -> (symTableAddr.contains(e.getKey()) || heapAddr.contains(e.getKey())))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue, (v1, v2) -> v2, HashMap::new));
    }

    public PrgState oneStep(PrgState state) throws MyException
    {
        MyIStack<IStmt> exeStack = state.getExeStack();
        if (exeStack.isEmpty()) throw new MyException("prgstate stack is empty");
        IStmt crtStmt = exeStack.pop();
        return crtStmt.execute(state);
    }

    public void allStep() throws MyException

    {
        PrgState prg = repository.getCrtPrg();
        repository.logPrgStateExec(prg);
        while (!prg.getExeStack().isEmpty()) {
            oneStep(prg);
            repository.logPrgStateExec(prg);
            prg.getHeap().setContent(safeGarbageCollector(getAddressFromSymTable(prg.getSymTable().getContent().values()), prg.getHeap().getContent()));
            repository.logPrgStateExec(prg);
        }
    }
    //public void displayPrgState(PrgState state) {
       // System.out.println(state);
   // }
}
