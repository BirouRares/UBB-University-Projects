package model;
import model.adt.*;
import model.statement.IStmt;
import model.value.Value;
import java.io.BufferedReader;
import java.io.IOException;
import model.adt.MyIFileTable;
import model.adt.MyIList;
import model.adt.MyIDictionary;
import model.adt.MyIStack;
import model.adt.MyIHeap;
import model.statement.IStmt;
import model.value.Value;
import java.io.BufferedReader;

import java.io.BufferedReader;

public class PrgState
{
    MyIStack<IStmt> exeStack;
    MyIDictionary<String, Value> symTable;
    MyIList<Value> out;
    MyIFileTable<String, BufferedReader> fileTable;
    IStmt originalProgram; //optional field, but good to have
    MyIHeap<Integer,Value> heap;
    private int id;
    private static int idCounter = 0;
    public PrgState(MyIStack<IStmt> stk, MyIDictionary<String, Value> symtbl, MyIList<Value> ot,MyIFileTable<String,BufferedReader> fileTable ,IStmt prg,MyIHeap<Integer,Value> heap){
        exeStack=stk;
        symTable=symtbl;
        out = ot;
        this.heap = heap;
        originalProgram=prg;
        this.fileTable = fileTable;
        id = setFreeAddress();
        stk.push(prg);
    }

    @Override
    public String toString() {
        return "ID: " + id + "\n" +
                "PrgState{" +
                "exeStack=" + exeStack +
                ", symTable=" + symTable +
                ", out=" + out +
                ", fileTable=" + fileTable +
                ", heap=" + heap +
                '}';
    }
    public int getId() {
        return id;
    }
    public int setFreeAddress(){
        idCounter++;
        return idCounter;
    }
    public MyIHeap<Integer,Value> getHeap() {
        return heap;
    }
    public MyIStack<IStmt> getExeStack() {
        return exeStack;
    }
    public MyIDictionary<String, Value> getSymTable() {
        return symTable;
    }
    public MyIList<Value> getOut() {
        return out;
    }
    public MyIFileTable<String, BufferedReader> getFileTable() {
        return fileTable;
    }

    public void setHeap(MyIHeap<Integer,Value> heap) {
        this.heap = heap;
    }
    public void setFileTable(MyIFileTable<String, BufferedReader> fileTable) {
        this.fileTable = fileTable;
    }
    public void setExeStack(MyIStack<IStmt> exeStack) {
        this.exeStack = exeStack;
    }

    public void setSymTable(MyIDictionary<String, Value> symTable) {
        this.symTable = symTable;
    }
    public void setOut(MyIList<Value> out) {
        this.out = out;
    }

    public PrgState oneStep() throws Exception {
        if(exeStack.isEmpty()) throw new Exception("Program state stack is empty");
        IStmt crtStmt = exeStack.pop();
        return crtStmt.execute(this);
    }
    public IStmt getOriginalProgram()
    {
        return originalProgram;
    }
    public boolean isNotCompleted(){
        return !exeStack.isEmpty();
    }
}
