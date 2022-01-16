package jdbc;

import java.io.IOException;
import java.io.StringReader;
import java.util.Properties;

import java.sql.DriverManager;

import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;

import org.apache.commons.dbcp2.ConnectionFactory;
import org.apache.commons.dbcp2.DriverManagerConnectionFactory;
import org.apache.commons.dbcp2.PoolableConnection;
import org.apache.commons.dbcp2.PoolableConnectionFactory;
import org.apache.commons.dbcp2.PoolingDriver;
import org.apache.commons.pool2.impl.GenericObjectPool;
import org.apache.commons.pool2.impl.GenericObjectPoolConfig;

public class DBCPInitListener implements ServletContextListener {
    
    @Override
    public void contextInitialized(ServletContextEvent sce) {
        String poolConfig = sce.getServletContext().getInitParameter("poolConfig");
        Properties prop = new Properties();

        // web.xml에서 설정한 커넥션 풀 설정 읽어오기
        try {
            prop.load(new StringReader(poolConfig));
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        }

        // jdbc 드라이버 로드 및 커넥션 풀 설정 : chapter17의 로직과 동일
        loadJDBCDriver(prop);
		initConnectionPool(prop);
    }

    private void loadJDBCDriver(Properties prop) {
		String driverClass = prop.getProperty("jdbcdriver");
		try {
			Class.forName(driverClass);
		} catch (ClassNotFoundException ex) {
			throw new RuntimeException("fail to load JDBC Driver", ex);
		}
	}

    private void initConnectionPool(Properties prop) {

		try {
			String jdbcUrl = prop.getProperty("jdbcUrl");
			String username = prop.getProperty("dbUser");
			String pw = prop.getProperty("dbPass");

			// 커넥션 풀이 사용할 커넥션 팩토리
			ConnectionFactory connFactory = new DriverManagerConnectionFactory(jdbcUrl, username, pw);

			// 커넥션을 커넥션 풀에 보관할 때 사용
			// 풀 관리를 하는데 필요한 기능들 제공
			PoolableConnectionFactory poolableConnFactory = new PoolableConnectionFactory(connFactory, null);

			// 커넥션이 유효한지 확인
			poolableConnFactory.setValidationQuery("select 1");

			// 커넥션 풀 설정 정보
			// 쉬는 커넥션 확인 주기, 보관 중인 커넥션 검사 주기, 최소 개수, 최대 개수
			GenericObjectPoolConfig poolConfig = new GenericObjectPoolConfig();
			poolConfig.setTimeBetweenEvictionRunsMillis(1000L * 60L * 5L);
			poolConfig.setTestWhileIdle(true);
			poolConfig.setMinIdle(4);
			poolConfig.setMaxTotal(50);

			// 커넥션 보관 팩토리와 설정을 이용하여 커넥션 풀 생성
			GenericObjectPool<PoolableConnection> connectionPool = new GenericObjectPool<>(poolableConnFactory,
					poolConfig);
			poolableConnFactory.setPool(connectionPool);

			// 커넥션 풀을 제공하는 jdbc 드라이버 등록
			Class.forName("org.apache.commons.dbcp2.PoolingDriver");
			PoolingDriver driver = (PoolingDriver) DriverManager.getDriver("jdbc:apache:commons:dbcp:");
			
			// 커넥션 풀 이름 지정
			String poolName = prop.getProperty("poolName");
			driver.registerPool(poolName, connectionPool);
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}

    @Override
    public void contextDestroyed(ServletContextEvent sce) {

    }
}
