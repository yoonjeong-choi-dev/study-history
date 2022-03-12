package designpattern.builder.main;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            usage();
            System.exit(0);
        }


        Director director = null;
        if (args[0].equals("plain")) {
            // Build Plain Document
            TextBuilder builder = new TextBuilder();
            director = new Director(builder);
            director.construct();

            String result = builder.getText();
            System.out.println(result);
        } else if (args[0].equals("html")) {
            // Build HTML Document
            HTMLBuilder builder = new HTMLBuilder();
            director = new Director(builder);
            director.construct();

            String filename = builder.getFilename();
            System.out.println(filename + " is written");
        } else {
            usage();
            System.exit(0);
        }
    }

    public static void usage() {
        System.out.println("Usage: java Main <plain|html>");
    }
}
