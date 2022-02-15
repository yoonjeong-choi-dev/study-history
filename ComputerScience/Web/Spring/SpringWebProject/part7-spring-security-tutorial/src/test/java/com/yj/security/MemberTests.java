package com.yj.security;

import lombok.Setter;
import lombok.extern.log4j.Log4j;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit.jupiter.SpringExtension;
import org.springframework.test.context.web.WebAppConfiguration;

import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;

@ExtendWith(SpringExtension.class)
@WebAppConfiguration
@ContextConfiguration({
        "file:src/main/webapp/WEB-INF/spring/root-context.xml",
        "file:src/main/webapp/WEB-INF/spring/security-context.xml"
})
@Log4j
public class MemberTests {
    @Setter(onMethod_ = @Autowired)
    private PasswordEncoder passwordEncoder;

    @Setter(onMethod_ = @Autowired)
    private DataSource dataSource;

    @Test
    public void testInsertMember() {
        String sql = "insert into member (user_id, user_pw, user_name) values (?, ?, ?)";

        String id, pw, name;
        for(int i=0;i<100;i++){
            Connection conn = null;
            PreparedStatement pstmt = null;

            try {
                conn = dataSource.getConnection();
                pstmt = conn.prepareStatement(sql);
                if(i<80) {
                    id = "user" + i;
                    pw = "user" + i;
                    name ="일반사용자" + i;
                } else if(i<90) {
                    id = "member" + i;
                    pw = "member" + i;
                    name ="운영자" + i;
                } else {
                    id = "admin" + i;
                    pw = "admin" + i;
                    name ="관리자" + i;
                }

                pstmt.setString(1, id);
                pstmt.setString(2, passwordEncoder.encode(pw));
                pstmt.setString(3, name);

                pstmt.executeUpdate();
            } catch(Exception ex) {
                ex.printStackTrace();
            } finally {
                if(pstmt != null) { try { pstmt.close();  } catch(Exception e) {} }
                if(conn != null) { try { conn.close();  } catch(Exception e) {} }
            }
        }
    }

    @Test
    public void testInsertAuth() {
        String sql = "insert into member_auth (user_id, auth) values (?, ?)";

        String id, auth;
        for(int i=0;i<100;i++){
            Connection conn = null;
            PreparedStatement pstmt = null;

            PreparedStatement pstmt2 = null;

            try {
                conn = dataSource.getConnection();
                pstmt = conn.prepareStatement(sql);
                if(i<80) {
                    id = "user" + i;
                    auth = "ROLE_USER";
                } else if(i<90) {
                    id = "member" + i;
                    auth = "ROLE_MEMBER";
                } else {
                    id = "admin" + i;
                    auth = "ROLE_ADMIN";
                }

                pstmt.setString(1, id);
                pstmt.setString(2, auth);

                pstmt.executeUpdate();

                // 관리자는 멤버 권한도 부여함
                if (auth.equals("ROLE_ADMIN")) {
                    pstmt2 = conn.prepareStatement(sql);
                    pstmt2.setString(1, id);
                    pstmt2.setString(2, "ROLE_MEMBER");
                    pstmt2.executeUpdate();
                }


            } catch(Exception ex) {
                ex.printStackTrace();
            } finally {
                if(pstmt != null) { try { pstmt.close();  } catch(Exception e) {} }
                if(pstmt2 != null) { try { pstmt2.close();  } catch(Exception e) {} }
                if(conn != null) { try { conn.close();  } catch(Exception e) {} }
            }
        }
    }
}
