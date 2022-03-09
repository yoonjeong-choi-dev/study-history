package designpattern.adapter.main.exercise2;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Properties;
import java.io.IOException;

/**
 * java.util.Properties 클래스를 이용하여 property 집합을 파일로 보존하는 어댑터
 * java.util.Properties ->  FileIO 어댑터
 * 상속을 이용하여 Properties 내부 메서드를 몰라도 property 조작 가능
 */
public class FileProperties extends Properties implements FileIO {
    @Override
    public void readFromFile(String filename) throws IOException {
        load(new FileInputStream(filename));
    }

    @Override
    public void writeToFile(String filename) throws IOException {
        store(new FileOutputStream(filename), "[ Written by FileProperties Adapter]");
    }

    @Override
    public void setValue(String key, String value) {
        setProperty(key, value);
    }

    @Override
    public String getValue(String key) {
        return getProperty(key);
    }
}
