package member.model;

import java.util.Date;

public class Member {
	private String id;
	private String name;
	private String password;
	private Date registeredDate;

	public Member(String id, String name, String password, Date registeredDate) {
		this.id = id;
		this.name = name;
		this.password = password;
		this.registeredDate = registeredDate;
	}

	public String getId() {
		return id;
	}

	public String getName() {
		return name;
	}

	public String getPassword() {
		return password;
	}

	public Date getRegisteredDate() {
		return registeredDate;
	}

	public boolean matchPassword(String pwd) {
		return password.equals(pwd);
	}

	public void changePassword(String newPwd) {
		this.password = newPwd;
	}
}