package model.adt;
import java.util.List;
public interface MyIStack<T>
{
    T pop();
    void push(T valueToPush);
    boolean isEmpty();
    String toString();
    List<T> getAll();
    List<T> getReverese();

    //MyIStack<T> copy();
}
