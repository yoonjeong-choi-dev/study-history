package designpattern.visitor.main;

import designpattern.visitor.main.element.Directory;
import designpattern.visitor.main.element.Entry;
import designpattern.visitor.main.element.File;
import designpattern.visitor.main.visitor.FileFindVisitor;
import designpattern.visitor.main.visitor.PrintInfoVisitor;
import designpattern.visitor.main.visitor.SizeVisitor;

public class Main {
    public static void main(String[] args) {
        System.out.println("Making root directory...");

        Directory root = new Directory("root");
        Directory bin = new Directory("bin");
        Directory tmp = new Directory("tmp");
        Directory home = new Directory("home");

        root.add(bin);
        root.add(tmp);
        root.add(home);

        bin.add(new File("vi", 10000));
        bin.add(new File("git", 20000));
        tmp.add(new File("temp_log.txt", 7777));

        // 방문자 허가
        root.accept(new PrintInfoVisitor());

        System.out.println("\nMaking users");
        Directory user1 = new Directory("yjchoi");
        Directory user2 = new Directory("admin");
        home.add(user1);
        home.add(user2);

        File chrome = new File("Chrome", 50000);

        user1.add(chrome);
        user1.add(new File("IntelliJ", 100000));
        user1.add(new File("index.html", 500));
        user1.add(new File("test.txt", 50));
        user2.add(new File("index2.html", 300));
        user2.add(new File("diary.txt", 555));

        Directory custom = new Directory("Downloads");
        user1.add(custom);
        root.accept(new PrintInfoVisitor());

        System.out.println("\n\n===============================");
        System.out.println("Exercise 1");
        System.out.println("===============================");
        FileFindVisitor format1 = new FileFindVisitor("txt");
        FileFindVisitor format2 = new FileFindVisitor(".html");
        root.accept(format1);
        root.accept(format2);

        System.out.println("1) .txt");
        for(Entry entry : format1.getFoundFiles()) {
            System.out.println(entry.toString());
        }
        System.out.println("2) .html");
        for(Entry entry : format2.getFoundFiles()) {
            System.out.println(entry.toString());
        }


        System.out.println("\n\n===============================");
        System.out.println("Exercise 2");
        System.out.println("===============================");
        SizeVisitor rootSize = new SizeVisitor();
        root.accept(rootSize);
        System.out.printf("Root size : %d\n", rootSize.getSize());
    }
}
