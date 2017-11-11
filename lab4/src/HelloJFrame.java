import javax.swing.*;
import java.awt.Color;
import java.awt.*;
;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;

class HelloJFrame {
    static int count;
    static int number;
    static JLabel infoLabel;
    private static JTextField inputField = new JTextField(20);

    public static void main(String[] args) {

        final int max = 1000;
        final int min = 1;
        Random random = new Random();


        number = random.nextInt(max)%(max-min+1) + min;
        System.out.println("random number is " + number);
        count = 0;
        infoLabel = new JLabel();

        JFrame topPanel = new JFrame("Hello JFrame!");
        topPanel.setLayout(new BoxLayout(topPanel, BoxLayout.LINE_AXIS));
        topPanel.setLayout(new FlowLayout());//设置此容器的布局管理器。 设置 LayoutManager。重写此方法，从而有条件地将调用转发到 contentPane。


        JButton button1 = new JButton("确认");//如果没有设置布局格式，JFrame是无法直接加入JButton组件的，即使调用了add()方法，界面上也是空白的。

        JButton button2 = new JButton("重新开始");//如果没有设置布局格式，JFrame是无法直接加入JButton组件的，即使调用了add()方法，界面上也是空白的。

        JButton button3 = new JButton("退出");//如果没有设置布局格式，JFrame是无法直接加入JButton组件的，即使调用了add()方法，界面上也是空白的。

        topPanel.add(infoLabel);//将指定组件追加到此容器的尾部。这是一个适用于 addImpl(java.awt.Component, java.lang.Object, int) 的便捷方法。 注：如果已经将某个组件添加到显示的容器中，则必须在此容器上调用 validate，以显示新的组件。如果添加多个组件，那么可以在添加所有组件之后，通过只调用一次 validate 来提高效率。
        topPanel.add(inputField);
        topPanel.add(button1);
        topPanel.add(button2);
        topPanel.add(button3);

        infoLabel.setText("你已经猜测了" + count + "次");//定义此组件将要显示的单行文本。如果 text 值为 null 或空字符串，则什么也不显示。

        show(topPanel);

        button1.addActionListener(new ActionListener() {//添加匿名内部类事件监听器
            public void actionPerformed(ActionEvent e) {

                int data;

                data = Integer.parseInt(inputField.getText());
                count = count + 1;
                infoLabel.setText("你已经猜测了" + count + "次");

                if(data > number){
                    topPanel.getContentPane().setBackground(new Color(255,127,80));
                }
                else if(data < number){
                    topPanel.getContentPane().setBackground(new Color(0,0,139));
                }
                else{
                    infoLabel.setText("祝贺你猜对了！");
                    inputField.setEditable(false);

                }

                //System.out.print(count);
            }
        });




        button2.addActionListener(new ActionListener() {//添加匿名内部类事件监听器
            public void actionPerformed(ActionEvent e) {
                Random random = new Random();
                number = random.nextInt(max)%(max-min+1) + min;
                System.out.println("random number is " + number);

                count = 0;
                infoLabel.setText("你已经猜测了" + count + "次");
                inputField.setEditable(true);
            }
        });




        button3.addActionListener(new ActionListener() {//添加匿名内部类事件监听器
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });


    }

    private static void show(JFrame jf) {
        jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jf.setSize(300, 200);//调整组件的大小，使其宽度为 width，高度为 height。 如果 width 值或 height 值小于之前调用 setMinimumSize 指定的最小大小，则它将自动增大。

        jf.setVisible(true);//根据参数 b 的值显示或隐藏此 Window。
    }
}
