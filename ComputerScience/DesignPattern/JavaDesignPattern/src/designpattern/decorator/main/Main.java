package designpattern.decorator.main;

import designpattern.decorator.main.component.Display;
import designpattern.decorator.main.component.MultiStringDisplay;
import designpattern.decorator.main.component.StringDisplay;
import designpattern.decorator.main.decorator.FullBorder;
import designpattern.decorator.main.decorator.SideBorder;
import designpattern.decorator.main.decorator.UpDownBorder;

public class Main {
    public static void main(String[] args) {
        Display d1 = new StringDisplay("Simple Display");
        Display deco1 = new SideBorder(d1, '#');
        Display deco2 = new FullBorder(deco1);

        System.out.println("Example 1 : Simple String Display");
        d1.show();

        System.out.println("Example 2 : String Display with Side Deco");
        deco1.show();

        System.out.println("Example 3 : String Display with Side&Full Deco");
        deco2.show();

        System.out.println("\n\nExample 4 : A lot of decorations");
        Display d2 = new SideBorder(
                new FullBorder(
                        new SideBorder(
                                new FullBorder(
                                        new StringDisplay("Hello~~ I am Yoonjeong!")
                                ), '*'
                        )
                ), '/'
        );
        d2.show();


        System.out.println("\n\n Exercise 1");
        Display ex1 = new UpDownBorder(
                new SideBorder(
                        new StringDisplay("Exercise 1- Up Down Deco"), '*'
                ), '='
        );
        ex1.show();

        System.out.println("\n\n Exercise 2");
        MultiStringDisplay md = new MultiStringDisplay();
        md.add("Good Morning~");
        md.add("Hello~!");
        md.add("Good night. See you tomorrow!!");

        Display ex2 = new FullBorder(
                new SideBorder(
                        md, '*'
                )
        );
        ex2.show();
    }
}
