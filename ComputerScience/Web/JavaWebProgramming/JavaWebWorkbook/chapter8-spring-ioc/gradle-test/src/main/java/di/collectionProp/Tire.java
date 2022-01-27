package di.collectionProp;

import java.util.Date;
import java.util.Map.Entry;
import java.util.Properties;

public class Tire {
    String maker;
    Date createdDate;
    Properties spec;

    public String getMaker() {
        return maker;
    }

    public void setMaker(String maker) {
        this.maker = maker;
    }

    public Properties Properties() {
        return spec;
    }

    public void setSpec(Properties spec) {
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
        StringBuffer buffer = new StringBuffer();
        if (spec != null) {
            for(Entry<Object, Object> entry : spec.entrySet()) {
                buffer.append(entry.getKey() + ":" + entry.getValue() + ", ");
            }
        }
        return "Tire{" +
                "maker='" + maker + '\'' +
                ", spec='" + buffer.toString() + '\'' +
                ( (createdDate !=null)? '\'' + ", createdDate=" + createdDate.toString() : "" )+
                '}';
    }
}
