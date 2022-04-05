package designpattern.flyweight.main.flyweight;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

/**
 * Flyweight 역할을 하는 공유 인스턴스
 * - FlyweightFactory 인스턴스에서 해당 인스턴스 생성
 * - 매우 큰 메모리를 차지하는 인스턴스로 공유의 대상이 되는 클래스
 */
public class BigChar {
    // 큰 문자를 저장하는 파일 경로
    private static final String basePath = "src/designpattern/flyweight/main/resource";

    private final char charName;
    private String fontData;

    public BigChar(char charName) {
        this.charName = charName;
        String filePath = String.format("%s/big%c.txt", basePath, charName);
        try {
            BufferedReader reader = new BufferedReader(new FileReader(filePath));

            String line;
            StringBuffer buffer = new StringBuffer();
            while ((line = reader.readLine()) != null) {
                buffer.append(line).append("\n");
            }
            reader.close();
            this.fontData = buffer.toString();

        } catch (IOException e) {
            this.fontData = charName + "?";
        }
    }

    public void print() {
        System.out.println(fontData);
    }
}
