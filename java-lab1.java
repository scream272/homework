import javax.swing.*;
public class lab1 {
    private static boolean judgeloop(String str) {
        int len = str.length();
        for (int j =0; j < len / 2; j++) {
            if (str.charAt(j) != str.charAt(len - 1 - j)) {
                return false;
            }
        }
        return true;
    }
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        String oristr = JOptionPane.showInputDialog("请输入一个数:");
        String str = oristr.replaceAll("\\s*", "").replaceAll("\\pP" , "").toLowerCase();
        if (judgeloop(str))
            JOptionPane.showMessageDialog(null,oristr+"是回文串");
        else
            JOptionPane.showMessageDialog(null,oristr+"不是回文串");
    }
}
