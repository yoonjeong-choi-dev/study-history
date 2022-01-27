package di.factoryMethod;

public class EngineFactory {
    public Engine createEngine(String type) {
        if(type.equals("super")) {
            return createSuperEngine();
        } else {
            return createNormalEngine();
        }
    }

    private Engine createSuperEngine() {
        Engine engine = new Engine("SUPER");
        engine.setCc(1000);
        return engine;
    }

    private Engine createNormalEngine() {
        Engine engine = new Engine("Normal");
        engine.setCc(100);
        return engine;
    }
}
