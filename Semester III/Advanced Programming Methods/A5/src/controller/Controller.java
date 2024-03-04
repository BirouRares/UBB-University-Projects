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
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import model.*;
import model.adt.*;
import model.statement.*;
import model.value.*;
public class Controller
{
    private IRepository repository;
    private ExecutorService executor;
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

    private List<Integer> getAddrFromSymTable(Collection<Value> symTableValues) {
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
    public void conservativeGarbageCollector(List<PrgState> programStates) {
        List<Integer> symTableAddresses = Objects.requireNonNull(programStates.stream()
                        .map(p -> getAddrFromSymTable(p.getSymTable().values()))
                        .map(Collection::stream)
                        .reduce(Stream::concat).orElse(null))
                .collect(Collectors.toList());
        programStates.forEach(p -> p.getHeap().setContent((HashMap<Integer, Value>) safeGarbageCollector(symTableAddresses, p.getHeap().getContent())));
    }
    private HashMap<Integer, Value> safeGarbageCollector(List<Integer> symTableAddr, Map<Integer, Value> heap)
    {
        List<Integer> heapAddr = getAddrFromHeap(heap.values());
        return heap.entrySet().stream()
                .filter(e -> (symTableAddr.contains(e.getKey()) || heapAddr.contains(e.getKey())))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue, (v1, v2) -> v2, HashMap::new));
    }

    public List<PrgState> removeCompletedPrg(List<PrgState> inPrgList) {
        return inPrgList.stream()
                .filter(p -> p.isNotCompleted())
                .collect(Collectors.toList());
    }

    /*public PrgState oneStep(PrgState state) throws MyException
    {
        MyIStack<IStmt> exeStack = state.getExeStack();
        if (exeStack.isEmpty()) throw new MyException("prgstate stack is empty");
        IStmt crtStmt = exeStack.pop();
        return crtStmt.execute(state);
    }*/
    public void oneStepForAllPrograms(List<PrgState> programList) throws InterruptedException{
        programList.forEach(prg -> {
            try {
                repository.logPrgStateExec(prg);
            } catch (MyException e) {
                throw new RuntimeException(e.getMessage());
            }
        });

        List<Callable<PrgState>> callList = programList.stream()
                .map((PrgState p) -> (Callable<PrgState>)(() -> {return p.oneStep();}))
                .collect(Collectors.toList());

        List<PrgState> newPrgList = executor.invokeAll(callList).stream()
                .map(future -> {
                    try {
                        return future.get();
                    } catch (InterruptedException | ExecutionException e) {
                        throw new RuntimeException(e.getMessage());
                    }
                })
                .filter(p -> p != null)
                .collect(Collectors.toList());
        programList.addAll(newPrgList);
        programList.forEach(prg -> {
            try {
                repository.logPrgStateExec(prg);
            } catch (MyException e) {
                throw new RuntimeException(e.getMessage());
            }
        });
        repository.setPrgList(programList);
    }

    public void allStep() throws InterruptedException {
        executor = Executors.newFixedThreadPool(2);
        List<PrgState> programList = removeCompletedPrg(repository.getPrgList());
        while(programList.size() > 0){
            conservativeGarbageCollector(programList);
            oneStepForAllPrograms(programList);
            programList = removeCompletedPrg(repository.getPrgList());
        }
        executor.shutdownNow();
        repository.setPrgList(programList);
    }
    //public void displayPrgState(PrgState state) {
       // System.out.println(state);
   // }
}
