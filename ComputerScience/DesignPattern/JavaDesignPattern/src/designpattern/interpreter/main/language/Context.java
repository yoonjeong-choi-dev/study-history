package designpattern.interpreter.main.language;

import java.util.StringTokenizer;

/**
 * 인터프리터가 구문 해석을 실행하기 위한 정보를 제공하는 역할
 * - 구문 해석을 위해 필요한 메서드 제공
 * - 구문 해석을 실행하고 있는 상황을 표현
 */
public class Context {
    private final StringTokenizer tokenizer;
    private String currentToken;

    public Context(String program) {
        tokenizer = new StringTokenizer(program);
        nextToken();
    }

    public String nextToken() {
        if (tokenizer.hasMoreTokens()) {
            currentToken = tokenizer.nextToken();
        } else {
            currentToken = null;
        }
        return currentToken;
    }

    public String currentToken() {
        return currentToken;
    }

    public void skipToken(String token) throws ParseException {
        // 현재 토큰을 검사한 후, 다음 토큰으로 이동
        if (!token.equals(currentToken)) {
            throw new ParseException(String.format("[WARN] %s is expected, but %s is found", token, currentToken));
        }
        nextToken();
    }

    public int currentNumber() throws ParseException {
        // 현재 토큰의 숫자값 파싱
        int number = 0;
        try {
            number = Integer.parseInt(currentToken);
        } catch (NumberFormatException e) {
            throw new ParseException(String.format("[WARN] Number Parsing Exception : %s", e.getMessage()));
        }

        return number;
    }
}
