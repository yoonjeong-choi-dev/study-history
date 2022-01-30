package com.yj.customProperty.money;

import java.beans.PropertyEditorSupport;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

// MoneyEditor 로 만든 경우, 아무런 설정없이 사용 가능
// 동일 패키지 ${타입}Editor 형식이 아닌 경우, xml에서 따로 설정 필요
public class YjMoneyEditor extends PropertyEditorSupport {
    @Override
    public void setAsText(String text) throws IllegalArgumentException {
        Pattern pattern = Pattern.compile("([0-9]+)([A-Z]{3})");
        Matcher matcher = pattern.matcher(text);
        if(!matcher.matches())
            throw new IllegalArgumentException("Invalid Format : (digits)(3-codes)");

        int amount = Integer.parseInt(matcher.group(1));
        String currency = matcher.group(2);
        setValue(new Money(amount, currency));
    }
}
