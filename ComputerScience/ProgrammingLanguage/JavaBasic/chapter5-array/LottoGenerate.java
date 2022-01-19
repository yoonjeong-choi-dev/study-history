public class LottoGenerate {
    public static void main(String[] args) {
        final int LOTTO_MAX = 45; // 로또 범위
        final int LOTTO_SIZE = 6; // 로또 번호 개수

        // 로또 배열 초기화
        int[] nums = new int[LOTTO_MAX];
        for (int i = 0; i < LOTTO_MAX; i++) {
            nums[i] = i + 1;
        }

        // 랜덤 생성
        int temp, randIdx;

        for (int i = 0; i < LOTTO_SIZE; i++) {
            randIdx = (int) (Math.random() * LOTTO_MAX);
            temp = nums[i];
            nums[i] = nums[randIdx];
            nums[randIdx] = temp;
        }

        // 출력
        System.out.print("로또 결과 : ");
        for(int i=0;i<LOTTO_SIZE;i++) {
            System.out.printf("%d ", nums[i]);
        }
        System.out.println();
    }
}
