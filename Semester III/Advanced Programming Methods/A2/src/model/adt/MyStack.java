package model.adt;
import model.adt.MyIStack;
import java.util.Arrays;
import java.util.Stack;
import java.util.Collections;
import java.util.List;
public class MyStack<T> implements MyIStack<T>
{
    private Stack<T> stack; // stack of values
    public MyStack(){
        stack = new Stack<>();
    }  // constructor
    public MyStack(Stack<T> stack)
    {
        this.stack = stack;
    }  // constructor
    public Stack<T> getStack()
    {
        return stack;
    }  // returns the stack
    public void setStack(Stack<T> stack)
    {
        this.stack = stack;
    }  // sets the stack
    public String toString()
    {
        return "MyStack{" + "stack=" + stack + "}";
    }  // returns the string representation of the stack

    @Override
    public T pop() {
        return this.stack.pop();
    } // pops the value from the stack

    @Override
    public void push(T valueToPush)
    {
        this.stack.push(valueToPush);
    }  // pushes the value to the stack

    @Override
    public boolean isEmpty()
    {
        return this.stack.empty();
    }  // returns true if the stack is empty, false otherwise

    @Override
    public List<T> getReverese()  // returns the list
    {
        List<T> list = Arrays.asList((T[])this.stack.toArray());
        Collections.reverse(list);
        return list;
    }
}
