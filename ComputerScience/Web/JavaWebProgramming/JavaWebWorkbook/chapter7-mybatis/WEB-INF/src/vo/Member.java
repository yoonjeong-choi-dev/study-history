package vo;

import java.util.Date;

public class Member {
    protected int id;
    protected String name;
    protected String email;
    protected String password;
    protected Date createdDate;
    protected Date modifiedDate;

    public int getId() {
        return id;
    }
    public Member setId(int id) {
        this.id = id;
        return this;
    }

    public String getName() {
		return name;
	}
	public Member setName(String name) {
		this.name = name;
		return this;
	}

	public String getEmail() {
		return email;
	}
	public Member setEmail(String email) {
		this.email = email;
		return this;
	}

	public String getPassword() {
		return password;
	}
	public Member setPassword(String password) {
		this.password = password;
		return this;
	}

	public Date getCreatedDate() {
		return createdDate;
	}
	public Member setCreatedDate(Date createdDate) {
		this.createdDate = createdDate;
		return this;
	}
    
	public Date getModifiedDate() {
		return modifiedDate;
	}
	public Member setModifiedDate(Date modifiedDate) {
		this.modifiedDate = modifiedDate;
		return this;
	}
}
