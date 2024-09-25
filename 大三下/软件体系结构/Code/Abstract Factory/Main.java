import factory.*;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java Main class.name.of.ConcreteFactory");
            System.out.println("Example 1: java Main listfactory.ListFactory");
            System.out.println("Example 2: java Main tablefactory.TableFactory");
            System.exit(0);
        }
        Factory factory = Factory.getFactory(args[0]);

        Link sina = factory.createLink("新浪新闻", "http://www.sina.com/");
        Link sohu = factory.createLink("搜狐新闻", "http://www.sohu.com");

        Link us_yahoo = factory.createLink("Yahoo!", "http://www.yahoo.com/");
        Link china_yahoo = factory.createLink("Yahoo!China", "http://www.yahoo.com.cn/");
        Link xmu = factory.createLink("XMU", "http://www.xmu.edu.cn/");
        Link google = factory.createLink("Google", "http://www.google.com/");

        Tray traynews = factory.createTray("新闻");
        traynews.add(sina);
        traynews.add(sohu);

        Tray trayyahoo = factory.createTray("Yahoo!");
        trayyahoo.add(us_yahoo);
        trayyahoo.add(china_yahoo);

        Tray traysearch = factory.createTray("搜索引擎");
        traysearch.add(trayyahoo);
        traysearch.add(xmu);
        traysearch.add(google);

        Page page = factory.createPage("LinkPage", "厦门大学信息学院");
        page.add(traynews);
        page.add(traysearch);
        page.output();
    }
}

