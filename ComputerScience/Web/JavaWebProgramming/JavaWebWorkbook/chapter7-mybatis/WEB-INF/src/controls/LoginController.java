package controls;

import java.util.Map;

import javax.servlet.http.HttpSession;

import dao.MemberDao;
import vo.Member;
import bind.DataBinding;
import annotation.Component;

@Component("/auth/login.do")
public class LoginController implements Controller, DataBinding {
    // Java Bean Container
    MemberDao dao;

    public LoginController setMemberDao(MemberDao dao) {
        this.dao = dao;
        return this;
    }

    @Override
    public Object[] getDataBinders() {
        return new Object[] {
            "login", vo.Member.class
        };
    }

    @Override
    public String execute(Map<String, Object> model) throws Exception {
        Member login = (Member) model.get("login");
        if (login.getPassword() == null) {
            // GET : 비밀번호가 없는 경우
            return "/view/auth/LoginForm.jsp";
        } else {
            // 컨트롤러에서 받은 정보로 로직 처리
            Member member = dao.login(login.getEmail(), login.getPassword());

            // 해당 정보가 있으면 로그인 수행
            String viewPath;
            if(member!= null) {
                // 세션에 저장
                HttpSession session = (HttpSession) model.get("session");
                session.setAttribute("member", member);
                viewPath = "redirect:../member/list.do";
            } else {
                // 로그인 실패 페이지
                viewPath = "/view/auth/LoginFail.jsp";
            }

            return viewPath;
        }
    }
}
