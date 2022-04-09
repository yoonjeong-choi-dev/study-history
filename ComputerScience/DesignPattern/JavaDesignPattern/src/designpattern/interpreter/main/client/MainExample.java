package designpattern.interpreter.main.client;

import designpattern.interpreter.main.language.Context;
import designpattern.interpreter.main.language.Node;
import designpattern.interpreter.main.language.nonterminal.ProgramNode;

import java.io.BufferedReader;
import java.io.FileReader;

public class MainExample {

    public static void main(String[] args) {
        String filePath = "src/designpattern/interpreter/main/client/program.txt";

        try {
            BufferedReader reader = new BufferedReader(new FileReader(filePath));
            String text;
            while((text = reader.readLine()) != null) {
                System.out.printf("Text : %s\n", text);
                Node root = new ProgramNode();
                root.parse(new Context(text));

                System.out.printf("Node : %s\n", root.toString());
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
