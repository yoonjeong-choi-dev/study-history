package di.factoryMethod;

import java.text.SimpleDateFormat;
import java.util.Properties;

import org.springframework.beans.factory.config.AbstractFactoryBean;

public class TireFactoryBean extends AbstractFactoryBean<Tire> {
    String maker;

    public void setMaker(String maker) {
        this.maker = maker;
    }

    @Override
    public Class<?> getObjectType() {
        return di.factoryMethod.Tire.class;
    }

    @Override
    protected Tire createInstance() {
        if (maker.equals("Hankook")) {
            return createHankookTire();
        } else {
            return createDafaultTire();
        }
    }


    private Tire createHankookTire() {
        Tire tire = new Tire();
        tire.setMaker("[Bean]Hankook");

        Properties props = new Properties();
        props.setProperty("width", "255");
        props.setProperty("height", "75");
        props.setProperty("rim.diameter", "15");
        tire.setSpec(props);

        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");

        try {
            tire.setCreatedDate(dateFormat.parse("2022-01-15"));
        } catch (Exception e) {
        }

        return tire;
    }

    private Tire createDafaultTire() {
        Tire tire = new Tire();
        tire.setMaker("[Bean]Custom");

        Properties props = new Properties();
        props.setProperty("width", "123");
        props.setProperty("height", "45");
        props.setProperty("rim.diameter", "89");
        tire.setSpec(props);

        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");

        try {
            tire.setCreatedDate(dateFormat.parse("2022-07-13"));
        } catch (Exception e) {
        }

        return tire;
    }
}
