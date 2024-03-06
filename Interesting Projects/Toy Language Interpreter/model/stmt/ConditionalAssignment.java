package model.stmt;
import model.ADT.MyIDictionary;
import model.ADT.MyIStack;
import model.MyException;
import model.PrgState;
import model.exp.Exp;
import model.exp.VarExp;
import model.type.BoolType;
import model.type.Type;

public class ConditionalAssignment implements IStmt 
{
    private String value;


    private Exp Expression1;
    private Exp Expression2;
    private Exp Expression3;

    

    public ConditionalAssignment(String v, Exp exp1, Exp exp2, Exp exp3) //just a constructor
    {
        this.value = v;
        this.Expression1 = exp1;
        this.Expression2 = exp2;
        this.Expression3 = exp3;
    }



    @Override
    public PrgState execute(PrgState state) throws MyException 
    {
        MyIStack<IStmt> exeStack = state.getExeStack();
        IStmt converted = new IfStmt(Expression1, new AssignStmt(value, Expression2), new AssignStmt(value, Expression3));
        //create if stmt => if exp1 then value=exp2 else value=exp3
        exeStack.push(converted);// push the stmt on the stack
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException 
    {
        // we evaluate the variable v and the expressions exp1, exp2, exp3
        Type typev = new VarExp(value).typeCheck(typeEnv);
        Type type1 = Expression1.typeCheck(typeEnv);
        Type type2 = Expression2.typeCheck(typeEnv);
        Type type3 = Expression3.typeCheck(typeEnv);
        // exp1 must be of type bool and exp2 and exp3 must have the same type as v
        if (type1.equals(new BoolType()) && type2.equals(typev) && type3.equals(typev))
            return typeEnv;
        else
            throw new MyException("Invalid conditional assignment!");    
    }


    @Override
    public String toString() 
    {
        return "ConditionalAssignment{" +
                "v='" + value + '\'' +
                ", exp1=" + Expression1 +
                ", exp2=" + Expression2 +
                ", exp3=" + Expression3 +
                '}';
    }
}
