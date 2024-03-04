package model.statement;
import model.PrgState;
import model.expression.Exp;
import model.type.RefType;
import model.type.Type;
import model.value.RefValue;
import model.value.Value;
import model.MyException;
import java.util.Objects;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;


public class NewStmt implements IStmt
{
    private String variableName;
    private Exp expression;
    public NewStmt(String variableName, Exp expression){
        this.variableName = variableName;
        this.expression = expression;
    }
    public String getVariableName(){
        return this.variableName;
    }
    public Exp getExpression(){
        return this.expression;
    }
    public String toString(){
        return "new(" + this.variableName + ", " + this.expression.toString() + ")";
    }
    public void setVariableName(String variableName){
        this.variableName = variableName;
    }
    public void setExpression(Exp expression){
        this.expression = expression;
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symbolTable = state.getSymTable();
        MyIHeap<Integer,Value> heap = state.getHeap();

        Value value = symbolTable.lookup(this.variableName);
        if(value == null){
            throw new MyException("Variable " + this.variableName + " not declared!");
        }
        if(!(value.getType() instanceof RefType)){
            throw new MyException("Variable " + this.variableName + " is not a reference!");
        }
        Value expressionValue = this.expression.eval(symbolTable, heap);
        Type locationType = ((RefType) value.getType()).getInner();
        if(!expressionValue.getType().equals(locationType)){
            throw new MyException("Expression type and location type do not match!");
        }
        int heapAddress = heap.getFreeAddress();
        heap.put(heapAddress, expressionValue);
        RefValue refValue = (RefValue) value;
        RefValue newRefValue = new RefValue(heapAddress, ((RefType) refValue.getType()).getInner());
        symbolTable.update(this.variableName, newRefValue);
        return null;
    }
}
