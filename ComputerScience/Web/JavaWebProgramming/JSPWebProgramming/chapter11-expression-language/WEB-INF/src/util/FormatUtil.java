package util;

import java.text.DecimalFormat;
// 정적 메서드 호출 예시를 위한 클래스
public class FormatUtil {

	public static String number(long number, String pattern) {
		DecimalFormat format = new DecimalFormat(pattern);
		return format.format(number);
	}

}