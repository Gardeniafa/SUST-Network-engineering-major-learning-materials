import org.w3c.dom.ls.LSOutput;

public abstract class Animal {
    public abstract void eating();
    public abstract void sleeping();
    public abstract void thinking();
    public abstract void talking();
}
class Human extends Animal{
    @Override
    public void eating() {
        System.out.println("🍚");
    }

    @Override
    public void sleeping() {
        System.out.println("🛏️💤");
    }

    @Override
    public void thinking() {
        System.out.println("🤔");
    }

    @Override
    public void talking() {
        System.out.println("🗣️");
    }
}
class Bird extends Animal{
    @Override
    public void eating() {
        System.out.println("\uD83D\uDC1B");
    }

    @Override
    public void sleeping() {
        System.out.println("🐦💤");
    }

    @Override
    public void thinking() {
        System.out.println("🐦❓");
    }

    @Override
    public void talking() {
        System.out.println("🐦💬");
    }
}
class Cat extends Animal{
    @Override
    public void eating() {
        System.out.println("🐟");
    }

    @Override
    public void sleeping() {
        System.out.println("🐱💤");
    }
    @Override
    public void thinking() {
        System.out.println("🐱❓");
    }

    @Override
    public void talking() {
        System.out.println("🐱💬");
    }
}

class demo_04{
    public static void main(String[] args) {
        Animal cat = new Cat();
        Animal bird = new Bird();
        Animal human = new Human();
        human.sleeping();
        cat.eating();
        bird.eating();
    }
}