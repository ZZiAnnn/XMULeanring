import Bridge.add.AddMilk;
import Bridge.add.AddNothing;
import Bridge.add.AddSugar;
import Bridge.cup.Cup;
import Bridge.cup.LargeCup;
import Bridge.cup.MediumCup;
import Bridge.cup.SmallCup;

public class Main {
    public static void main(String[] args) {
        Cup largeCupWithMilk = new LargeCup(new AddMilk());
        Cup largeCupWithSugar = new LargeCup(new AddSugar());
        Cup largeCupWithNothing = new LargeCup(new AddNothing());
        Cup mediumCupWithMilk = new MediumCup(new AddMilk());
        Cup mediumCupWithSugar = new MediumCup(new AddSugar());
        Cup mediumCupWithNothing = new MediumCup(new AddNothing());
        Cup smallCupWithMilk = new SmallCup(new AddMilk());
        Cup smallCupWithSugar = new SmallCup(new AddSugar());
        Cup smallCupWithNothing = new SmallCup(new AddNothing());

        largeCupWithMilk.drink();
        largeCupWithSugar.drink();
        largeCupWithNothing.drink();
        mediumCupWithMilk.drink();
        mediumCupWithSugar.drink();
        mediumCupWithNothing.drink();
        smallCupWithMilk.drink();
        smallCupWithSugar.drink();
        smallCupWithNothing.drink();
    }
}
