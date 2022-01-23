package controls;

import java.util.Map;

import annotation.Component;
import dao.ProjectDao;

@Component("/project/list.do")
public class ProjectListController implements Controller {
    ProjectDao dao;
    
    public ProjectListController setProjectDao(ProjectDao dao) {
        this.dao = dao;
        return this;
    }

    @Override
    public String execute(Map<String, Object> model) throws Exception {
        // 컨트롤러에게 데이터(결과 및 뷰) 전달
        model.put("projects", dao.selectList());
        return "/view/project/ProjectList.jsp";
    }
}
