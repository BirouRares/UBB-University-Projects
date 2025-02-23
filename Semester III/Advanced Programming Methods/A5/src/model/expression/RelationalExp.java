package model.expression;

import model.MyException;
import model.adt.MyIDictionary;
import model.type.IntType;
import model.value.BoolValue;
import model.value.IntValue;
import model.value.Value;
import model.adt.MyIHeap;


public class RelationalExp implements Exp{
    private Exp firstExpression;
    private Exp secondExpression;
    int intOperand;

    public static final int LESS_THAN = 1;
    public static final int LESS_THAN_OR_EQUAL = 2;
    public static final int GREATER_THAN = 3;
    public static final int GREATER_THAN_OR_EQUAL = 4;
    public static final int EQUAL = 5;
    public static final int NOT_EQUAL = 6;

    public RelationalExp(String stringOperand, Exp firstExpression, Exp secondExpression){
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
        switch(stringOperand){
            case "<" -> this.intOperand = LESS_THAN;
            case "<=" -> this.intOperand = LESS_THAN_OR_EQUAL;
            case ">" -> this.intOperand = GREATER_THAN;
            case ">=" -> this.intOperand = GREATER_THAN_OR_EQUAL;
            case "==" -> this.intOperand = EQUAL;
            case "!=" -> this.intOperand = NOT_EQUAL;
        }
    }
    public Exp getFirstExpression(){
        return this.firstExpression;
    }
    public Exp getSecondExpression(){
        return this.secondExpression;
    }
    public int getIntOperand(){
        return this.intOperand;
    }
    public void setFirstExpression(Exp firstExpression){
        this.firstExpression = firstExpression;
    }
    public void setSecondExpression(Exp secondExpression){
        this.secondExpression = secondExpression;
    }
    public void setIntOperand(int intOperand){
        this.intOperand = intOperand;
    }
    @Override
    public String toString()
    {
        return "RelationalExpressions{"+
                "firstExpression="+firstExpression+
                ", secondExpression="+secondExpression+
                ", intOperand="+intOperand+
                '}';
    }


    @Override
    public Value eval(MyIDictionary<String, Value> symbolTable, MyIHeap<Integer,Value> heap) throws MyException {
        Value firstValue, secondValue;
        firstValue = firstExpression.eval(symbolTable,heap);
        if(firstValue.getType().equals(new IntType())){
            secondValue = secondExpression.eval(symbolTable,heap);
            if(secondValue.getType().equals(new IntType())){
                IntValue IntValue1 = (IntValue) firstValue;
                IntValue IntValue2 = (IntValue) secondValue;
                int number1, number2;
                number1 = IntValue1.getVal();
                number2 = IntValue2.getVal();
                switch(intOperand){
                    case LESS_THAN -> {
                        if(number1 < number2)
                            return new BoolValue(true);
                        else
                            return new BoolValue(false);
                    }
                    case LESS_THAN_OR_EQUAL -> {
                        if(number1 <= number2)
                            return new BoolValue(true);
                        else
                            return new BoolValue(false);
                    }
                    case GREATER_THAN -> {
                        if(number1 > number2)
                            return new BoolValue(true);
                        else
                            return new BoolValue(false);
                    }
                    case GREATER_THAN_OR_EQUAL -> {
                        if(number1 >= number2)
                            return new BoolValue(true);
                        else
                            return new BoolValue(false);
                    }
                    case EQUAL -> {
                        if(number1 == number2)
                            return new BoolValue(true);
                        else
                            return new BoolValue(false);
                    }
                    case NOT_EQUAL -> {
                        if(number1 != number2)
                            return new BoolValue(true);
                        else
                            return new BoolValue(false);
                    }
                    default -> throw new MyException("Invalid operand!");
                }

            }
            else throw new MyException("Second operand is not an integer!");

        }
        else throw new MyException("First operand is not an integer!");

    }
}