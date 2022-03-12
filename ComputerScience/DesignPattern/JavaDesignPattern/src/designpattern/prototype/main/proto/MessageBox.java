package designpattern.prototype.main.proto;

import designpattern.prototype.main.framework.Product;

public class MessageBox implements Product {
    private final char decoChar;
    public MessageBox(char decoChar) {
        this.decoChar = decoChar;
    }

    @Override
    public void use(String s) {
        int length = s.getBytes().length;

        for(int i=0;i<length+4;i++){
            System.out.print(decoChar);
        }
        System.out.println();

        System.out.printf("%c %s %c\n", decoChar, s, decoChar);

        for(int i=0;i<length+4;i++){
            System.out.print(decoChar);
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
