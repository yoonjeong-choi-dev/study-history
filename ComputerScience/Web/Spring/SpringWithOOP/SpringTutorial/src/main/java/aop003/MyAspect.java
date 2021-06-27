package aop003;

import org.aspectj.lang.JoinPoint;

public class MyAspect {
	
	//@Before("execution(* runSomething())")
	public void before(JoinPoint joinPoint) {
		System.out.println(joinPoint.getTarget().toString());
		System.out.println("Face Recognization : Open the door");
		System.out.println("Enter the house through the door opened");
	}
	
	//@After("execution(* runSomething())")
	public void after(JoinPoint joinPoint) {
		System.out.println("Turn off the light and Sleep");
	}
	
	//@AfterThrowing(value="execution(* runSomething())", throwing = "e")
	public void afterThrowing(JoinPoint joitPoint, Exception e) {
		if(e.getMessage().equals("Fire in the house")) {
			System.out.println("Call 119");
		}
	}
	
	//@AfterReturning("execution(* runSomething())")
	public void afterReturning(JoinPoint joinPoint) {
		System.out.println("Lock the door and Go out");
	}
}
