package designpattern.facade.main;

import designpattern.facade.main.facade.PageMaker;

// 클라이언트 코드
// component 패키지의 존재를 모름
public class Main {
    private static final String basePath = "src/designpattern/facade/main";

    public static void main(String[] args) {

        String file1 = String.format("%s/%s", basePath, "welcome.html");
        String file2 = String.format("%s/%s", basePath, "java-yj.html");
        PageMaker.makeWelcomePage("yjchoi7166@gmail.com", file1);
        PageMaker.makeWelcomePage("yjchoi7166.java@gmail.com", file2);

        // Exercise 2
        String file3 = String.format("%s/%s", basePath, "users.html");
        PageMaker.makeLinkPage(file3);
    }
}
