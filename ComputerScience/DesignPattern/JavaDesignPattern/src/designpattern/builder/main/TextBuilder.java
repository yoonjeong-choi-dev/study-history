package designpattern.builder.main;

public class TextBuilder extends Builder {
    private final StringBuffer buffer = new StringBuffer();

    @Override
    public void buildTitle(String title) {
        buffer.append("===========================\n");
        buffer.append("[ ").append(title).append(" ]\n").append("\n");
    }

    @Override
    public void buildString(String string) {
        buffer.append("■ ").append(string).append("\n\n");
    }

    @Override
    public void buildItems(String[] items) {
        for (String string : items) {
            buffer.append("\t● ").append(string).append("\n");
        }
        buffer.append("\n");
    }

    @Override
    public void buildClose() {
        buffer.append("===========================\n");
    }

    public String getText() {
        return buffer.toString();
    }
}
