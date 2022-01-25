package controls;

import java.util.Map;

import bind.DataBinding;
import dao.MemberDao;
import vo.Member;
import annotation.Component;

@Component("/member/update.do")
public class MemberUpdateController implements Controller, DataBinding {
    // Java Bean Container
    MemberDao dao;

    public MemberUpdateController setMemberDao(MemberDao dao) {
        this.dao = dao;
        return this;
    }
    
    @Override
    public Object[] getDataBinders() {
        return new Object[] {
            "id", String.class,
            "member", vo.Member.class
        };
    }

    @Override
    public String execute(Map<String, Object> model) throws Exception {
        Member member = (Member)model.get("member");

        if (member.getEmail() == null) {
            // GET : 이메일 정보가 없는 경우 (DataBinding을 사용하기 위해 이러한 조건 사용)
            String id = (String) model.get("id");
            Member result = dao.selectById(Integer.parseInt(id));

            String viewPath;
            if (result != null) {
                model.put("member", result);
                viewPath = "/view/member/MemberUpdate.jsp";
            } else {
                // 에러 저장
                model.put("error", "일치하는 회원이 없습니다");
                viewPath = "/view/ClientError.jsp";
            }

            return viewPath;
        } else {
            // POST : 이메일 정보가 있는 경우

            // 컨트롤러에서 받은 정보로 로직 처리
            dao.update(member);

            return "/view/member/MemberUpdateSuccess.jsp";
        }
    }
}
