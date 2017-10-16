package lab3;

import javax.swing.*;
import java.awt.*;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.TimerTask;

/**
 * 时钟类
 */
public class Clock extends JFrame {
    // 画时钟的面板
    private paintPanel clock = new paintPanel();
    // 定时器
    private java.util.Timer timer = new java.util.Timer();
    // 显示时间的label
    JLabel messageLabel = new JLabel("", SwingConstants.CENTER);

    public Clock() {
        setTitle("时钟");
        this.setVisible(true);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        // this.setLocationRelativeTo(null);
        this.setSize(400, 400);

        add(clock);
        messageLabel.setForeground(Color.RED);
        messageLabel.setFont(new Font("Courier", Font.BOLD, 18));
        add(messageLabel, BorderLayout.SOUTH);

        // 定时器执行任务
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                clock.setCurrentTime();// 设置为当前时间
                messageLabel.setText(clock.getHour() + ":" + clock.getMinute() + ":" + clock.getSecond() + '\n');
                repaint();
            }
        }, 0, 1000);

    }

    public static void main(String[] args) {
        new Clock();
    }

    private class paintPanel extends JPanel {
        private int hour, minute, second;

        public paintPanel() {
            setCurrentTime();
        }

        // 设置时钟为当前时间
        private void setCurrentTime() {
            Calendar calendar = new GregorianCalendar();
            hour = calendar.get(Calendar.HOUR_OF_DAY);
            minute = calendar.get(Calendar.MINUTE);
            second = calendar.get(Calendar.SECOND);
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            int xCenter = getWidth() / 2;
            int yCenter = getHeight() / 2;

            // 计算半径
            int radius = (int) (Math.min(this.getWidth(), this.getHeight()) * 0.8 * 0.5);
            // 画圆
            g.drawOval(xCenter - radius, yCenter - radius, radius * 2, radius * 2);

            // 画钟面上显示的数字
            g.drawString("12", xCenter - 6, yCenter - radius + 12);
            g.drawString("3", xCenter + radius - 12, yCenter + 4);
            g.drawString("6", xCenter - 4, yCenter + radius - 8);
            g.drawString("9", xCenter - radius + 4, yCenter + 6);

            // 画时针、分针、秒针
            g.drawLine(xCenter, yCenter, (int) (xCenter + radius * 0.8 * Math.sin(second * 2 * Math.PI / 60)), (int) (yCenter - radius * 0.8 * Math.cos(second * 2 * Math.PI / 60)));
            g.drawLine(xCenter, yCenter, (int) (xCenter + radius * 0.6 * Math.sin(minute * 2 * Math.PI / 60)), (int) (yCenter - radius * 0.6 * Math.cos(minute * 2 * Math.PI / 60)));
            g.drawLine(xCenter, yCenter, (int) (xCenter + radius * 0.4 * Math.sin((hour + minute / 60.0) * 2 * Math.PI / 12)), (int) (yCenter - radius * 0.4
                    * Math.cos((hour + minute / 60.0) * 2 * Math.PI / 12)));
        }

        public int getHour() {
            return hour;
        }

        public int getMinute() {
            return minute;
        }

        public int getSecond() {
            return second;
        }
    }
}

