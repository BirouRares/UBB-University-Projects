package model.adt;
import java.util.List;
public interface MyIStack<T>
{
    List<T> getReverese(); // returns the list
    boolean isEmpty(); // returns true if the stack is empty, false otherwise
    void push(T valueToPush); // pushes the value to the stack
    T pop(); // pops the value from the stack
}
