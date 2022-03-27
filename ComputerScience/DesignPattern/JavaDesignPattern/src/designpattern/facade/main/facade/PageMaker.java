package designpattern.facade.main.facade;

import designpattern.facade.main.component.Database;
import designpattern.facade.main.component.HtmlWriter;

import java.io.FileWriter;
import java.io.IOException;
import java.util.Properties;

/**
 * 퍼사드 역할을 하는 클래스
 * - component 패키지의 클래스들을 이용하여 사용자에게 제공할 API 정의
 * - 사용자 측에서는 component 패키지의 존재를 모른채로 패지키의 기능을 사용하게 됨
 * - 인스턴스 생성없이 정적 메서드만 제공
 */
public class PageMaker {
    private PageMaker() {
    }

    public static void makeWelcomePage(String mailAddress, String filename) {
        try {
            // 데이터베이스에서 이메일에 해당하는 유저 이름 가져오기
            Properties mailProp = Database.getProperties("maildata");
            String username = mailProp.getProperty(mailAddress);

            HtmlWriter writer = new HtmlWriter(new FileWriter(filename));
            writer.title(String.format("Welcome to %s's page!", username));
            writer.paragraph(String.format("This is the Main Page for %s", username));
            writer.paragraph("I'm waiting your Email!");
            writer.mailTo(mailAddress, username);
            writer.close();

            System.out.printf("%s is created for %s(%s)\n", filename, mailAddress, username);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // Exercise 2
    public static void makeLinkPage(String filename) {
        try {
            // 데이터베이스에서 이메일에 해당하는 유저 이름 가져오기
            Properties properties = Database.getProperties("maildata");

            HtmlWriter writer = new HtmlWriter(new FileWriter(filename));
            writer.title("Link Page");
            writer.paragraph("List of emails for all users");

            for (String email : properties.stringPropertyNames()) {
                String username = properties.getProperty(email);
                writer.link(email, username);
            }

            writer.close();

            System.out.printf("%s is created\n", filename);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
