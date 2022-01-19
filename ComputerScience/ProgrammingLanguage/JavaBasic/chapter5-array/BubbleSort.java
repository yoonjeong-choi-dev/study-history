import java.util.Arrays;

public class BubbleSort {
    public static void main(String[] args) {
        int[] example1 = {5,43,2,12,2};
        int[] example2 = {12,2,156,21,11};

        System.out.println("원본 : " + Arrays.toString(example1));
        doSort(example1);
        System.out.println("결과 : " + Arrays.toString(example1));

        System.out.println("원본 : " + Arrays.toString(example2));
        doSort(example2);
        System.out.println("원본 : " + Arrays.toString(example2));
        
        System.out.println(Arrays.toString(example2));
    }

    private static void doSort(int[] arr) {
        int len = arr.length;
        for(int i=0;i<len-1;i++) {
            for(int j=0;j<len - 1 -i ;j++ ){
                if(arr[j] > arr[j+1]) {
                    int temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
    }
    
}
