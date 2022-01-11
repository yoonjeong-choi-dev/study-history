package util;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.Cookie;
import java.util.Map;
import java.net.URLEncoder; 
import java.net.URLDecoder; 
import java.io.IOException; 

public class Cookies {
	
    // (key, Cookie Object) 형태의 Map 
	private Map<String, Cookie> cookieMap = 
			new java.util.HashMap<String, Cookie>();
	
    // 생성자 : 요청으로 전달된 쿠키들을 저장
	public Cookies(HttpServletRequest request) {
		Cookie[] cookies = request.getCookies();
		if (cookies != null) {
			for (int i = 0 ; i < cookies.length ; i++) {
				cookieMap.put(cookies[i].getName(), cookies[i]);
			}
		}
	}

    // 쿠키의 키를 통해 쿠키 객체 접근
	public Cookie getCookie(String name) {
		return cookieMap.get(name);
	}
	
    // 쿠키의 키를 통해 쿠키 값 접근
	public String getValue(String name) throws IOException {
		Cookie cookie = cookieMap.get(name);
		if (cookie == null) {
			return null;
		}
		return URLDecoder.decode(cookie.getValue(), "utf-8");
	}

    // 특정 키에 대한 쿠키 존재 여부 확인
	public boolean exists(String name) {
		return cookieMap.get(name) != null;
	}

    // createCookie : 오버로딩을 이용하여 다양한 방식으로 쿠키 객체 생성
	public static Cookie createCookie(String name, String value)
	    throws IOException {
		return new Cookie(name, URLEncoder.encode(value, "utf-8"));
	}

	public static Cookie createCookie(String name, String value, String path, int maxAge) 
        throws IOException {
		Cookie cookie = new Cookie(name, URLEncoder.encode(value, "utf-8"));
		cookie.setPath(path);
		cookie.setMaxAge(maxAge);
		return cookie;
	}
	
	public static Cookie createCookie(String name, String value, String domain,
			String path, int maxAge) throws IOException {
		Cookie cookie = new Cookie(name, URLEncoder.encode(value, "utf-8"));
		cookie.setDomain(domain);
		cookie.setPath(path);
		cookie.setMaxAge(maxAge);
		return cookie;
	}

}
