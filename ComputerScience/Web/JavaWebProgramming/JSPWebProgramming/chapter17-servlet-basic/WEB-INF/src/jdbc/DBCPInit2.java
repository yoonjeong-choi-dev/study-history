package jdbc;

import java.sql.DriverManager;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;

import org.apache.commons.dbcp2.ConnectionFactory;
import org.apache.commons.dbcp2.DriverManagerConnectionFactory;
import org.apache.commons.dbcp2.PoolableConnection;
import org.apache.commons.dbcp2.PoolableConnectionFactory;
import org.apache.commons.dbcp2.PoolingDriver;
import org.apache.commons.pool2.impl.GenericObjectPool;
import org.apache.commons.pool2.impl.GenericObjectPoolConfig;

// web.xml에서 db 관련 설정을 초기화 파라미터로 전달
public class DBCPInit2 extends HttpServlet {

	// 어플리케이션 시작 시 한번만 실행되는 함수
	// 1. jdbc 드라이버 로드
	// 2. 커넥션 풀 생성 i.e 커넥션 객체들 생성
	@Override
	public void init() throws ServletException {
		loadJDBCDriver();
		initConnectionPool();
	}

	// MySQLDriverLoader에서 구현하였던 함수 : 초기에 연결 시도
	private void loadJDBCDriver() {
		String driverClass = getInitParameter("jdbcdriver");
		try {
			Class.forName(driverClass);
		} catch (ClassNotFoundException ex) {
			throw new RuntimeException("fail to load JDBC Driver", ex);
		}
	}

	private void initConnectionPool() {

		try {
			String jdbcUrl = getInitParameter("jdbcUrl");
			String username = getInitParameter("dbUser");
			String pw = getInitParameter("dbPass");

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
			String poolName = getInitParameter("poolName");
			driver.registerPool(poolName, connectionPool);
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}
}
