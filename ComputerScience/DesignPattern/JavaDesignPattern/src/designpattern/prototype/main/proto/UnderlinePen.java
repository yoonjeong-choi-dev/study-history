package designpattern.prototype.main.proto;

import designpattern.prototype.main.framework.Product;

public class UnderlinePen implements Product {
    private final char underline;
    public UnderlinePen(char underline) {
        this.underline = underline;
    }

    @Override
    public void use(String s) {
        int length = s.getBytes().length;

        System.out.printf("\"%s\"\n", s);

        System.out.print(" ");
        for(int i=0;i<length;i++){
            System.out.print(underline);
        }
        System.out.println();
    }

    @Override
    public Product createClone() {
        Product p = null;
        try {
            p = (Product) this.clone();
        } catch (CloneNotSupportedException e) {
            e.printStackTrace();
        }
        return p;
    }
}
