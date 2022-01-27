package di.collectionProp;

import java.util.Map;

public class Car {
    String model;
    Engine engine;
    Tire[] tires;
    Map<String, Object> options;

    public Car() {}

    public Car(String model, Engine engine) {
        this.model = model;
        this.engine = engine;
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public Engine getEngine() {
        return engine;
    }

    public void setEngine(Engine engine) {
        this.engine = engine;
    }

    public Tire[] getTires() {
        return tires;
    }

    public void setTires(Tire[] tires) {
        this.tires = tires;
    }

    public Map<String, Object> getOptions() {
        return options;
    }

    public void setOptions(Map<String, Object> options) {
        this.options = options;
    }

    @Override
    public String toString() {
        StringBuffer carInfo = new StringBuffer();
        carInfo.append("[Car: " + model);
        carInfo.append("\n\t" + engine.toString());
        if(tires!=null) {
            for(Tire t : tires) {
                carInfo.append("\n\t" + t.toString());
            }
        }
        if(options!=null){
            carInfo.append("\n\t");
            for(Map.Entry<String, Object> entry : options.entrySet()) {
                carInfo.append(entry.getKey() + ":" + entry.getValue() + ", ");
            }
        }

        carInfo.append("\n]");
        return carInfo.toString();
    }
}
