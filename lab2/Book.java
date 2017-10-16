package lab2;

//图书类
public class Book{
    public  String name;
    public  int id;
    public  Student borrower;
    public boolean state;      //状态：1在馆  0外借

    public Book(String name, int id){
        this.name = name;
        this.id = id;
        this.state = true;
    }

    public void display() {
        if (borrower != null) {
            System.out.printf("Book info:\n name: %s, id: %d, student: %s\n", name, id, borrower.name);
        }
        else {
            System.out.printf("Book info:\n name: %s, id: %d, student: %s\n", name, id, "null");
        }
    }

    public  void borrow(Student student){
        //书籍借出需要做两件事：第一是修改书籍的信息，第二是改对应的借阅学生的信息：传递信息为书的类和学生的类
        this.borrower = student;
        this.state = false;
        student.books.add(this);
    }

    public  void ReturnBook(Student student){
        this.borrower = null;
        this.state = true;
        student.books.remove(this);
    }

}