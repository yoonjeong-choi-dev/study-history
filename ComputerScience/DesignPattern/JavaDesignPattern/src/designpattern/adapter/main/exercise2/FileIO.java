package designpattern.adapter.main.exercise2;

import java.io.IOException;

// Target 역할 : 어댑터를 통해 이미 주어진 클래스(Adaptee, java.util.Properties)의 기능을 변환해야 하는 목적지
public interface FileIO {
    void readFromFile(String filename) throws IOException;
    void writeToFile(String filename) throws IOException;
    void setValue(String key, String value);
    String getValue(String key);
}
