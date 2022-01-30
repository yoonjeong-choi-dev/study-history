package com.yj.customService;

import org.springframework.core.convert.TypeDescriptor;
import org.springframework.core.convert.converter.GenericConverter;

import java.util.Collections;
import java.util.HashSet;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class MoneyGenericConverter implements GenericConverter {
    // 타입1-> 타입2 로 변환 가능한 (타입1, 타입2)에 대한 집합
    private Set<ConvertiblePair> pairs;

    public MoneyGenericConverter() {
        Set<ConvertiblePair> pairs = new HashSet<ConvertiblePair>();
        pairs.add(new ConvertiblePair(String.class, Money.class));
        this.pairs = Collections.unmodifiableSet(pairs);
    }

    @Override
    public Set<ConvertiblePair> getConvertibleTypes() {
        return pairs;
    }

    @Override
    public Object convert(Object src, TypeDescriptor srcType, TypeDescriptor dstType) {
        // String -> Money 타입으로의 변환이 아닌 경우 예외
        if(dstType.getType() != Money.class)
            throw new IllegalArgumentException("Invalid target type");
        if(srcType.getType() != String.class)
            throw new IllegalArgumentException("Invalid source type");

        String moneyString = (String) src;
        Pattern pattern = Pattern.compile("([0-9]+)([A-Z]{3})");
        Matcher matcher = pattern.matcher(moneyString);
        if(!matcher.matches())
            throw new IllegalArgumentException("Invalid Format : (digits)(3-codes)");

        int amount = Integer.parseInt(matcher.group(1));
        String currency = matcher.group(2);

        return new Money(amount, currency);
    }
}
