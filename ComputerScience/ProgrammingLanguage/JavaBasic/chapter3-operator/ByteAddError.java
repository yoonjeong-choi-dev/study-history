public class ByteAddError {
    public static void main(String[] args) {
        byte a = 10, b = 20;
        // byte c = a + b; // 컴파일 에러 발생
        byte c = (byte) ( a + b);
        System.out.println(c);
    }
}
