import java.util.Arrays;

import javax.swing.text.StyledEditorKit;

public class ArrayCopy {
    public static void main(String[] args) {
        int[] origin = {1,2,3,4,5};
        System.out.print("Original : ");
        System.out.println(Arrays.toString(origin));

        System.out.print("Resize with larger size : ");
        System.out.println(Arrays.toString(resizeArray(origin, 10)));

        System.out.print("Resize with smaller size : ");
        System.out.println(Arrays.toString(resizeArray(origin, 3)));
    }

    private static int[] resizeArray(int[] array, int len) {
        int originalLen = array.length;
        if (originalLen > len) {
            return new int[0];
        }

        int[] ret = new int[len];
        System.arraycopy(array, 0, ret, 0, originalLen);
        return ret;
    }
}
