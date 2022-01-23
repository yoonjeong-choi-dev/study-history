package controls;

import java.util.Map;

import bind.DataBinding;
import dao.MemberDao;
import annotation.Component;

@Component("/member/delete.do")
public class MemberDeleteController implements Controller, DataBinding {
    // Java Bean Container
    MemberDao dao;

    public MemberDeleteController setMemberDao(MemberDao dao) {
        this.dao = dao;
        return this;
    }

    @Override
    public Object[] getDataBinders() {
        return new Object[] {
            "id", String.class
        };
    }
    
    @Override
    public String execute(Map<String, Object> model) throws Exception {
        String id = (String) model.get("id");
        int ret = dao.delete(Integer.parseInt(id));

        // 컨트롤러에게 데이터(결과 및 뷰) 전달
        String viewPath;
        if (ret != 0) {
            viewPath = "redirect:list.do";
        } else {
            // 에러 저장
            model.put("error", "일치하는 회원이 없습니다");
            viewPath = "/view/ClientError.jsp";
        }
        return viewPath;
    }
}
