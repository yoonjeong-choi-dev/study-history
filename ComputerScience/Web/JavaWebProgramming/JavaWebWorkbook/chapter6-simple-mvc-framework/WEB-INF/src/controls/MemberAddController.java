package controls;

import java.util.Map;

import dao.MemberDao;
import vo.Member;
import bind.DataBinding;
import annotation.Component;

@Component("/member/add.do")
public class MemberAddController implements Controller, DataBinding {
    // Java Bean Container
    MemberDao dao;

    public MemberAddController setMemberDao(MemberDao dao) {
        this.dao = dao;
        return this;
    }

    @Override
    public Object[] getDataBinders() {
        return new Object[] {
            "member", vo.Member.class
        };
    }
    
    @Override
    public String execute(Map<String, Object> model) throws Exception {
        Member member = (Member)model.get("member");
        if (member.getEmail() == null) {
            // GET : 이메일 정보가 없는 경우 (DataBinding을 사용하기 위해 이러한 조건 사용)
            return "/view/member/MemberAdd.jsp";
        } else {
            // POST : 이메일 정보가 있는 경우
            // 컨트롤러에서 받은 정보로 로직 처리
            dao.insert(member);

            return "redirect:list.do";
        }
    }
}
