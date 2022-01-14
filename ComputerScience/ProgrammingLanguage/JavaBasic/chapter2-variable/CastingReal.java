public class CastingReal {
    public static void main(String[] args) {
        float f = 9.1234567f;
        double d = (double) f;
        double d1 = 9.1234567;       

        System.out.printf("f = %20.18f\n", f);
        System.out.printf("d = %20.18f\n", d);
        System.out.printf("d1 = %20.18f\n", d1);
    }
}
