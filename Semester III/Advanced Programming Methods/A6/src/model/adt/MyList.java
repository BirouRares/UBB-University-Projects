package model.adt;
import model.MyException;

import java.util.List;
import java.util.ArrayList;
import java.util.Vector;
public class MyList <V> implements MyIList<V>
{
    private List<V> list;
    public MyList(){
        list = new ArrayList<V>();
    }
    public MyList(List<V> list){
        this.list = list;
    }
    public List<V> getList(){
        return list;
    }
    public void setList(List<V> list){
        this.list = list;
    }
    public String toString(){
        StringBuilder result = new StringBuilder("MyList{\n");
        for (V item : list)
        {
            result.append("\t").append(item).append("\n");
        }
        result.append("}");
        return result.toString();
    }
    @Override
    public void add(V valueToAdd){
        list.add(valueToAdd);
    }
    @Override
    public void clear(){
        list.clear();
    }

    /*@Override
    public V get(int index){
        return list.get(index);
    }*/
 }
