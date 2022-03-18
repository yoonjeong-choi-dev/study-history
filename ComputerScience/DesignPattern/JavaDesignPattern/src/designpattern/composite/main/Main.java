package designpattern.composite.main;

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

        root.printList();

        System.out.println("\nMaking users");
        Directory user1 = new Directory("yjchoi");
        Directory user2 = new Directory("admin");
        home.add(user1);
        home.add(user2);

        File chrome = new File("Chrome", 50000);

        user1.add(chrome);
        user1.add(new File("IntelliJ", 100000));

        Directory custom = new Directory("Downloads");
        user1.add(custom);

        root.printList();

        System.out.println("\nExercise 2");
        System.out.printf("Chrome path : %s\n", chrome.getFullPath());
        System.out.printf("yjchoi path : %s\n", user1.getFullPath());
    }
}
