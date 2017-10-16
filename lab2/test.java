package lab2;


//测试类
public class test{

    public static void main(String args[]){
        Book book1 = new Book("a tale of two cities", 746535);
        Book book2 = new Book("gone with wind", 21135);
        Student sam = new Student("Sam", 12345);

        book1.display();
        book2.display();
        sam.display();

        book1.borrow(sam);
        book2.borrow(sam);

        book1.display();
        sam.display();


    }


}