package view;

public abstract class Command
{
    public Command(String key, String description)
    {
        this.key = key;
        this.description = description;
    }
    private final String key;
    private final String description;

    public abstract void execute();
    public String getKey()
    {
        return key;
    }
    public String getDescription()
    {
        return description;
    }
}
