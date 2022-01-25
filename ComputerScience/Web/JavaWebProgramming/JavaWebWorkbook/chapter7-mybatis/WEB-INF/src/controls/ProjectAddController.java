package controls;

import java.util.Map;

import annotation.Component;
import dao.ProjectDao;
import vo.Project;
import bind.DataBinding;

@Component("/project/add.do")
public class ProjectAddController implements Controller, DataBinding {
    // Java Bean Container
    ProjectDao dao;

    public ProjectAddController setProjectDao(ProjectDao dao) {
        this.dao = dao;
        return this;
    }

    @Override
    public Object[] getDataBinders() {
        return new Object[] {
            "project", vo.Project.class
        };
    }
    
    @Override
    public String execute(Map<String, Object> model) throws Exception {
        Project project = (Project)model.get("project");
        if (project.getContent() == null) {
            return "/view/project/ProjectAdd.jsp";
        } else {
            dao.insert(project);

            return "redirect:list.do";
        }
    }
}
