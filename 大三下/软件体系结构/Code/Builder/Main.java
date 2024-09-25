public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            //System.out.println(args.length);
            usage();
            System.exit(0);
        }
        if (args[0].equals("plain")) {
            Director director = new Director(new TextBuilder());
            String result = (String)director.construct();
            System.out.println(result);
        } else if (args[0].equals("html")) {
            Director director = new Director(new HTMLBuilder());
            String filename = (String)director.construct();
            System.out.println("�Ѳ���" + filename + "��");
        } else {
            usage();
            System.exit(0);
        }
    }
    public static void usage() {
        System.out.println("Usage: java Main plain  ����һ���ʽ���ļ�");
        System.out.println("Usage: java Main html   ����HTML��ʽ���ļ�");
    }
}

