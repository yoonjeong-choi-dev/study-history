package designpattern.facade.main.component;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Properties;

public class Database {
    private static final String basePath = "src/designpattern/facade/main/component";

    // 인스턴스 생성 X
    private Database() {
    }

    public static Properties getProperties(String dbname) {
        String filename = String.format("%s/%s.txt", basePath, dbname);
        Properties properties = new Properties();
        try {
            properties.load(new FileInputStream(filename));
        } catch (IOException e) {
            System.out.printf("[Warning] %s is not found\n", filename);
        }

        return properties;
    }

}
