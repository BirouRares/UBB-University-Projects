import java.util.Random;

class RandomString
{
    private static final String CHAR_LIST =
            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    private static final int RANDOM_STRING_LENGTH = 10;

    String generateRandomString()
    {
        StringBuilder randStr = new StringBuilder();

        for(int i=0; i<RANDOM_STRING_LENGTH; i++)
        {
            int number = getRandomNumber();
            char ch = CHAR_LIST.charAt(number);
            randStr.append(ch);
        }

        return randStr.toString();
    }
    private int getRandomNumber()
    {
        int randomInt = 0;
        Random randomGenerator = new Random();
        randomInt = randomGenerator.nextInt(CHAR_LIST.length());
        if (randomInt - 1 == -1)
        {
            return randomInt;
        }
        else
        {
            return randomInt - 1;
        }
    }
}