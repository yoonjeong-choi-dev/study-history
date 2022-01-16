package mvc.hello;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import mvc.command.CommandHandler;

public class HelloHandler implements CommandHandler {
    @Override
	public String process(HttpServletRequest req, HttpServletResponse res)  {
		String name = req.getParameter("name");
        if (name == null ) {
            name = "Anonymous";
        }
        String result = "Hello~~ " + name + "!";
        req.setAttribute("hello", result);
        return "/WEB-INF/view/hello.jsp";
	}
}
