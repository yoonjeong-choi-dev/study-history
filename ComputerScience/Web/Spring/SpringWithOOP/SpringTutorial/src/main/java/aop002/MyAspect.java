package aop002;

import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;
import org.aspectj.lang.JoinPoint;

@Aspect
public class MyAspect {
	@Before("execution(public void aop002.Boy.runSomething())")
	public void before(JoinPoint jointPoint) {
		System.out.println("Face Recognization : Open the door");
		System.out.println("Enter the house through the door opened");
	}
}
