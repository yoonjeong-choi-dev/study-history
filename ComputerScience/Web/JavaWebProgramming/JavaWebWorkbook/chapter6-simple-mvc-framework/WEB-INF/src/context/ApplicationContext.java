package context;

import java.io.FileReader;
import java.lang.reflect.Method;
import java.util.Hashtable;
import java.util.Properties;
import java.util.Set;

import javax.naming.Context;
import javax.naming.InitialContext;

import org.reflections.Reflections;

import annotation.Component;

public class ApplicationContext {
    Hashtable<String, Object> objTable = new Hashtable<String, Object>();

    public Object getBean(String key) {
        return objTable.get(key);
    }

    public ApplicationContext(String propertiesPath) throws Exception {
        Properties props = new Properties();
        props.load(new FileReader(propertiesPath));

        prepareObjects(props);
        prepareAnnotationObjects();
        injectDependency();
    }

    private void prepareObjects(Properties props) throws Exception {
        Context ctx = new InitialContext();
        String key = null;
        String value = null;

        for (Object item : props.keySet()) {
            key = (String) item;
            value = props.getProperty(key);

            if (key.startsWith("jndi")) {
                // jndi로 시작하는 경우 데이터 소스
                objTable.put(key, ctx.lookup(value));
            } else {
                // 나머지는 클래스 정보
                objTable.put(key, Class.forName(value).newInstance());
            }
        }
    }

    private void prepareAnnotationObjects() throws Exception {
        Reflections reflector = new Reflections("");

        // Component 어노테이션이 붙은 클래스
        Set<Class<?>> list = reflector.getTypesAnnotatedWith(Component.class);
        // 각 클래스의 어노테이션 이름으로 맵에 추가
        String key = null;
        for(Class<?> cls : list) {
            key = cls.getAnnotation(Component.class).value();
            objTable.put(key, cls.newInstance());
        }
    }

    private void injectDependency() throws Exception {
        // jndi로 시작하지 않는 경우 의존성 주입
        for (String key : objTable.keySet()) {
            if (!key.startsWith("jndi")) {
                callSetter(objTable.get(key));
            }
        }
    }

    private void callSetter(Object obj) throws Exception {
        Object dependency = null;

        // 의존성 주입과 관련된 세터 찾아서 주입
        for (Method m : obj.getClass().getMethods()) {
            if (m.getName().startsWith("set")) {
                dependency = findObjectByType(m.getParameterTypes()[0]);
                if (dependency != null) {
                    m.invoke(obj, dependency);
                }
            }
        }
    }

    private Object findObjectByType(Class<?> type) {
        for (Object obj : objTable.values()) {
            if (type.isInstance(obj)) {
                return obj;
            }
        }
        return null;
    }
}
