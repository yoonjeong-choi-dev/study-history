package dao;

import java.util.List;
import vo.Project;

public interface ProjectDao {
    public List<Project> selectList() throws Exception;
    Project selectById(int id) throws Exception;
    int insert(Project project) throws Exception;
    int update(Project project) throws Exception;
    int delete(int id) throws Exception;
}
