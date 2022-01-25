package controls;

import java.util.HashMap;
import java.util.Map;

import annotation.Component;
import bind.DataBinding;
import dao.ProjectDao;

@Component("/project/list.do")
public class ProjectListController implements Controller, DataBinding {
    ProjectDao dao;
    
    public ProjectListController setProjectDao(ProjectDao dao) {
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
        // 정렬 정보 가져오기
        HashMap<String, Object> paramMap = new HashMap<String, Object>();
        paramMap.put("orderCond", model.get("orderCond"));

        // 컨트롤러에게 데이터(결과 및 뷰) 전달
        model.put("projects", dao.selectList(paramMap));
        return "/view/project/ProjectList.jsp";
    }
}
