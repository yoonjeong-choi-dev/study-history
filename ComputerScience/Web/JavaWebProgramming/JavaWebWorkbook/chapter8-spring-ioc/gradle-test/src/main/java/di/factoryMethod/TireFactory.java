package di.factoryMethod;

import java.text.SimpleDateFormat;
import java.util.Properties;

public class TireFactory {
    public static Tire createTire(String maker) {
        if (maker.equals("Hankook")) {
            return createHankookTire();
        } else {
            return createDafaultTire();
        }
    }

    private static Tire createHankookTire() {
        Tire tire = new Tire();
        tire.setMaker("Hankooko");

        Properties props = new Properties();
        props.setProperty("width", "255");
        props.setProperty("height", "75");
        props.setProperty("rim.diameter", "15");
        tire.setSpec(props);

        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");

        try {
            tire.setCreatedDate(dateFormat.parse("2022-01-15"));
        } catch (Exception e) {}

        return  tire;
    }

    private static Tire createDafaultTire() {
        Tire tire = new Tire();
        tire.setMaker("Custom");

        Properties props = new Properties();
        props.setProperty("width", "123");
        props.setProperty("height", "45");
        props.setProperty("rim.diameter", "89");
        tire.setSpec(props);

        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");

        try {
            tire.setCreatedDate(dateFormat.parse("2022-07-13"));
        } catch (Exception e) {}

        return  tire;
    }
}
