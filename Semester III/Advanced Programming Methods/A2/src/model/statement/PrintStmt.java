package model.statement;
import model.adt.*;
import model.MyException;
import model.PrgState;
import model.expression.Exp;
import model.value.Value;
public class PrintStmt implements IStmt
{
    Exp expression;
    public PrintStmt(Exp givenExpression) // constructor
    {
        expression =givenExpression;}
    public Exp getExpression()
    {
        return expression;
    } // getter
    public void setExpression(Exp expression)
    {
        this.expression = expression;
    }  // setter
    public String toString()
    {
        return "print(" + expression.toString() + ")";
    }  // string representation

    @Override
    public PrgState execute(PrgState state) throws MyException // execute the statement
    {
        MyIStack<IStmt> exeStack = state.getExeStack(); // get the execution stack
        MyIList<Value> out = state.getOut();  // get the output list
        MyIDictionary<String, Value> symTable = state.getSymTable();  // get the symbol table
        out.add(expression.evaluate(symTable));  // add the evaluated expression to the output list
        return state;
    }
}
