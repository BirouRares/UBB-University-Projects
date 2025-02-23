package model.adt;

import java.util.HashMap;

public interface MyIFileTable<K,V>
{
    V lookup(K key);
    void update(K key, V value);
    void add(K key, V value);
    void remove(K key);
    boolean isDefined(K key);
    HashMap<K,V> getContent();
}
