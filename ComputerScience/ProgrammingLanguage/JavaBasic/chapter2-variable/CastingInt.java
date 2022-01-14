public class CastingInt {
    public static void main(String[] args) {
        int i = 10;
        byte b = (byte) i;
        System.out.println("Before casting bit : " + Integer.toBinaryString(i));
        System.out.println("After casting bit : " + Integer.toBinaryString(b));
        System.out.printf("[int -> byte] i=%d -> b=%d\n", i, b);

        i = 300;
        b = (byte) i;
        System.out.println("Before casting bit : " + Integer.toBinaryString(i));
        System.out.println("After casting bit : " + Integer.toBinaryString(b));
        System.out.printf("[int -> byte] i=%d -> b=%d\n", i, b);

        b = 10;
        i = (int) b;
        System.out.println("Before casting bit : " + Integer.toBinaryString(b));
        System.out.println("After casting bit : " + Integer.toBinaryString(i));
        System.out.printf("[byte -> int] b=%d -> i=%d\n", b, i);

        b = -2;
        i = (int) b;
        System.out.println("Before casting bit : " + Integer.toBinaryString(b));
        System.out.println("After casting bit : " + Integer.toBinaryString(i));
        System.out.printf("[byte -> int] b=%d -> i=%d\n", b, i);
    }
}
