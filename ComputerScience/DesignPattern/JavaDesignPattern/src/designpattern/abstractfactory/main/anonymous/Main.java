package designpattern.abstractfactory.main.anonymous;

import designpattern.abstractfactory.main.factory.*;

// 추상 팩토리 클래스를 이용하는 클라이언트
// 구체 클래스는 코드 상 존재하지 않으며, 인자로 받아 동적으로 프로그램 구성
public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java Main <class name of concrete factory");
            System.out.println("Example 1: java Main designpattern.abstractfactory.main.concrete.list.ListFactory");
            System.out.println("Example 2: java Main designpattern.abstractfactory.main.concrete.table.TableFactory");
            return;
        }

        Factory factory = Factory.getFactory(args[0]);

        // 각 페이지 이름에 따른 링크 생성
        Link joins = factory.createLink("중앙일보", "https://www.joins.com");
        Link chosun = factory.createLink("조선일보", "https://www.chosun.com");
        Link yahoo = factory.createLink("Yahoo", "https://www.yahoo.com");
        Link naver = factory.createLink("Naver", "https://www.naver.com");
        Link google = factory.createLink("Google", "https://www.google.com");
        Link googleKorea = factory.createLink("Google Korea", "https://www.google.co.kr");

        // 주제별로 링크 분류
        Tray news = factory.createTray("News");
        news.add(joins);
        news.add(chosun);

        Tray googleTray = factory.createTray("Google");
        googleTray.add(google);
        googleTray.add(googleKorea);

        Tray search = factory.createTray("Search Engine");
        search.add(googleTray);
        search.add(yahoo);
        search.add(naver);

        // 페이지 생성
        Page page = factory.createPage("YJ-Page", "YJ");
        page.add(news);
        page.add(search);
        page.output();

    }
}
