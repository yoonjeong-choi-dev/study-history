package designpattern.templatemethod.headfirst.concrete;

import designpattern.templatemethod.headfirst.abstractclass.CaffeineBeverageWithHook;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CoffeeWithHook extends CaffeineBeverageWithHook {

    @Override
    protected void init() {
        System.out.println("Preparing Coffee (With Hook)...");
    }

    @Override
    protected void brew() {
        System.out.println("Brewing coffee grinds through the filter");
    }

    @Override
    protected void addCondiments() {
        System.out.println("Adding sugar and milk to the coffee");
    }

    // hook override
    @Override
    protected boolean customerWantsCondiments() {
        String answer = getUserInput();
        return answer.toLowerCase().startsWith("y");
    }

    private String getUserInput() {
        String answer = null;

        System.out.println("Do you want to add sugar and milk? (y/n)  ");

        BufferedReader in = new BufferedReader(new InputStreamReader((System.in)));
        try {
            answer = in.readLine();
        } catch (IOException e) {
            System.err.println("IO Exception!");
        }

        if (answer == null) answer = "no";
        return answer;
    }
}
