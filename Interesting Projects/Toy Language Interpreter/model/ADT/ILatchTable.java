package model.ADT;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
public interface ILatchTable
{
    HashMap<Integer, Integer> getContent(); //return the content of the latch table as a HashMap
    void setContent(HashMap<Integer, Integer> latchTable);  // this function sets the content of the latch table
    int getFree();  // this function returns a free location in the latch table
    void put(int key, int value);  // this function adds a new entry in the latch table
    int get(int key);  // this function returns the value of a given key
    boolean containsKey(int key);  //this function checks if a given key exists in the latch table
    void update(int key, int value); // this function updates the value of a given key



    /*int get(int key);
    boolean containsKey(int k);
    void update(int key, int v); */
}
