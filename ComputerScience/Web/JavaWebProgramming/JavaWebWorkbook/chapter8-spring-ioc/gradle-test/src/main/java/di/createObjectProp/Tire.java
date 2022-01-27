package di.createObjectProp;

import java.util.Date;

public class Tire {
    String maker;
    String spec;
    Date createdDate;

    public String getMaker() {
        return maker;
    }

    public void setMaker(String maker) {
        this.maker = maker;
    }

    public String getSpec() {
        return spec;
    }

    public void setSpec(String spec) {
        this.spec = spec;
    }

    public Date getCreatedDate() {
        return createdDate;
    }

    public void setCreatedDate(Date createdDate) {
        this.createdDate = createdDate;
    }

    @Override
    public String toString() {
        return "Tire{" +
                "maker='" + maker + '\'' +
                ", spec='" + spec +
                ( (createdDate !=null)? '\'' + ", createdDate=" + createdDate.toString() : "" )+
                '}';
    }
}
