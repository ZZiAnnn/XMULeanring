public class Main {
    public static void main(String[] args) {
        try {
            System.out.println("Making root entries...");
            Directory rootdir = new Directory("root");
            Directory bindir = new Directory("bin");
            Directory tmpdir = new Directory("tmp");
            Directory usrdir = new Directory("usr");
            rootdir.add(bindir);
            rootdir.add(tmpdir);
            rootdir.add(usrdir);
            bindir.add(new File("vi", 10000));
            bindir.add(new File("latex", 20000));
            rootdir.printList();

            System.out.println("");
            System.out.println("Making user entries...");
            Directory lee = new Directory("Lee");
            Directory wang = new Directory("Wang");
            Directory liu = new Directory("Liu");
            usrdir.add(lee);
            usrdir.add(wang);
            usrdir.add(liu);
            lee.add(new File("diary.html", 100));
            lee.add(new File("Composite.java", 200));
            wang.add(new File("memo.tex", 300));
            liu.add(new File("game.doc", 400));
            liu.add(new File("junk.mail", 500));
            rootdir.printList();
            //System.out.println(rootdir.getSize());
        } catch (FileTreatmentException e) {
            e.printStackTrace();
        }
    }
}
