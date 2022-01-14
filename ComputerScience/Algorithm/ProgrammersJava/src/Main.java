import level1.InnerProduct;

public class Main {

    public static void main(String[] args) {

        InnerProduct s = new InnerProduct();
        int[] a = {1,2,3,4};
        int[] b = {-3,-1,0,2};

        System.out.println(s.solution(a,b));
    }
}
