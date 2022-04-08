package designpattern.proxy.main;

import designpattern.proxy.main.proxy.PrinterProxy;
import designpattern.proxy.main.subject.Printable;

public class Main {
    public static void main(String[] args) {
        Printable printer = new PrinterProxy("YJ");
        System.out.printf("Current name is %s\n", printer.getPrinterName());

        printer.setPrinterName("YJ-CHOI");
        System.out.printf("Current name is %s\n", printer.getPrinterName());

        printer.print("Hello~ World~~!");

        // Exercise 1
        String className = "designpattern.proxy.main.realsubject.Printer";
        Printable printer2 = new PrinterProxy("Exercise", className);
        System.out.printf("Current name is %s\n", printer2.getPrinterName());
        printer2.print("Exercise Test~");
    }
}
