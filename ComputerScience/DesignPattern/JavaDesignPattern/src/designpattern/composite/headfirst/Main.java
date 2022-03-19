package designpattern.composite.headfirst;

public class Main {
    public static void main(String[] args) {
        // 메뉴 구성
        MenuComponent pancakeHouseMenu = new Menu("Pancake House Menu", "Breakfast");
        MenuComponent dinerMenu = new Menu("Diner Menu", "Lunch");
        MenuComponent cafeMenu = new Menu("Cafe Menu", "Dinner");
        MenuComponent dessertMenu = new Menu("Dessert Menu", "Enjoy our dessert!");

        MenuComponent totalMenus = new Menu("All Menus", "All menus are here!");
        totalMenus.add(pancakeHouseMenu);
        totalMenus.add(dinerMenu);
        totalMenus.add(cafeMenu);

        pancakeHouseMenu.add(new MenuItem("Pancake House Menu1", "Pancakes1", true, 3.99));
        pancakeHouseMenu.add(new MenuItem("Pancake House Menu2", "Pancakes2", false, 1.99));

        dinerMenu.add(new MenuItem("Diner Menu1", "with Diner", true, 1.99));
        dinerMenu.add(dessertMenu);

        cafeMenu.add(new MenuItem("Cafe Menu1", "Cafe1", false, 0.75));
        cafeMenu.add(new MenuItem("Cafe Menu2", "Cafe2", false, 2.75));

        dessertMenu.add(new MenuItem("Dessert1", "Sweet!", false, 3.99));
        dessertMenu.add(new MenuItem("Dessert2", "Sweet!", false, 2.79));

        // 클라이언트 생성
        Waitress waitress = new Waitress(totalMenus);
        waitress.print();

        waitress.printVegetarian();
    }
}
