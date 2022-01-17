package auth.service;

// 로그인한 사용자 정보 : 세션 쿠키에 저장할 정보
public class User {
    private String id;
    private String name;

    public User(String id, String name) {
        this.id = id;
        this.name = name;
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }
}
