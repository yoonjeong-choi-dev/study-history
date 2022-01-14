package level1;

// https://programmers.co.kr/learn/courses/30/lessons/70128
public class InnerProduct {
    public int solution(int[] a, int[] b) {
        int answer = 0;
        int len = a.length;
        for (int i = 0; i < len; i++) {
            answer += a[i] * b[i];
        }
        return answer;
    }
}
