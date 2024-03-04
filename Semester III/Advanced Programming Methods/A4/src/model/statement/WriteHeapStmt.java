package model.statement;
import model.adt.*;
import model.MyException;
import model.PrgState;
import model.type.Type;
import model.value.Value;
import model.expression.*;
import model.type.BoolType;
import model.value.BoolValue;
import model.type.RefType;
import model.value.RefValue;


import java.util.Objects;

public class WriteHeapStmt implements IStmt
{
    private String variableName;
    private Exp expression;
    public WriteHeapStmt(String variableName, Exp expression){
        this.variableName = variableName;
        this.expression = expression;
    }
    public String getVariableName(){
        return this.variableName;
    }
    public Exp getExpression(){
        return this.expression;
    }
    public void setVariableName(String variableName){
        this.variableName = variableName;
    }
    public void setExpression(Exp expression){
        this.expression = expression;
    }

    @Override
    public String toString(){
        return "Write heap(" + this.variableName + ", " + this.expression.toString() + ")";
    }


    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyIHeap<Integer,Value> heap = state.getHeap();

        Value variableValue = null;
        variableValue = symTable.lookup(this.variableName);
        if(variableValue == null){
            throw new MyException("Variable " + this.variableName + " not declared!");
        }
        if(!(variableValue instanceof RefValue)){
            throw new MyException("Variable " + this.variableName + " is not a reference!");
        }
        RefValue variableRefValue = (RefValue)variableValue;
        int heapAddress = variableRefValue.getAddress();
        if(heap.get(heapAddress) == null){
            throw new MyException("Address " + heapAddress + " not allocated!");
        }
        Value expressionValue = this.expression.eval(symTable, heap);
        if (!expressionValue.getType().equals(variableRefValue.getLocationType())){
            throw new MyException("Expression type and variable type do not match!");
        }
        heap.update(heapAddress, expressionValue);
        return null;
    }
}
