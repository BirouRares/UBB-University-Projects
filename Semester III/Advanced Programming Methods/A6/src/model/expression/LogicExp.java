package model.expression;
import model.adt.MyIDictionary;
import model.MyException;
import model.value.Value;
import model.type.Type;
import model.adt.MyIHeap;
import model.value.BoolValue;
import model.type.BoolType;
public class LogicExp implements Exp{
    Exp e1;
    Exp e2;
    public static final int AND = 1;
    public static final int OR = 2;

    int op; // 1-and, 2-or
    public LogicExp(String stringOp, Exp e1, Exp e2){
        this.e1 = e1;
        this.e2 = e2;
        switch(stringOp){
            case "&&" -> this.op = AND;
            case "||" -> this.op = OR;
        }
    }

    public Exp getE1(){
        return this.e1;
    }
    public Exp getE2(){
        return this.e2;
    }
    public int getOp(){
        return this.op;
    }
    public void setE1(Exp e1){
        this.e1 = e1;
    }
    public void setE2(Exp e2){
        this.e2 = e2;
    }
    public void setOp(int op){
        this.op = op;
    }

    @Override
    public Value eval(MyIDictionary<String, Value> tbl, MyIHeap<Integer,Value> heap) throws MyException {
        Value leftValue, rightValue;
        leftValue = e1.eval(tbl,heap);

        if (leftValue.getType().equals(new model.type.BoolType())) {
            rightValue = e2.eval(tbl,heap);

            if (rightValue.getType().equals(new model.type.BoolType())) {
                model.value.BoolValue boolValue1 = (model.value.BoolValue) leftValue;
                model.value.BoolValue boolValue2 = (model.value.BoolValue) rightValue;
                boolean leftBoolValue, rightBoolValue;
                leftBoolValue = boolValue1.getVal();
                rightBoolValue = boolValue2.getVal();

                if (op == 1) return new model.value.BoolValue(leftBoolValue && rightBoolValue);
                if (op == 2) return new model.value.BoolValue(leftBoolValue || rightBoolValue);
            } else {
                throw new MyException("second operand is not a boolean");
            }
        } else {
            throw new MyException("first operand is not a boolean");
        }
        return null;
    }

    @Override
    public Type typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type type1, type2;
        type1 = e1.typecheck(typeEnv);
        type2 = e2.typecheck(typeEnv);

        if (type1.equals(new model.type.BoolType())) {
            if (type2.equals(new model.type.BoolType())) {
                return new model.type.BoolType();
            } else {
                throw new MyException("Second one is not a boolean");
            }
        } else {
            throw new MyException("First one is not a boolean");
        }
    }
}