package dao;

import java.util.HashMap;
import java.util.Hashtable;
import java.util.List;

import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;

import annotation.Component;
import vo.Member;

@Component("memberDao")
public class MySqlMemberDao implements MemberDao {
    SqlSessionFactory sqlSessionFactory;

    public void setSqlSessionFactory(SqlSessionFactory sqlSessionFactory) {
        this.sqlSessionFactory = sqlSessionFactory;
    }

    @Override
    public List<Member> selectList(HashMap<String, Object> paramMap) throws Exception {
        SqlSession sqlSession = sqlSessionFactory.openSession();

        try {
            return sqlSession.selectList("dao.MemberDao.selectList", paramMap);
        } catch (Exception e) {
            throw e;
        } finally {
            sqlSession.close();
        }
    }

    @Override
    public Member selectById(int id) throws Exception {
        SqlSession sqlSession = sqlSessionFactory.openSession();

        try {
            return sqlSession.selectOne("dao.MemberDao.selectById", id);
        } finally {
            sqlSession.close();
        }

    }

    @Override
    public Member login(String email, String password) throws Exception {
        HashMap<String, String> loginInfo = new HashMap<String, String>();
        loginInfo.put("email", email);
        loginInfo.put("password", password);

        SqlSession sqlSession = sqlSessionFactory.openSession();

        try {
            return sqlSession.selectOne("dao.MemberDao.login", loginInfo);
        } finally {
            sqlSession.close();
        }
    }

    @Override
    public int insert(Member member) throws Exception {
        SqlSession sqlSession = sqlSessionFactory.openSession();

        try {
            int count = sqlSession.update("dao.MemberDao.insert", member);
            sqlSession.commit();

            return count;
        } finally {
            sqlSession.close();
        }
    }

    @Override
    public int update(Member member) throws Exception {
        SqlSession sqlSession = sqlSessionFactory.openSession();

        try {
            Member original = sqlSession.selectOne("dao.MemberDao.selectById", member.getId());

            // 변경해야 하는 부분 저장
            Hashtable<String, Object> paramMap = new Hashtable<String, Object>();
            if (!member.getEmail().equals(original.getEmail())) {
                paramMap.put("email", member.getEmail());
            }
            if (!member.getName().equals(original.getName())) {
                paramMap.put("name", member.getName());
            }

            if (paramMap.size() > 0) {
                paramMap.put("id", member.getId());
                int count = sqlSession.update("dao.MemberDao.update", paramMap);
                sqlSession.commit();

                return count;
            } else {
                return 0;
            }
        } finally {
            sqlSession.close();
        }

    }

    @Override
    public int delete(int id) throws Exception {
        SqlSession sqlSession = sqlSessionFactory.openSession();
        try {
            int count = sqlSession.delete("dao.MemberDao.delete", id);
            sqlSession.commit();
            return count;
        } finally {
            sqlSession.close();
        }
    }
}
