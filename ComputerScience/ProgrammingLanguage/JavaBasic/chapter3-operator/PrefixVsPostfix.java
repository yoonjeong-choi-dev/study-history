public class PrefixVsPostfix {
    public static void main(String[] args) {
        int x = 10;
        x = x++ - ++x;
        System.out.printf("x = x++ - ++x : %d\n", x);

        int y = 10;
        y = ++y - y++;
        System.out.printf("y = y++ - ++y : %d\n", y);
    }
}