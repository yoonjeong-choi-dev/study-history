package controls;

import java.util.Map;

import dao.MemberDao;
import annotation.Component;

@Component("/member/list.do")
public class MemberListController implements Controller {
    // Java Bean Container
    MemberDao dao;

    public MemberListController setMemberDao(MemberDao dao) {
        this.dao = dao;
        return this;
    }

    @Override
    public String execute(Map<String, Object> model) throws Exception {
        // 컨트롤러에게 데이터(결과 및 뷰) 전달
        model.put("members", dao.selectList());
        return "/view/member/MemberList.jsp";
    }
}
