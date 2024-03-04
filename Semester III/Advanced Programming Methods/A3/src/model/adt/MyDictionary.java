package model.adt;
import model.MyException;
import java.util.HashMap;
import java.util.Collection;

public class MyDictionary <T,V> implements MyIDictionary<T,V>
{
    private HashMap<T,V> dictionary;
    public MyDictionary() // constructor
    {
        dictionary= new HashMap<T,V>();
    }
    public MyDictionary(HashMap<T,V> dictionary)  // constructor
    {
        this.dictionary=dictionary;
    }
    public String toString() // returns the string representation of the dictionary
    {
        return "MyDictionary{" + "dictionary=" + dictionary + "}";
    }
    @Override
    public V lookup(T key) // returns the value associated with key
    {
        return dictionary.get(key);
    }
    @Override
    public HashMap<T,V> getContent() // returns the content of the dictionary
    {
        return this.dictionary;
    }
    @Override
    public Collection<V> values() // returns a collection containing all the values from the dictionary
    {
        synchronized (this)
        {
            return dictionary.values();
        }
    }
    @Override
    public boolean isDefined (T key)
    {
        return this.dictionary.get(key)!=null;
    } // returns true if the key exists in the dictionary and false otherwise
    @Override
    public void update(T key, V value)  throws MyException // updates the pair (key,value) to the dictionary
    {
        if(dictionary.get(key)==null)
            throw new MyException("Key not found");
        else dictionary.put(key,value);
    }
    @Override
    public void add (T key, V value)
    {
        this.dictionary.putIfAbsent(key,value);
    } // adds the pair (key,value) to the dictionary
}