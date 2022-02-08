package com.yj.simpleAop;

import org.springframework.stereotype.Service;

@Service
public class SampleServiceImpl implements SampleService{
    @Override
    public Integer doAdd(String str1, String str2) throws Exception {
        return Integer.valueOf(str1) + Integer.valueOf(str2);
    }

    @Override
    public Integer doMinus(String str1, String str2) throws Exception {
        return Integer.valueOf(str1) - Integer.valueOf(str2);
    }

}
