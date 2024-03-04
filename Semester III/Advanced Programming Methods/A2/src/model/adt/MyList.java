package model.adt;
import java.util.List;
import java.util.ArrayList;
public class MyList <V> implements MyIList<V>
{
    private List<V> list; // list of values
    public MyList()
    {
        list = new ArrayList<V>();
    }  // constructor
    public MyList(List<V> list)
    {
        this.list = list;
    }  // constructor
    public List<V> getList(){
        return list;
    }  // returns the list
    public void setList(List<V> list)
    {
        this.list = list;
    }  // sets the list
    public String toString(){ // returns the string representation of the list
        return
                "MyList{" +
                        "list=" + list +
                        '}';
    }
    @Override
    public void add(V valueToAdd)
    {
        list.add(valueToAdd);
    }  // adds the value to the list
    @Override
    public void clear()
    {
        list.clear();
    }   // clears the list
 }
