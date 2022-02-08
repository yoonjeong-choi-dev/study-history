package com.yj.simpleAop;

import lombok.extern.log4j.Log4j;
import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.AfterThrowing;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;
import org.springframework.stereotype.Component;

import java.util.Arrays;

@Aspect
@Log4j
@Component
public class LogAdvice {
    @Before("execution(* com.yj.simpleAop.SampleService*.doAdd(..))")
    public void logBefore() {
        log.info("[@Before] Simple Log ==============>");
    }

    @Before("execution(* com.yj.simpleAop.SampleService*.doAdd(String, String)) && args(str1, str2)")
    public void logBeforeWithParam(String str1, String str2) {
        log.info("[@Before] Logging parameters");
        log.info("str1 : " + str1);
        log.info("str2 : " + str2);
    }

    @AfterThrowing(pointcut = "execution(* com.yj.simpleAop.SampleService*.doAdd(..))", throwing = "ex")
    public void logException(Exception ex) {
        log.info("[@AfterThrowing] Exception!!!");
        log.info("exception : " + ex);
    }

    @Around("execution(* com.yj.simpleAop.SampleService*.doMinus(..))")
    public Object logTime(ProceedingJoinPoint joinPoint) {
        log.info("[@Around] Simple Execution Log ==============>");
        long start = System.currentTimeMillis();

        log.info("Target : " + joinPoint.getTarget());
        log.info("Param : " + Arrays.toString(joinPoint.getArgs()));

        Object result = null;
        try {
            result = joinPoint.proceed();
        } catch (Throwable e) {
            e.printStackTrace();;
        }

        long end = System.currentTimeMillis();
        log.info("Time : " + (end - start));

        return result;
    }
}
