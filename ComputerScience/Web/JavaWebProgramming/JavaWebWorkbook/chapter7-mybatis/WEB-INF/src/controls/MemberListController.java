package controls;

import java.util.HashMap;
import java.util.Map;

import dao.MemberDao;
import annotation.Component;
import bind.DataBinding;

@Component("/member/list.do")
public class MemberListController implements Controller, DataBinding {
    // Java Bean Container
    MemberDao dao;

    public MemberListController setMemberDao(MemberDao dao) {
        this.dao = dao;
        return this;
    }

    @Override
    public Object[] getDataBinders() {
        return new Object[] {
            "orderCond", String.class
        };
    }

    @Override
    public String execute(Map<String, Object> model) throws Exception {
        HashMap<String, Object> paramMap = new HashMap<String, Object>();
        paramMap.put("orderCond", model.get("orderCond"));

        // 컨트롤러에게 데이터(결과 및 뷰) 전달
        model.put("members", dao.selectList(paramMap));
        return "/view/member/MemberList.jsp";
    }
}
