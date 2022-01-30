package com.yj.customService;

import org.springframework.core.convert.converter.Converter;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class StringToMoneyConverter implements Converter<String, Money> {

    @Override
    public Money convert(String src) {
        Pattern pattern = Pattern.compile("([0-9]+)([A-Z]{3})");
        Matcher matcher = pattern.matcher(src);
        if(!matcher.matches())
            throw new IllegalArgumentException("Invalid Format : (digits)(3-codes)");

        int amount = Integer.parseInt(matcher.group(1));
        String currency = matcher.group(2);

        return new Money(amount, currency);
    }
}
