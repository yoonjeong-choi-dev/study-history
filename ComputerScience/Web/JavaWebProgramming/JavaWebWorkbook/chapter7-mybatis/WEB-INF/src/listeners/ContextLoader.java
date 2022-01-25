package listeners;

import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;

import javax.servlet.ServletContext;
import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;

//import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import context.ApplicationContext;


public class ContextLoader implements ServletContextListener {

    static ApplicationContext applicationContext;

    public static ApplicationContext getApplicationContext() {
        return applicationContext;
    }

    @Override
    public void contextInitialized(ServletContextEvent event) {
        try {
            applicationContext = new ApplicationContext();

            ServletContext sc = event.getServletContext();

            // myBatis : 빌더(빌더 패턴)를 통해 SqlSessionFactory 생성
            String resource = sc.getRealPath("/WEB-INF/src/dao/mybatis-config.xml");
            InputStream inputStream = new FileInputStream(new File(resource));
            String propertiesPath = sc.getRealPath(sc.getInitParameter("contextConfigLocation"));
            
            SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);

            // 의존성 주입
            applicationContext.addBean("sqlSessionFactory", sqlSessionFactory);
            applicationContext.prepareObjectsByProperties(propertiesPath);
            applicationContext.prepareObjectsByAnnotation("");
            applicationContext.injectDependency();

            
        } catch (Throwable ex) {
            ex.printStackTrace();
        }
    }

    @Override
    public void contextDestroyed(ServletContextEvent event) { }
}
