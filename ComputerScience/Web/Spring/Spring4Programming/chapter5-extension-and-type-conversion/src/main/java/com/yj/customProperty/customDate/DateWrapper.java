package com.yj.customProperty.customDate;

import java.util.Date;

// Date 커스텀 에디터 설정 테스트용 래퍼 클래스
public class DateWrapper {
    private Date date;

    public void setDate(Date date) {
        this.date = date;
    }

    @Override
    public String toString() {
        return "DateWrapper{" +
                "date=" + date +
                '}';
    }
}
