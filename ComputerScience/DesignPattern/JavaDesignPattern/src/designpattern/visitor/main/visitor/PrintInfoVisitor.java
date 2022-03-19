package designpattern.visitor.main.visitor;

import designpattern.visitor.main.element.Directory;
import designpattern.visitor.main.element.Entry;
import designpattern.visitor.main.element.File;

import java.util.Iterator;

// 각 요소를 방문하여 정보를 출력하는 Visitor
public class PrintInfoVisitor extends Visitor {
    // 현재 방문한 디렉터리 이름
    private String currentDirectory = "";

    @Override
    public void visit(File file) {
        // 파일 객체 방문 시, 파일 명 호출
        System.out.printf("%s/%s\n", currentDirectory, file.toString());
    }

    @Override
    public void visit(Directory directory) {
        // 폴더 객체 방문시,
        // 1. 폴더 이름 출력
        // 2. 폴더 내의 요소들(File, Directory) 방문
        System.out.printf("%s/%s\n", currentDirectory, directory.toString());

        String origin = currentDirectory;
        currentDirectory = String.format("%s/%s", currentDirectory, directory.getName());
        Iterator<Entry> itr = directory.iterator();
        while(itr.hasNext()) {
            Entry entry = itr.next();

            // 디렉터리의 각 요소들에 대한 방문 요청
            entry.accept(this);
        }

        currentDirectory = origin;
    }
}
