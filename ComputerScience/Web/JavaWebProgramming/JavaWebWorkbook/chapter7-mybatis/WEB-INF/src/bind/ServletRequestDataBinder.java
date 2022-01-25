package bind;

import java.lang.reflect.Method;
import java.util.Date;
import java.util.Set;

import javax.servlet.ServletRequest;

public class ServletRequestDataBinder {
    public static Object bind(
            ServletRequest request, Class<?> dataType, String dataName) throws Exception {
        // 기본 타입인 경우, 데이터 이름에 해당하는 요청 파라미터로 데이터 생성
        if (isPrimitiveType(dataType)) {
            return createValuObject(dataType, request.getParameter(dataName));
        }

        // 요청 파라미터의 모든 필드 가져오기
        Set<String> paramNames = request.getParameterMap().keySet();
        Object dataObject = dataType.newInstance();
        Method m = null;

        // 객체에 요청 파라미터에 해당하는 세터 호출
        for (String paramName : paramNames) {
            m = findSetter(dataType, paramName);
            if (m != null) {
                // dataObject.m() 형태로 호출
                m.invoke(dataObject,
                        createValuObject(m.getParameterTypes()[0], request.getParameter(paramName)));
            }
        }

        return dataObject;
    }

    private static boolean isPrimitiveType(Class<?> type) {
        if (type.getName().equals("int") || type == Integer.class ||
                type.getName().equals("long") || type == Long.class ||
                type.getName().equals("float") || type == Float.class ||
                type.getName().equals("double") || type == Double.class ||
                type.getName().equals("boolean") || type == Boolean.class ||
                type == Date.class || type == String.class) {
            return true;
        }
        return false;
    }

    private static Object createValuObject(Class<?> type, String value) {
        if (type.getName().equals("int") || type == Integer.class) {
            return new Integer(value);
        } else if (type.getName().equals("float") || type == Float.class) {
            return new Float(value);
        } else if (type.getName().equals("double") || type == Double.class) {
            return new Double(value);
        } else if (type.getName().equals("long") || type == Long.class) {
            return new Long(value);
        } else if (type.getName().equals("boolean") || type == Boolean.class) {
            return new Boolean(value);
        } else if (type == Date.class) {
            return java.sql.Date.valueOf(value);
        } else {
            return value;
        }
    }

    private static Method findSetter(Class<?> type, String name) {
        Method[] methods = type.getMethods();

        String propName = null;
        for (Method m : methods) {
            // setter가 아니면 무시
            if (!m.getName().startsWith("set"))
                continue;

            // setter의 프로퍼티 이름 추출
            propName = m.getName().substring(3);
            if (propName.toLowerCase().equals(name.toLowerCase())) {
                return m;
            }
        }
        return null;
    }
}
