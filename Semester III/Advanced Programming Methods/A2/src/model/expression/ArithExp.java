package model.expression;
import model.adt.MyIDictionary;
import model.MyException;
import model.type.IntType;
import model.type.Type;
import model.value.IntValue;
import model.value.Value;
public class ArithExp implements Exp
{

    // e1, e2 are the operands, op is the operator
    // op is an integer value, 1 for plus, 2 for minus, etc.
    private Exp e1;
    private Exp e2;
    public static final int ADD = 1;
    public static final int SUBTRACT = 2;
    public static final int MULTIPLY = 3;
    public static final int DIVIDE = 4;
    private int op;
    public ArithExp(String stringOp, Exp e1, Exp e2) // constructor
    {
        this.e1 = e1;
        this.e2 = e2;
        switch(stringOp){
            case "+" -> this.op = ADD;
            case "-" -> this.op = SUBTRACT;
            case "*" -> this.op = MULTIPLY;
            case "/" -> this.op = DIVIDE;
        }
    }
    // getters and setters
    public Exp getE1()
    {
        return this.e1;
    }
    public Exp getE2()
    {
        return this.e2;
    }
    public int getOp()
    {
        return this.op;
    }
    public void setE1(Exp e1)
    {
        this.e1 = e1;
    }
    public void setE2(Exp e2)
    {
        this.e2 = e2;
    }
    public void setOp(int op)
    {
        this.op = op;
    }


    @Override
    public String toString() // returns the string representation of the arithmetic expression
    {
        return "ArithExp{"+
                "e1="+e1+
                ", e2="+e2+
                ", op="+op+
                '}';
    }

    @Override
    public Value evaluate(MyIDictionary<String, Value> symbolTable) throws MyException // evaluates the arithmetic expression
    {
        Value leftValue, rightValue; // left and right values
        leftValue = e1.evaluate(symbolTable); // evaluate the left expression

        if (leftValue.getType().equals(new IntType()))  // if the left value is an integer
        {
            rightValue = e2.evaluate(symbolTable); // evaluate the right expression

            if (rightValue.getType().equals(new IntType()))  // if the right value is an integer
            {
                IntValue intValue1 = (IntValue) leftValue;
                IntValue intValue2 = (IntValue) rightValue;
                int leftIntValue, rightIntValue;
                leftIntValue = intValue1.getVal();
                rightIntValue = intValue2.getVal();// get the integer values of the left and right values

                if (op == ArithExp.ADD)
                {
                    return new IntValue(leftIntValue + rightIntValue);
                }
                if (op == ArithExp.SUBTRACT)
                {
                    return new IntValue(leftIntValue - rightIntValue);
                }
                if (op == ArithExp.MULTIPLY)
                {
                    return new IntValue(leftIntValue * rightIntValue);
                }
                if (op == ArithExp.DIVIDE)
                {
                    if (rightIntValue == 0)
                    {
                        throw new MyException("division by zero");
                    }
                    else
                    {
                        return new IntValue(leftIntValue / rightIntValue);
                    }
                }
            }
            else
            {
                throw new MyException("second operand is not an integer");
            }
        }
        else
        {
            throw new MyException("first operand is not an integer");
        }

        return null;
    }
}
