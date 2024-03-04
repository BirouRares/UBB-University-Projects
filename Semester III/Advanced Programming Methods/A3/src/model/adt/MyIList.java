package model.adt;
import java.util.List;
public interface MyIList<V>
{   // V - value
    List<V> getList(); // returns the list
    void add(V valueToAdd); // adds the value to the list
    void clear(); // clears the list
}
