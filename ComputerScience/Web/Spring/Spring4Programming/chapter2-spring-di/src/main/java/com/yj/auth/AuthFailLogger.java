package com.yj.auth;

public class AuthFailLogger {
    private int threshold;
    private int failCounts;

    public void insertBadPassword(String userId, String password) {
        System.out.printf("AuthFail [type=bad-password], userid=%s, password=%s\n", userId, password);
        failCounts++;

        if(threshold>0&&failCounts>threshold) {
            notifyTooManyFail();
            failCounts = 0;
        }
    }

    private void notifyTooManyFail() {
        System.out.println("너무 많은 로그인 시도 실패");
    }

    public void setThreshold(int threshold) {
        this.threshold = threshold;
    }
}
