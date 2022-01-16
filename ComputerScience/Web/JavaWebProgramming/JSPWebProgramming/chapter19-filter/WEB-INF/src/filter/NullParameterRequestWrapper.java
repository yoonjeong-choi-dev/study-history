package filter;

import java.util.Collections;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletRequestWrapper;

public class NullParameterRequestWrapper extends HttpServletRequestWrapper {
    private Map<String, String[]> paramsMap = null;

    public NullParameterRequestWrapper(HttpServletRequest request) {
        super(request);
        paramsMap = new HashMap<String, String[]>(request.getParameterMap());
    }

    public void checkNull(String[] parameterNames) {
        for (int i = 0; i < parameterNames.length; i++) {
            if(!paramsMap.containsKey(parameterNames[i])) {
                // 해당 파라미터가 없는 경우 빈문자로 채워준다
                String[] value = new String[]{""};
                paramsMap.put(parameterNames[i], value);
            }
        }
    }

    @Override
    public String getParameter(String name) {
        String[] values = getParameterValues(name);
        if(values!=null && values.length >0) {
            return values[0];
        }
        return null;
    }

    @Override
    public Map<String, String[]> getParameterMap() {
        return paramsMap;
    }

    @Override
    public Enumeration<String> getParameterNames() {
        return Collections.enumeration(paramsMap.keySet());
    }

    @Override
    public String[] getParameterValues(String name) {
        return (String[]) paramsMap.get(name);
    }
}
