import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.Scanner;

public class FileProcess {

    public static void main(String[] args) throws Exception {
        Scanner input = new Scanner(System.in);
        System.out.println("请输入文件路径:");
        String path = input.next();
        int countChar = 0;
        int countWord = 0;
        InputStreamReader isr = new InputStreamReader(new FileInputStream(path));
        BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(path)));


        while(br.read()!=-1)//read()=-1代表数据读取完毕
        {
            String s = br.readLine();
            countChar += s.length();
            countWord += s.replaceAll("\\p{P}" , "").split(" ").length;
        }
        isr.close();//关闭文件
        System.out.println("字符统计 " + countChar);
        System.out.println("单词数统计 " + countWord );
    }
}
