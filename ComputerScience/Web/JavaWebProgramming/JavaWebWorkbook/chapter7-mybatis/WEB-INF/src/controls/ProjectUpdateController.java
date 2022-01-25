package controls;

import java.util.Map;

import annotation.Component;
import bind.DataBinding;
import dao.ProjectDao;
import vo.Project;

@Component("/project/update.do")
public class ProjectUpdateController implements Controller, DataBinding {
    // Java Bean Container
    ProjectDao dao;

    public ProjectUpdateController setProjectDao(ProjectDao dao) {
        this.dao = dao;
        return this;
    }
    
    @Override
    public Object[] getDataBinders() {
        return new Object[] {
            "id", String.class,
            "project", vo.Project.class
        };
    }

    @Override
    public String execute(Map<String, Object> model) throws Exception {
        Project project = (Project)model.get("project");

        if (project.getContent() == null) {
            String id = (String) model.get("id");
            Project result = dao.selectById(Integer.parseInt(id));

            String viewPath;
            if (result != null) {
                model.put("project", result);
                viewPath = "/view/project/ProjectUpdate.jsp";
            } else {
                // 에러 저장
                model.put("error", "일치하는 프로젝트가 없습니다");
                viewPath = "/view/ClientError.jsp";
            }

            return viewPath;
        } else {
            dao.update(project);
            return "redirect:list.do";
        }
    }
}
