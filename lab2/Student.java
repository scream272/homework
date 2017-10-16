package lab2;

import java.util.ArrayList;

//学生类
public  class Student{
    public String name;
    public int id;
    public ArrayList<Book> books;

    public Student(String name, int id){
        this.name = name;
        this.id = id;
        books = new ArrayList<>();
    }

    public void display()
    {
        System.out.printf("Student info:\n name: %s, id %d, books:\n", name, id);
        if(books != null && !books.isEmpty()) {
            for (Book b : books) {
                System.out.printf("  --%s\n", b.name);
            }
        }
        System.out.printf("\n");
    }

}