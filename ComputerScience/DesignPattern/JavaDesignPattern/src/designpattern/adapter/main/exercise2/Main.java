package designpattern.adapter.main.exercise2;

import java.io.File;
import java.io.IOException;

public class Main {
    public static void main(String[] args) {

        FileIO f = new FileProperties();
        try {
            File directory = new File("src/designpattern/adapter/main/exercise2");
            String base = directory.getCanonicalPath();
            f.readFromFile(base + "/example.properties");
            f.setValue("year", "1993");
            f.setValue("month", "7");
            f.setValue("day", "13");
            f.writeToFile(base + "/newFile.txt");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
