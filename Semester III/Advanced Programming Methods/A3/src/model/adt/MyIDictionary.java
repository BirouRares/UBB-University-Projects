package model.adt;
import model.MyException;
import java.util.Collection;
import java.util.HashMap;

public interface MyIDictionary<T,V>
{ // T - key, V - value
    V lookup(T key); // returns the value associated with key
    HashMap<T,V> getContent(); // returns the content of the dictionary
    Collection<V> values(); // returns a collection containing all the values from the dictionary
    boolean isDefined (T key); // returns true if the key exists in the dictionary and false otherwise
    void update(T key, V value)  throws MyException; // updates the pair (key,value) to the dictionary
    void add (T key, V value); // adds the pair (key,value) to the dictionary

}
