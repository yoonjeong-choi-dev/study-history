package aop002;

import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;
import org.aspectj.lang.annotation.After;
import org.aspectj.lang.annotation.AfterReturning;
import org.aspectj.lang.annotation.AfterThrowing;
import org.aspectj.lang.annotation.Pointcut;
import org.aspectj.lang.JoinPoint;
import org.springframework.stereotype.Component;

@Component
@Aspect
public class MyAspect {
	@Pointcut("execution(* runSomething())")
	private void pc() {
		
	}
	
	@Before("pc()")
	public void before(JoinPoint joinPoint) {
		System.out.println(joinPoint.getTarget().toString());
		System.out.println("Face Recognization : Open the door");
		System.out.println("Enter the house through the door opened");
	}
	
	@After("pc()")
	public void after(JoinPoint joinPoint) {
		System.out.println("Turn off the light and Sleep");
	}
	
	@AfterThrowing(value="pc()", throwing = "e")
	public void afterThrowing(JoinPoint joitPoint, Exception e) {
		if(e.getMessage().equals("Fire in the house")) {
			System.out.println("Call 119");
		}
	}
	
	@AfterReturning("pc()")
	public void afterReturning(JoinPoint joinPoint) {
		System.out.println("Lock the door and Go out");
	}
}
