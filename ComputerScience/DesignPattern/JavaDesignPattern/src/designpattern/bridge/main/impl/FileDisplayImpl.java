package designpattern.bridge.main.impl;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

// Exercise 2
public class FileDisplayImpl extends DisplayImpl {
    private final String fileName;
    private BufferedReader reader;

    public FileDisplayImpl(String fileName) {
        this.fileName = fileName;
    }

    @Override
    public void rawOpen() {
        try {
            reader = new BufferedReader(new FileReader(fileName));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        System.out.printf("[Read File] %s\n", fileName);
    }

    @Override
    public void rawPrint() {
        if (reader == null) return;

        try {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void rawClose() {
        if (reader == null) return;

        System.out.println("[End File] ==================");
        try {
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            reader = null;
        }
    }
}
