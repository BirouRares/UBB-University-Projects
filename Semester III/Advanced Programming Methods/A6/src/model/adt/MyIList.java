package model.adt;
import model.MyException;

import java.util.List;
import java.util.Vector;

public interface MyIList<V>
{   // V - value
    void add(V valueToAdd);
    List<V> getList();
    void clear();
}
