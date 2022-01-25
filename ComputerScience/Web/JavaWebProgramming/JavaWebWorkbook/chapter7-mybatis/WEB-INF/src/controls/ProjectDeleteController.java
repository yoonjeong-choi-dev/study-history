package controls;

import java.util.Map;

import annotation.Component;
import bind.DataBinding;
import dao.ProjectDao;

@Component("/project/delete.do")
public class ProjectDeleteController implements Controller, DataBinding {
    // Java Bean Container
    ProjectDao dao;

    public ProjectDeleteController setProjectDao(ProjectDao dao) {
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
