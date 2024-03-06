package model.ADT;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;


public class LatchTable implements ILatchTable
{
    private int location_that_is_free = 0;
    private HashMap<Integer, Integer> latchTable;




    public LatchTable()  // constructor - initialize the latch table as a new HashMap
    {
        latchTable = new HashMap<>();
    }

    @Override
    public String toString()//retunr the string
    {
        return latchTable.toString();
    }




    @Override
    public int getFree() // free loc.
    {
        synchronized (this)
        {
            location_that_is_free++;
            return location_that_is_free;
        }

    }

    @Override
    public void put(int key, int value)
    {
        synchronized (this)
        {
            this.latchTable.put(key, value);

        }

    }

    @Override
    public int get(int key)
    {
        synchronized (this)
        {
            return this.latchTable.get(key);

        }

    }

    @Override
    public boolean containsKey(int key)
    {// check if exists
        synchronized (this)
        {
            if (this.latchTable.get(key) != null)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

    }

    @Override
    public void update(int key, int value)
    {
        synchronized (this)
        {
            this.latchTable.put(key, value);
        }
    }

    @Override
    public void setContent(HashMap<Integer, Integer> latchTable)
    {
        synchronized (this)
        {
            this.latchTable = latchTable;
        }
    }



    @Override
    public HashMap<Integer, Integer> getContent()
    {
        synchronized (this)
        {
            return latchTable;
        }
    }
}
