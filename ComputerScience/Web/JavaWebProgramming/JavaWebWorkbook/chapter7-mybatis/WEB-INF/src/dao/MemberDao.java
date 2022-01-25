package dao;

import java.util.HashMap;
import java.util.List;
import vo.Member;

public interface MemberDao {

    public List<Member> selectList(HashMap<String, Object> paramMap) throws Exception;
    public Member selectById(int id) throws Exception;
    public Member login(String email, String password) throws Exception;
    public int insert(Member member) throws Exception;
    public int update(Member member) throws Exception;
    public int delete(int id) throws Exception;
}
