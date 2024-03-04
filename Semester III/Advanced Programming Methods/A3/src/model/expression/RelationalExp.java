package model.expression;

import model.MyException;
import model.adt.MyIDictionary;
import model.type.IntType;
import model.value.BoolValue;
import model.value.IntValue;
import model.value.Value;


public class RelationalExp implements Exp
{
    private Exp Exp1;
    private Exp Exp2;
    int Operand;

    public static final int LESS_THAN = 1;
    public static final int LESS_THAN_OR_EQUAL = 2;
    public static final int GREATER_THAN = 3;
    public static final int GREATER_THAN_OR_EQUAL = 4;
    public static final int EQUAL = 5;
    public static final int NOT_EQUAL = 6;

    public RelationalExp(String stringOperand, Exp firstExpression, Exp secondExpression)
    {
        this.Exp1 = firstExpression;
        this.Exp2 = secondExpression;

        if(stringOperand.equals("<"))
            this.Operand = LESS_THAN;
        else if(stringOperand.equals("<="))
            this.Operand = LESS_THAN_OR_EQUAL;
        else if(stringOperand.equals(">"))
            this.Operand = GREATER_THAN;
        else if(stringOperand.equals(">="))
            this.Operand = GREATER_THAN_OR_EQUAL;
        else if(stringOperand.equals("=="))
            this.Operand = EQUAL;
        else if(stringOperand.equals("!="))
            this.Operand = NOT_EQUAL;

    }
    public Exp getExp1()
    {
        return this.Exp1;
    }
    public Exp getExp2()
    {
        return this.Exp2;
    }
    public int getIntOperand()
    {
        return this.Operand;
    }
    public void setExp1(Exp exp1)
    {
        this.Exp1 = exp1;
    }
    public void setExp2(Exp exp2)
    {
        this.Exp2 = exp2;
    }
    public void setIntOperand(int intOperand)
    {
        this.Operand = intOperand;
    }
    @Override
    public String toString()
    {
        return "RelationalExpressions{"+
                "firstExpression="+ Exp1 +
                ", secondExpression="+ Exp2 +
                ", intOperand="+Operand+
                '}';
    }


    @Override
    public Value evaluate(MyIDictionary<String, Value> symbolTable) throws MyException
    {
        Value firstValue, secondValue;
        firstValue = Exp1.evaluate(symbolTable);
        if(firstValue.getType().equals(new IntType()))
        {
            secondValue = Exp2.evaluate(symbolTable);
            if(secondValue.getType().equals(new IntType()))
            {
                IntValue IntValue1 = (IntValue) firstValue;
                IntValue IntValue2 = (IntValue) secondValue;
                int value1, value2;
                value1 = IntValue1.getVal();
                value2 = IntValue2.getVal();

                if(Operand == LESS_THAN)
                {
                    if(value1 < value2)
                        return new BoolValue(true);
                    else
                        return new BoolValue(false);
                }
                else if(Operand == LESS_THAN_OR_EQUAL)
                {
                    if(value1 <= value2)
                        return new BoolValue(true);
                    else
                        return new BoolValue(false);
                }
                else if(Operand == GREATER_THAN)
                {
                    if(value1 > value2)
                        return new BoolValue(true);
                    else
                        return new BoolValue(false);
                }
                else if(Operand == GREATER_THAN_OR_EQUAL)
                {
                    if(value1 >= value2)
                        return new BoolValue(true);
                    else
                        return new BoolValue(false);
                }
                else if(Operand == EQUAL)
                {
                    if(value1 == value2)
                        return new BoolValue(true);
                    else
                        return new BoolValue(false);
                }
                else if(Operand == NOT_EQUAL)
                {
                    if(value1 != value2)
                        return new BoolValue(true);
                    else
                        return new BoolValue(false);
                }
                else
                    throw new MyException("Invalid operand!");
            }
            else
                throw new MyException("Second operand is not an integer!");

        }
        else
            throw new MyException("First operand is not an integer!");
    }
}
